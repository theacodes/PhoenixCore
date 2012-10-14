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

#ifdef DEBUG_BATCHRENDERER
//! Lists all the geometry in the list.
void BatchRenderer::listGeometry()
{
	BOOST_FOREACH( BATCHMAPDELTA::value_type& deltapair, geometry ){
		BOOST_FOREACH( BATCHMAPGAMMA::value_type& gammapair, deltapair.second ){
			BOOST_FOREACH( BATCHMAPBETA::value_type& betapair, gammapair.second ){
				BOOST_FOREACH( BATCHMAPALPHA::value_type& alphapair, betapair.second ){
					BOOST_FOREACH( intrusive_ptr<BatchGeometry>& geom, alphapair.second )
					{
						std::cout<<"\n Geometry "<<geom.get()
							<<" at "
							<<deltapair.first
							<<", "<<gammapair.first
							<<", "<<betapair.first
							<<", "<<alphapair.first
							<<" with properties "<<geom->getDepth()
							<<", "<<geom->getGroup()
							<<", "<<geom->getTextureId()
							<<", "<<geom->getPrimitiveType();
					}
				}
			}
		}
	}
}
#endif

unsigned int BatchRenderer::count()
{
	boost::recursive_mutex::scoped_lock l( getMutex() );
	unsigned int total = 0;
	BOOST_FOREACH( BATCHMAPDELTA::value_type& deltapair, geometry ){
		BOOST_FOREACH( BATCHMAPGAMMA::value_type& gammapair, deltapair.second ){
			BOOST_FOREACH( BATCHMAPBETA::value_type& betapair, gammapair.second ){
				BOOST_FOREACH( BATCHMAPALPHA::value_type& alphapair, betapair.second ){
					total += alphapair.second.size();
				}
			}
		}
	}
	return total;
}


void BatchRenderer::add( boost::intrusive_ptr<BatchGeometry> _g )
{
	std::cout<<"Adding geom: "<<_g<<std::endl;
	geometry_set.insert(_g);
}

void BatchRenderer::remove( boost::intrusive_ptr<BatchGeometry> _g )
{
	std::cout<<"Removing geom: "<<_g<<std::endl;
	geometry_set.erase(_g);
}

void BatchRenderer::removeProper( boost::intrusive_ptr<BatchGeometry> _g, bool _inv )
{
/*
	unsigned int textureid = _g->getTextureId();
	signed int groupid = _g->getGroup();
	unsigned int primitivetype = _g->getPrimitiveType();
	float depth = _g->getDepth();

	if( _inv == true ) {// we're using the previous value
		groupid = _g->getGroupInvariant().getPrevious();
		primitivetype = _g->getPrimitiveTypeInvariant().getPrevious();
		depth = _g->getDepthInvariant().getPrevious();
		textureid = _g->getTextureIdInvariant().getPrevious();
	}

	//lock the mutex
	boost::recursive_mutex::scoped_lock l( getMutex() );

	GEOMCONTAINER* container = &(geometry[ depth ][ groupid ][ textureid ][ primitivetype ]);
	GEOMCONTAINER::iterator f = std::find( container->begin(), container->end(), _g );
	if( f != container->end() )
	{
		// The ol' pop & swap;
		boost::swap( (*f) , container->back() );
		container->pop_back();

	}
	else
	{
		//throw;
	}*/
}

void BatchRenderer::move( boost::intrusive_ptr<BatchGeometry> _g )
{
	assert(false);
}


void BatchRenderer::clean()
{
/*
	boost::recursive_mutex::scoped_lock l( getMutex() );

    unsigned int multiplier = recyclelist.size()/getCollectionRate();
    if( multiplier < getCollectionRate() ) multiplier = getCollectionRate();

	for( unsigned int i = 0; i < multiplier; ++i )
	{
		if( ! recyclelist.empty() )
		{
			boost::intrusive_ptr<BatchGeometry>& g = recyclelist.back();
			if( g )
				removeProper( g );
			recyclelist.pop_back();
		}
		else
		{
			break;
		}
	}*/
}

/*!
	Main drawing routine,
	this is the meat of phoenix, all of the important stuff goes here.
*/
void BatchRenderer::draw( bool _persist_immediate )
{

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

	//clipping variables
	bool clipping = false;
	Rectangle clipping_rect;

	// track state
	BatchState state;

	//iterate through the graph.
	boost::recursive_mutex::scoped_lock l( getMutex() );

	//activate the group state
	// GROUPSTATEMAP::iterator gs = groupstates.find( gammapair->first );
	// if( gs != groupstates.end() ) gs->second->begin( *this );

	std::cout<<"Starting drawing..."<<std::endl;
	auto end = geometry_set.end();
	for(auto it = geometry_set.begin(); it != end;){
		auto geom = (*it++); //increment but grab it first, allows for deletion in place

		if( geom && ! geom->dropped() && geom->getEnabled() )
		{

			std::cout<<"Drawing geom "<<geom<<" d: "<<geom->getDepth()<<" g: "<<geom->getGroup()<<" t: "<<geom->getTextureId()<<" p: "<<geom->getPrimitiveType()<<std::endl;

			state.update(geom);
			state.activate();

			try{

				// if( geom->locked() ){
				// 	submitVertexBufferObject(geom);
				// 	continue;
				// }

				// Check for clipping, and if clipped, skip batching.
				//if( clipGeometry( geom, clipping, clipping_rect ) ) continue;

				/* Batch the vertices */
				geom->batch( vlist );

				/* Do not accumulate for tri strips, line strips, line loops, triangle fans, quad strips, or polygons */
				if( geom->getPrimitiveType() == GL_LINE_STRIP ||
					geom->getPrimitiveType() == GL_LINE_LOOP ||
					geom->getPrimitiveType() == GL_TRIANGLE_STRIP ||
					geom->getPrimitiveType() == GL_TRIANGLE_FAN ||
					geom->getPrimitiveType() == GL_QUAD_STRIP ||
					geom->getPrimitiveType() == GL_POLYGON ){
						// Send it on, this will also clear the list for the next geom so it doesn't acccumlate as usual.
						submitVertexList(vlist, geom->getPrimitiveType());
				}


			}catch(...)
			{
				assert( false ); // Not enough space.
			}

			// Send it on
			submitVertexList(vlist,geom->getPrimitiveType());


			if( !persist_immediate && geom->getImmediate() ) geom->drop();
		}

		// call the end group function
		// if( gs != groupstates.end() ) gs->second->end( *this );

	} // end iteration

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

	//Do we have clipping enabled?
	if(clipping) {
		glDisable( GL_SCISSOR_TEST );
	}

	// Prune.
	clean();

}

/*!
	Clipping Routine
*/
bool BatchRenderer::clipGeometry(  boost::intrusive_ptr<BatchGeometry> geom, bool &clipping, phoenix::Rectangle &clipping_rect ){
	// Check for clipping
	if( geom->getClipping() ){

		//enable clipping, if we're not already doing it.
		if( !clipping ){
			glEnable( GL_SCISSOR_TEST );
			clipping = true;
		}

		// set the clip area, if it's not already the same.
		if( clipping_rect != geom->getClippingRectangle()){
			clipping_rect = geom->getClippingRectangle();

			// translate from top-left coords to bottom-left cords
			GLint view[4];
			glGetIntegerv( GL_VIEWPORT, &view[0] );
			GLuint r_y = view[3] - ((GLuint)clipping_rect.getX() + (GLuint)clipping_rect.getHeight());

			glScissor( (GLuint)clipping_rect.getX() , r_y, (GLsizei)clipping_rect.getWidth(), (GLsizei)clipping_rect.getHeight() );
		}

		if( geom->locked() ){
			submitVertexBufferObject(geom);
		} else {
			std::vector< Vertex > t_vlist;
			geom->batch( t_vlist );
			submitVertexList(t_vlist,geom->getPrimitiveType());
		}

		return true;

	}
	else {

		//disable clipping, if we're still doing it
		if( clipping ){
			glDisable( GL_SCISSOR_TEST );
			clipping = false;
		}

		return false;
	}
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

	//If we have a render target active, set it. Don't keep drawing if it failed.
	if( target && !target->start() ) return;

	// View.
    view.activate();

	// matrix stuff
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    // Enable states
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

	//activate the group state
	GROUPSTATEMAP::iterator gs = groupstates.find( geom->getGroup() );
	if( gs != groupstates.end() ) gs->second->begin( *this );

	//set our texture
	if( (geom->getTextureId()) ){
		glEnable( GL_TEXTURE_2D );
		geom->getTexture()->bind();
	}
	else{
		glDisable( GL_TEXTURE_2D );
	}

	// Check for clipping, and if clipped, skip regular rendering.
	bool clipping = false;
	Rectangle clipping_rect;
	if( !clipGeometry( geom, clipping, clipping_rect ) ){
		std::vector< Vertex > t_vlist;
		geom->batch( t_vlist );
		submitVertexList(t_vlist,geom->getPrimitiveType());
	} else {
		//disable clipping
		glDisable( GL_SCISSOR_TEST );
	}


	// call the end group function
	if( gs != groupstates.end() ) gs->second->end( *this );

    // disable states
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

	//matrix
	glPopMatrix();

	//If we have a render target active, and it was in use, unbind it now.
	if( target ){
		target->end();
	}
}
