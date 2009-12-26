/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHRESOURCE_H__
#define __PHRESOURCE_H__

#include "ResourceManager.h"
#include "Droppable.h"

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
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
                : public boost::enable_shared_from_this<Resource>, public virtual Droppable
    {

    public:

        //! Destructor.
        /*!
            Should be overloaded and used to clean up anything allocated by this resource.
        */
        virtual ~Resource()
        {
        }

        //! Create
        /*!
        	This is a simple create function that just returns a smart pointer to a
        	new resource. It also adds the new resource to the given resource manager.
        	Derived classes can easily use this to construct themselves, but in order to
        	do so they must declare Resource as a friend class, because constructors
        	are private. They also must make their constructor only require a pointer to
        	a resource manager. Examples of doing this can be seen in Texture::create() and
			in BatchGeometry::create().
        */
        template <typename T>
        static boost::shared_ptr<T> create( ResourceManager& r )
        {
            boost::shared_ptr<T> newnode(new T(r));
            r.addResource( newnode->grab<Resource>() );
            return newnode->grab<T>();
        }

        //! Grab
        /*!
        	This should be used to grab a pointer to this resource.
        	Derived classes should call grab<DerivedResource>(). If it fails
        	to grab a valid pointer, or fails to cast, it will throw an exception.
        */
        template <typename T>
        inline boost::shared_ptr<T> grab()
        {
			return boost::static_pointer_cast<T,Resource>( shared_from_this() );
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
				_rmanager.removeResource( grab<Resource>() );
			}
		}

        //! Get resource manager.
        inline virtual ResourceManager& getResourceManager()
        {
            return _rmanager;
        }

        //! Get Type.
        inline virtual const signed int& getType() const
        {
            return _type;
        }

        //! Set Type.
        inline virtual void setType(const signed int& t)
        {
            _type = t;
        }

        //! Get Name
        inline virtual const std::string& getName() const
        {
            return _name;
        }

        //! Set Name
        inline virtual void setName(const std::string& n)
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

        //! Private constructor.
        /*!
            Constructs the resource and initializes its members. It is private, and all
            derived classes should have a private constructor and should use the create()
			method instead.
        */
        Resource( ResourceManager& rm, const signed int& t = 0 )
                : Droppable(), _rmanager(rm), _type(t), _name("None")
        {
        }

    };

}// namespace phoenix

#endif // __PHRESOURCE_H__
