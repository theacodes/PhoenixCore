/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHRESOURCE_H__
#define __PHRESOURCE_H__

#include "ResourceManager.h"
#include "Droppable.h"

#include <string>

namespace phoenix
{

    //! Garbage-Collected Resource
    /*!
    	This class is provided for garbage collection of dynamically allocated
    	objects. This can be used with ResourceManager to enable
    	automatic garbage collection.
    */
    class Resource
        : public virtual Droppable
    {

    public:

        //! Private constructor.
        /*!
            Constructs the resource and initializes its members. It adds the resource to
            the resource manager's list.
        */
        Resource( ResourceManager& rm, const signed int& t = 0 )
                : Droppable(), _rmanager(rm), _type(t), _name("None")
        {
            rm.addResource( this );
        }


        //! Destructor.
        /*!
            Should be overloaded and used to clean up anything allocated by this resource.
        */
        virtual ~Resource()
        {
        }

        //! Grab
        /*!
        	This should be used to grab a pointer to this resource.
        	Derived classes should call grab<DerivedResource>(). If it fails
        	to grab a valid pointer, or fails to cast, it will throw an exception.
        */
        template <typename T>
        inline boost::intrusive_ptr<T> grab()
        {
			return boost::static_pointer_cast<T,Resource>( this );
        }

        //! Drop
        /*!
            This function adds this resource to the resource manager's recycle list to be
			garbage collected. This means the object will be destructed as soon as the 
			garbage colletor comes to it, and it should no longer be used for anything.
        */
        inline virtual void drop(){ 
			if( ! dropped() )
			{
				Droppable::drop();
				_rmanager.removeResource( this );
			}
		}

        //! Get resource manager.
        inline ResourceManager& getResourceManager()
        {
            return _rmanager;
        }

        //! Get Type.
        inline signed int getType() const
        {
            return _type;
        }

        //! Set Type.
        inline void setType(const signed int& t)
        {
            _type = t;
        }

        //! Get Name
        inline const std::string& getName() const
        {
            return _name;
        }

        //! Set Name
        inline void setName(const std::string& n)
        {
            _name = n;
        }

	protected:

        //! Reference to the resource manager
        ResourceManager& _rmanager;

        //! User-defined type
        signed int _type;

        //! User-defined name
        std::string _name;

    };

    //! Friendly name for Resource pointers.
    typedef boost::intrusive_ptr<Resource> ResourcePtr;

}// namespace phoenix

#endif // __PHRESOURCE_H__
