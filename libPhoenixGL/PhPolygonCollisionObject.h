/*

Copyright (c) 2007, Jonathan Wayne Parrott.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef PHPOLYGONCOLLISIONOBJECT_H
#define PHPOLYGONCOLLISIONOBJECT_H

#include "PhVector2d.h"
#include "PhPolygon.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

namespace phoenix
{

    struct PhCollisionData;

    //! Callback typedef.
    /*!
        Defines the type of collision callbacks. When the collision manager detects a collision
        it calls the callbacks of the involved objects and passes it a phoenix::PhCollisionData
        object representing details from the collision. For non-class members you can simply cast
        a function pointer to this type (ie PhObjectCallback(function)). However, for member
        functions (which is usually the case) you can use boost which provides an elegant way
        to do so (ie PhObjectCallback(boost::bind(&Class::function, this, _1)) ).
        \sa phoenix::PhCollisionObject, phoenix::PhPolygonCollisionHandler
    */
    typedef function<void (PhCollisionData data)> PhObjectCallback;

    //! Collision object.
    /*!
        Provides a structed way to store collision objects for later testing.
        \sa phoenix::PhPolygonCollisionHandler
    */
    class PhCollisionObject
    {

    protected:

        //! User data.
        /*!
            This is a void pointer, using RTTI you can make this store a pointer to a class and cast it
            in order to make changes.
            \sa RTTI
        */
        void* userdata;


        //! Type.
        /*!
            An integer representing the type of this object. This can be used to gather what this object
            is (A solid wall, a bullet, an enemy, etc.).
            \sa userdata
        */
        int RTTI;

        //! Polygon.
        /*!
            The polygon used by the collision handle to test for collisions.
        */
        PhPolygon* poly;

        //! Callback.
        /*!
            The callback of this collision object, can be null.
            \sa phoenix::PhObjectCallback
        */
        PhObjectCallback callback;

    public:

        //! Construct.
        PhCollisionObject();

        //! Construct.
        /*!
            \param p The polygon.
            \param r The type.
            \param c The callback.
            \param o The user data.
        */
        PhCollisionObject(PhPolygon* p, int r = 0, PhObjectCallback c = NULL, void * o = NULL);

        //! Set user data.
        /*!
            \param o The new user data.
            \sa getUserData(), userdata
        */
        void setUserData(void* o);

        //! Get user data.
        /*!
            \return The user data.
            \sa setUserData(), userdata
        */
        void* getUserData();

        //! Set callback.
        /*!
            \param c The new callback.
            \sa getCallback(), phoenix::PhObjectCallback
        */
        void setCallback( PhObjectCallback c );

        //! Get callback.
        /*!
            \return The callback.
            \sa setCallback(), phoenix::PhObjectCallback
        */
        PhObjectCallback getCallback();

        //! Set type.
        /*!
            \param r The new type.
            \sa getType(), RTTI
        */
        void setType(int r);

        //! Get type.
        /*!
            \return The type.
            \sa setType(), RTTI
        */
        int getType();

        //! Set polygon.
        /*!
            \param p The new polygon.
            \sa getPolygon()
        */
        void setPolygon(PhPolygon* p);

        //! Get polygon.
        /*!
            \return The polygon.
            \sa setPolygon()
        */
        PhPolygon* getPolygon();

        bool operator== (const PhCollisionObject other);

    };

    //! Collision data.
    /*!
        This struct provides information about a collision.
    */
    struct PhCollisionData
    {
        //! True if a collision occured.
        bool collision;

        //! The first object.
        /*!
            This is the first object involved in collisions. This will always be the object whose callback
            was given this data.
            \sa objB
        */
        PhCollisionObject objA;

        //! The second object.
        /*!
            This is always the object that you collided with.
            \sa objA
        */
        PhCollisionObject objB;

        //! Normal of collision.
        /*!
            This is the normal of the collision. Along with sepmag it can be used to separate this object
            from this other by adding (sep*sepmag) to the polygon's position.
            \sa sepmag
        */
        PhVector2d sep;

        //! Magnitude of separation.
        /*!
            This stores the magnitude of the vector needed to separate the polygons. Along with sep it can
            be used to separate the objects.
            \sa sep
        */
        float sepmag;
    };

}


#endif // PHPOLYGONCOLLISIONOBJECT_H
