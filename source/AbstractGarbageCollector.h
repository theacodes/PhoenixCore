/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#ifndef __PH_AB_GC_H__
#define __PH_AB_GC_H__

#include <boost/thread.hpp>
#include <boost/function.hpp>

namespace phoenix
{

//! Abstract Garbage Collector.
/*!
	The class eases the chore of creating threaded incremental garbage collectors. It provides a (relatively)
	simple means to peridocially run a function to clean up resource lists. The class is used by ResourceManager
	and BatchRenderer. The basic concept behind threaded garbage collection in phoenix is to allow iteration
	over containers while allowing safe removal of the objects contained. Threaded, Incremental garbage collection
	achieves this by adding dropped() objects to a list of items to be removed (called a recycle list). The threaded
	garbage collector should periodically come by and lock the list of objects and remove some (or all) of the objects
	that are in the recycle list. This class provides the utility of periodically calling the function to delete objects
	in the recycle list. It does not provide the recycle list, or does it provide the function that actually removes
	the objects- this is up to the object list manager.
*/
class AbstractGarbageCollector
{

public:

	/*!
		Creates an abstract garbage collector. Does not start the thread automatically, you must call
        start() to begin collecting.
		\sa setGarbageCollectionFunction()
	*/
	AbstractGarbageCollector( boost::function< void() > _f = boost::function< void() >() )
		: gc_thread(), gc_mutex(), gc_param_mutex(), gc_function( _f ), gc_sleep_time( 50 ), gc_collect_rate( 10 )
	{
	}

	/*!
		Stops the thread.
        \note If the garbage collection thread accesses derived members, you should reset the function first!
	*/
	virtual ~AbstractGarbageCollector()
	{
		stop();
	}

    //! Start Garbage Collecting
    inline void start() { gc_thread = boost::thread( boost::bind( &AbstractGarbageCollector::gcThreadMain, this ) ); }
    inline void stop() { gc_thread.interrupt(); gc_thread.join(); gc_thread = boost::thread(); }

	//! Get a pointer to the thread's handle.
	inline boost::thread& getThreadHandle() { return gc_thread; }

	//! Get a pointer to the resource list's mutex.
	inline boost::recursive_mutex& getMutex() { return gc_mutex; }

	//! Lock resource list mutex.
	/*!
		This should be used (along with scoped_locks) in the resource manager that
		derives from this class in order to secure exclusive access to its
		resource list. You must call unlock() for every call to lock(), failing
		to do so will result in deadlock.
		\sa unlock()
	*/
	inline void lock(){ gc_mutex.lock(); }

	//! Unlock resource list mutex.
	/*!
		This should be used (along with scoped_locks) in the resource manager that
		derives from this class in order to release exclusive access to the resource
		list. 
		\sa lock()
	*/
	inline void unlock() { gc_mutex.unlock(); }

	//! Get GC function.
	/*!
		Returns the function object (boost::function) of the current garbage 
		collection function. This can possibly be used in conditional compiles 
		with no threads. 
	*/
	const boost::function< void() >& getGarbageCollectionFunction() {
		boost::mutex::scoped_lock( gc_param_mutex );
		return gc_function; 
	}

	//! Set GC function.
	/*!
		Sets the function object of the garbage collection function. This
		function is called every gc_sleep_time seconds. You can refer to
		BatchRenderer::pruneGeometry() and ResourceManager::garbageCollect()
		for example implementations.
		\sa BatchRenderer::pruneGeometry(), ResourceManager::garbageCollect()
	*/
    void setGarbageCollectionFunction( const boost::function< void() >& _f = boost::function< void() >() ){
		boost::mutex::scoped_lock( gc_param_mutex );
		gc_function = _f;
	}

	//! Get Sleep Time.
	unsigned int getSleepTime(){
		boost::mutex::scoped_lock( gc_param_mutex );
		return gc_sleep_time;
	}

	//! Set Sleep Time.
	void setSleepTime( unsigned int _s ){
		boost::mutex::scoped_lock( gc_param_mutex );
		gc_sleep_time = _s;
	}

	//! Get Collection Rate
	unsigned int getCollectionRate(){
		boost::mutex::scoped_lock( gc_param_mutex );
		return gc_collect_rate;
	}

	//! Set Collection Rate
	void setCollectionRate( unsigned int _r ){
		boost::mutex::scoped_lock( gc_param_mutex );
		gc_collect_rate = _r;
	}


private:

	//! Thread Handle.
	boost::thread gc_thread;
	
	//! Resource list Mutex.
	boost::recursive_mutex gc_mutex;

	//! Parameter mutex
	boost::mutex gc_param_mutex;

	//! Garbage Collection function.
	boost::function< void() > gc_function;

	//! Sleep time.
	/*!
		How long (in milliseconds) the thread sleeps before calling
		the Garbage Collection function. default is 50ms.
	*/
	unsigned int gc_sleep_time;

	//! Collection rate.
	/*
		The number of resources this will collect every visit. This is optional
		and should be used in the garbage collection function if desired. default
		is 10 resources.
	*/
	unsigned int gc_collect_rate;

	//! Garbage Collection Thread.
	/*!
		This is fairly simple, but fairly robust thread. It sleeps for gc_sleep_time, then
		checks and runs the gc_function. It always waits for interruption from the desctructor
		in order to be immediately terminated.
		\sa setGarbageCollectionFunction()
	*/
	void gcThreadMain()
	{
		try
		{
			while(1)
			{

				//sleep
				boost::this_thread::sleep( boost::posix_time::milliseconds( getSleepTime() ) );

				//call the user's gc function
				if( gc_function )
					gc_function();
			}
		}
		catch( boost::thread_interrupted )
		{
			return;
		}
	}


}; // AbstractGarbageCollector

}; //namespace phoenix

#endif //__PH_AB_GC_H__