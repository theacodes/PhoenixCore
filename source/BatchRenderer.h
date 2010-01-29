/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#ifndef __PH_BATCH_RENDERER_H__
#define __PH_BATCH_RENDERER_H__

#include <map>
#include <vector>
#include <iostream>
#include <GL/glfw.h>
#include <boost/unordered_map.hpp>
#include <boost/thread.hpp>
#include "AbstractGarbageCollector.h"
#include "View.h"
#include "Droppable.h"

namespace phoenix
{

class BatchGeometry;

//! Optimizing Batch Renderer.
/*!
	The Optimizing Batch Renderer is the soul of phoenix's rendering framework. All drawing calls 
	will go through the batching renderer. The main purpose of the batching renderer is to store all geometry 
	and draw it at once, performing as many optimizations as possible. This adds a slight layer of complexity, 
	but the speed tradeoff is well worth it. BatchGeometry is automatically sorted in a graph based on
	depth, group, texture, and primitive type (in that order).
*/
class BatchRenderer
	: public AbstractGarbageCollector
{

public:

	//! Constructor
	/*!
		Initializes the geometry graph and starts the garbage collection routines.
	*/
	BatchRenderer( )
		: geometry(), recyclelist(), AbstractGarbageCollector()
	{
        setGarbageCollectionFunction( boost::bind( &BatchRenderer::prune, this ) );
		//collect fast.
		setSleepTime( 5 );
        setCollectionRate( 2 );
	}

	//! Destructor
	/*!
		Releases all references to geometry. 
	*/
	virtual ~BatchRenderer()
	{
        setGarbageCollectionFunction();//clear the gc function
		clear(); //drop all geometry.
	}

	//! Add geometry to the render graph. (Automatically called by BatchGeometry::create() ).
	void add( boost::intrusive_ptr<BatchGeometry> _g );

	//! Add geometry to the recycle list. ( Automatically called by BatchGeometry::drop() ).
	void remove( boost::intrusive_ptr<BatchGeometry> _g );

	//! Update a geometry's position in the graph. ( Automatically called by BatchGeometry::update() ).
	void move( boost::intrusive_ptr<BatchGeometry> _g );

	//! Drops all geometry.
	void clear()
	{
		lock();
		recyclelist.clear();
		geometry.clear();
		unlock();
	}

	//! Counts all the geometry in the list (may be slow). 
	unsigned int count();

    //! Sets the rendere's view.
    inline void setView( const View& other ) { view = other; }

    //! Gets a reference to the renderer's view.
    inline View& getView() {return view; }

#ifdef DEBUG_BATCHRENDERER
	//! Lists all the geometry in the list.
	void listGeometry();
#endif

	//! Draws everything in the graph.
	void draw( );

private:

	typedef std::list< boost::intrusive_ptr<BatchGeometry> > GEOMCONTAINER;
	typedef boost::unordered_map< unsigned int, GEOMCONTAINER > BATCHMAPALPHA; // Primitive Keyed
	typedef boost::unordered_map< unsigned int, BATCHMAPALPHA > BATCHMAPBETA; // Texture Keyed
	typedef boost::unordered_map< signed int, BATCHMAPBETA > BATCHMAPGAMMA; // Group Keyed
	typedef std::map< float, BATCHMAPGAMMA > BATCHMAPDELTA; // Depth Keyed (Ordered)

	//! Geometry List Container.
	BATCHMAPDELTA geometry;

	//! Recycle list
	std::vector< boost::intrusive_ptr<BatchGeometry> > recyclelist;

    //! View
    View view;

	//! Prune routine
	virtual void prune();

	//! Real removal routine ( used by prune() and move() ).
	void removeProper( boost::intrusive_ptr<BatchGeometry> _g , bool _inv = false);
};

} //namespace phoenix

#include "BatchGeometry.h"

#endif //__PH_BATCH_RENDERER_H__
