/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "BatchRenderer.h"

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

unsigned int BatchRenderer::geometryCount()
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


void BatchRenderer::addGeometry( boost::intrusive_ptr<BatchGeometry> _g )
{
	boost::recursive_mutex::scoped_lock l( getMutex() );
	geometry[_g->getDepth()][ _g->getGroup() ][ _g->getTextureId() ][_g->getPrimitiveType()].push_back( _g );
}

void BatchRenderer::removeGeometry( boost::intrusive_ptr<BatchGeometry> _g )
{
	boost::recursive_mutex::scoped_lock l( getMutex() );
	recyclelist.push_back( _g );
}

void BatchRenderer::removeGeometryProper( boost::intrusive_ptr<BatchGeometry> _g, bool _inv )
{

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
		//std::cout<<"Removing..."<<std::endl;
		boost::swap( (*f) , container->back() );
		container->pop_back();


		//now check the above containers.
		if( geometry[ depth ][ groupid ][ textureid ][ primitivetype ].empty() ){
			geometry[ depth ][ groupid ][ textureid ].erase( primitivetype );

			if( geometry[ depth ][ groupid ][ textureid ].empty() ){
				geometry[ depth ][ groupid ].erase( textureid );

				if( geometry[ depth ][ groupid ].empty() ){
					geometry[ depth ].erase( groupid );

					if( geometry[ depth ].empty() ){
						geometry.erase( depth );
					}
				}
			}
		}
	}
	else
	{
		//throw;
	}
}

void BatchRenderer::moveGeometry( boost::intrusive_ptr<BatchGeometry> _g )
{
	lock();
	removeGeometryProper( _g, true );
	addGeometry( _g );
	unlock();
}


void BatchRenderer::pruneGeometry()
{
	
	boost::recursive_mutex::scoped_lock l( getMutex() );

    unsigned int multiplier = recyclelist.size()/getCollectionRate();
    if( multiplier < getCollectionRate() ) multiplier = getCollectionRate();
	
	for( unsigned int i = 0; i < multiplier; ++i )
	{
		if( ! recyclelist.empty() )
		{
			boost::intrusive_ptr<BatchGeometry>& g = recyclelist.back();
			if( g )
				removeGeometryProper( g );
			recyclelist.pop_back();
		}
		else
		{
			break;
		}
	}
}

void BatchRenderer::draw( )
{

    // View.
    view.activate();

	// matrix stuff
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

    // Enable states
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

	//vector to store vertices.
	std::vector< Vertex > vlist;
    vlist.reserve( 1000 );

	//iterate through the graph.
	boost::recursive_mutex::scoped_lock l( getMutex() );

	//depth
    BATCHMAPDELTA::iterator deltaend = geometry.end();
    for( BATCHMAPDELTA::iterator deltapair = geometry.begin(); deltapair != deltaend; ++deltapair )
	{

		//Iterate through each group
        BATCHMAPGAMMA::iterator gammaend = deltapair->second.end();
        for( BATCHMAPGAMMA::iterator gammapair = deltapair->second.begin(); gammapair != gammaend; ++gammapair )
		{

            intrusive_ptr<BatchGeometry> groupmaster  = (*gammapair->second.begin()->second.begin()->second.begin());

			if( groupmaster )
				groupmaster->groupBegin();

			//Iterate through each texture.
            BATCHMAPBETA::iterator betaend = gammapair->second.end();
			for( BATCHMAPBETA::iterator betapair = gammapair->second.begin(); betapair != betaend; ++betapair )
			{

				//set our texture
				glEnable( GL_TEXTURE_2D );
				if( (betapair->first) )
				{
					(*(betapair->second.begin())->second.begin())->getTexture()->bind();
				}
				else
				{
					glDisable( GL_TEXTURE_2D );
				}

				// Now run down through each primitive type
                BATCHMAPALPHA::iterator alphaend = betapair->second.end();
				for( BATCHMAPALPHA::iterator alphapair = betapair->second.begin(); alphapair != alphaend; ++alphapair )
				{

					//now loop for each piece of geometry.
                    GEOMCONTAINER::iterator geomend = alphapair->second.end();
                    for( GEOMCONTAINER::iterator geom = alphapair->second.begin(); geom != geomend; ++geom )
                    {
						if( (*geom) && ! (*geom)->dropped() )
						{
							try{
								(*geom)->batch( vlist );
							}catch(...)
							{
								assert( false ); // Not enough space.
							}
						}
					}

					// Check for empty then send it to the graphics card.
					if( ! vlist.empty() )
					{

                        glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &vlist[0].tcoords);
                        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), &vlist[0].color);
                        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vlist[0].position);

						glDrawArrays( alphapair->first , 0, vlist.size() );

                        //clear the vlist
					    vlist.clear();

					}

				} // Primitive Type

			} // Texture

			// call the end group function
			if( groupmaster )
				groupmaster->groupEnd();

		} // Group

	} //depth

    // disable states
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

	//matrix
	glPopMatrix();

	// Prune.
	pruneGeometry();

}