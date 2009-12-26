/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHDROPPABLE_H__
#define __PHDROPABLE_H__

namespace phoenix
{

//! Droppable object.
/*!
	Provides a simple abstract class for 'droppable' objects. Essentially
	this eases the creating of garbage collected objects that are to be
	iterated over. Derived classes should add themselves to their managers
	recycle list to be garbage collected. Dropped objects are considered
	deleted and should be skipped during iteration.
	\sa AbstractGarbageCollector
*/
class Droppable
{

public:

	Droppable()
		: _dropped( false )
	{}

	virtual ~Droppable()
	{
	}

	//! Drop
	/*!
		Sets this object to 'dropped', and does nothing else.
		It is encourage that derived classes overload this,
		and simply call it with Droppable::drop().
	*/
	inline virtual void drop()
	{
		_dropped = true;
	}

	//! Dropped
	/*!
		Returns if this object has been 'dropped', this
		can be used by iterative lists that want to 
		skip objects that have been listed to be deleted.
	*/
	inline bool dropped()
	{
		return _dropped;
	}

private:
	bool _dropped;


}; //class droppable

} //namespace phoenix

#endif //__PHDROPPABLE_H__