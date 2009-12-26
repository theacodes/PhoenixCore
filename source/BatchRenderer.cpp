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
void BatchRenderer::listGeomery()
{
	BOOST_FOREACH( BATCHMAPDELTA::value_type& deltapair, geometry ){
		BOOST_FOREACH( BATCHMAPGAMMA::value_type& gammapair, deltapair.second ){
			BOOST_FOREACH( BATCHMAPBETA::value_type& betapair, gammapair.second ){
				BOOST_FOREACH( BATCHMAPALPHA::value_type& alphapair, betapair.second ){
					BOOST_FOREACH( shared_ptr<BatchGeometry>& geom, alphapair.second )
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


void BatchRenderer::addGeometry( boost::shared_ptr<BatchGeometry> _g )
{
	boost::recursive_mutex::scoped_lock l( getMutex() );
	geometry[_g->getDepth()][ _g->getGroup() ][ _g->getTextureId() ][_g->getPrimitiveType()].push_back( _g );
}

void BatchRenderer::removeGeometry( boost::shared_ptr<BatchGeometry> _g )
{
	boost::recursive_mutex::scoped_lock l( getMutex() );
	recyclelist.push_back( _g );
}

void BatchRenderer::removeGeometryProper( boost::shared_ptr<BatchGeometry> _g, bool _inv )
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

void BatchRenderer::moveGeometry( boost::shared_ptr<BatchGeometry> _g )
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
			boost::shared_ptr<BatchGeometry>& g = recyclelist.back();
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

	//vector to store vertices.
	std::vector< Vertex > vlist(10000);

	//iterate through the graph.
	boost::recursive_mutex::scoped_lock l( getMutex() );

	//depth
	BOOST_FOREACH( BATCHMAPDELTA::value_type& deltapair, geometry )
	{

		//Iterate through each group
		BOOST_FOREACH( BATCHMAPGAMMA::value_type& gammapair, deltapair.second )
		{

			GEOMCONTAINER::iterator groupmaster  = gammapair.second.begin()->second.begin()->second.begin();

			if( (*groupmaster) )
				(*groupmaster)->groupBegin();

			//Iterate through each texture.
			BOOST_FOREACH( BATCHMAPBETA::value_type& betapair, gammapair.second )
			{

				//set our texture
				glEnable( GL_TEXTURE_2D );
				if( (betapair.first) )
				{
					(*(betapair.second.begin())->second.begin())->getTexture()->bind();
				}
				else
				{
					glDisable( GL_TEXTURE_2D );
				}

				// Now run down through each primitive type
				BOOST_FOREACH( BATCHMAPALPHA::value_type& alphapair, betapair.second )
				{

					//clear the vlist
					vlist.clear();

					//now loop for each piece of geometry.
					BOOST_FOREACH( boost::shared_ptr<BatchGeometry>& g , alphapair.second )
					{
						if( ! g->dropped() )
						{
							try{
								g->batch( vlist );
							}catch(...)
							{
								assert( false ); // Not enough space.
							}
						}
					}

					// Check for empty then send it to the graphics card.
					if( ! vlist.empty() )
					{
						glInterleavedArrays( GL_T2F_C4UB_V3F, 0, &vlist[0] );
						glDrawArrays( alphapair.first , 0, vlist.size() );
					}

				} // Primitive Type

			} // Texture

			// call the end group function
			if( (*groupmaster) )
				(*groupmaster)->groupEnd();

		} // Group

	} //depth

	//matrix
	glPopMatrix();

	// Prune.
	pruneGeometry();

}