/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

//Uncomment this for really annoying spam on msvc compilers.
//#pragma warning( disable : 4503 )
#include "BatchRenderer.h"
#include "BatchState.h"

using namespace boost;
using namespace phoenix;
using namespace std;


bool BatchGeometryPtrCompare::operator()(const boost::intrusive_ptr<BatchGeometry> a, const boost::intrusive_ptr<BatchGeometry> b) const{
	return (*a) < (*b);
}


#ifdef DEBUG_BATCHRENDERER
//! Lists all the geometry in the list.
void BatchRenderer::listGeometry()
{
	std::cout<<"This has not been implemented."
}
#endif

unsigned int BatchRenderer::count()
{
	return geometry_set.size();
}


void BatchRenderer::add( boost::intrusive_ptr<BatchGeometry> _g )
{
	//std::cout<<"Adding geom: "<<_g<<" d: "<<_g->getDepth()<<" g: "<<_g->getGroup()<<" t: "<<_g->getTextureId()<<" p: "<<_g->getPrimitiveType()<<std::endl;
	geometry_set.insert(_g);
}

void BatchRenderer::remove( boost::intrusive_ptr<BatchGeometry> _g )
{
	//std::cout<<"Removing geom: "<<_g<<" d: "<<_g->getDepth()<<" g: "<<_g->getGroup()<<" t: "<<_g->getTextureId()<<" p: "<<_g->getPrimitiveType()<<std::endl;
	// std::erase will nuke everything with the same state, so we'll have to hunt down this particular geom.
	// this is O(log(n) + r) n being the number of geoms, r being the number of geoms with the same key.
	auto iters = geometry_set.equal_range(_g);

	if(iters.first == iters.second) return; // nothing found
	for(;iters.first != iters.second; ++iters.first){
		if( *iters.first == _g ){
			geometry_set.erase(iters.first);
			break;
		}
	}
}


/*!
	Main drawing routine,
	this is the meat of phoenix, all of the important stuff goes here.
*/
void BatchRenderer::draw( bool _persist_immediate )
{

	// Do we even have anything to draw?
	if(geometry_set.empty()) return;

	persist_immediate = _persist_immediate;

	//Do we have a shader? Activate it
	if( shader ) shader->activate();

	//If we have a render target active, set it. Don't keep drawing if it failed.
	if( target ){
		if( target->start() ){
			target->modifyView(view);
		} else {
			return;
		}
	}

	//Clear
	if( enable_clear ) clearScreen(clear_color);

    // View.
    view.activate();

	// push the modelview matrix (the view activate() function definitely put is in modelview mode).
	glPushMatrix();

    // Set up states
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);

	//vector to store vertices.
	std::vector< Vertex > vlist;
    vlist.reserve( 1000 );

	// track state
	BatchState state;

	//iterate through the graph.

	// First we need to initialize the state object with the first geom
	// This fixes issues with state tracking.

	auto end = geometry_set.end();
	auto geom = BatchGeometryPtr();
	for(auto it = geometry_set.begin(); it != end;){
		geom = (*it++); //increment but grab it first, allows for deletion in place

		if( geom && ! geom->dropped() )
		{

			/* If the update will cause a state change, submit the vertices accumulated */
			if(state.update(geom)){
				//std::cout<<"Submitting the batch... "<<vlist.size()<<" vertices with type "<<state.last().getPrimitiveType()<<std::endl;
				submitVertexList(vlist, state.last().getPrimitiveType());
			}

			// Now activate state changes (if any)
			state.activate(*this);

			if(geom->getEnabled()){
				try{

					//std::cout<<"Drawing geom "<<geom<<" d: "<<geom->getDepth()<<" g: "<<geom->getGroup()<<" t: "<<geom->getTextureId()<<" p: "<<geom->getPrimitiveType()<<std::endl;

					if( geom->locked() ){
					 	submitVertexBufferObject(geom);
					}

					/* Do not accumulate for tri strips, line strips, line loops, triangle fans, quad strips, or polygons */
					else if( geom->getPrimitiveType() == GL_LINE_STRIP ||
						geom->getPrimitiveType() == GL_LINE_LOOP ||
						geom->getPrimitiveType() == GL_TRIANGLE_STRIP ||
						geom->getPrimitiveType() == GL_TRIANGLE_FAN ||
						geom->getPrimitiveType() == GL_QUAD_STRIP ||
						geom->getPrimitiveType() == GL_POLYGON ){
							// doing this with the same list is fine because the primitive type causes a batch break anyways.
							geom->batch(vlist);
							// Send it on, this will also clear the list for the next geom so it doesn't acccumlate as usual.
							submitVertexList(vlist, geom->getPrimitiveType());
					}
					/* Accumulate, this is standard geometry */
					else {
						geom->batch( vlist );
					}


				}catch(...)
				{
					assert( false ); // Not enough space.
				}


				// Remove it.
				if( !persist_immediate && geom->getImmediate() ) geom->drop();
			}
		}

	} // end iteration

	// If there is anything left in the vertex buffer, submit it.
	if(vlist.size() && geom){
		//std::cout<<"Submitting the batch... "<<vlist.size()<<" vertices with type "<<state.last().getPrimitiveType()<<std::endl;
		state.update(geom);
		state.activate(*this);
		submitVertexList(vlist, state.last().getPrimitiveType());
	}

	// cleanup
	state.deactivate(*this);

    // disable states
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

	//matrix
	glPopMatrix();

	//If we have a render target active, and it was in use, unbind it now.
	if( target ){
		target->end();
		target->restoreView(view);
	}

	//Do we have a shader? deactivate it
	if( shader ) shader->deactivate();

	//std::cout<<"... drawing complete."<<std::endl;

}

/*!
	Vertex submission routine.
	Sends data to opengl
*/
void BatchRenderer::submitVertexList( std::vector< Vertex >& vlist, unsigned int type ){
	if( vlist.empty() ) return;

    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vlist[0].tcoords);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &vlist[0].color);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vlist[0].position);

	glDrawArrays( type, 0, vlist.size() );

    //clear the vlist
	vlist.clear();
}

void BatchRenderer::submitVertexBufferObject( boost::intrusive_ptr<BatchGeometry> geom ){
	if(!geom->getEnabled()) return;

	glBindBuffer(GL_ARRAY_BUFFER, geom->getVertexBuffer());

    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), 0);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), (GLvoid*)sizeof(TextureCoords));
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)(sizeof(TextureCoords) + sizeof(Color)));

	glDrawArrays( geom->getPrimitiveType(), 0, geom->getVertexBufferSize() );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/* Immediate drawing routine, fairly simple */
void BatchRenderer::drawImmediately(  boost::intrusive_ptr<BatchGeometry> geom ){

	if( !geom ) return;

	//Do we have a shader? Activate it
	if( shader ) shader->activate();

	//If we have a render target active, set it. Don't keep drawing if it failed.
	if( target ){
		if( target->start() ){
			target->modifyView(view);
		} else {
			return;
		}
	}

	// View.
    view.activate();

	// matrix stuff
	glPushMatrix();

    // Enable states
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);

	// track state
	BatchState state;

	state.update(geom);
	state.activate(*this);

	if(geom->locked()){
		submitVertexBufferObject(geom);
	} else {
		std::vector< Vertex > t_vlist;
		geom->batch( t_vlist );
		submitVertexList(t_vlist,geom->getPrimitiveType());
	}

	state.deactivate(*this);

    // disable states
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

	//matrix
	glPopMatrix();

	//If we have a render target active, and it was in use, unbind it now.
	if( target ){
		target->end();
		target->restoreView(view);
	}

	//Do we have a shader? deactivate it
	if( shader ) shader->deactivate();
}
