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

#ifndef PHOENIXPOLYC
#define PHOENIXPOLYC

#include "PhPolygon.h"
#include "PhPolygonCollisionObject.h"
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

namespace phoenix
{

    struct PhStaticGeometry;

    //! The polygon collision handler
    /*!
        Provides a simple and effective way to test for collisions using polygons and collision objects.
        \sa phoenix::PhCollisionObject
    */
    class PhPolygonCollisionHandler
    {

    protected:

        //! List of collision objects.
        /*!
            A list of all collision objects for testing.
            \sa addObject(), removeObject(), testCollisions(), isColliding()
        */
        vector<PhCollisionObject*> colobjs;

        //! List of static geometry.
        /*!
            A list of static geometry used for testing.
            \sa phoenix::PhStaticGeometry, addStaticGeometry(), removeStaticGeometry(), testCollisions(), testObjectCollidingStatic()
        */
        vector<PhStaticGeometry> level;

        void GetInterval(const PhPolygon P, const PhVector2d& xAxis, float& min, float& max);
        bool FindMTD(vector<PhVector2d>* xAxis, vector<float>* taxis, int iNumAxes, PhVector2d& N, float& t);
        bool IntervalIntersect(const PhPolygon A, const PhPolygon B, const PhVector2d& xAxis, float& taxis);
        bool PolygonCollision(PhPolygon A, PhPolygon B,PhVector2d& N,float& t);

    public:

        //! Construct.
        PhPolygonCollisionHandler();

        //! Destruct.
        ~PhPolygonCollisionHandler();

        //! Is colliding (polygon to polygon).
        /*!
            polygon to polygon, can be called if you don't want to use collision
            objects or just want some simple tests.
            \param A The polygon to test.
            \param B The polygon to test against.
            \return Collision data from this test.
        */
        PhCollisionData isColliding(PhPolygon A, PhPolygon B);

        //! Test static collisions.
        /*!
            Test a collision object against the static geometry and performs callback.
            Can be called directly, but this function is called by testObjectCollisions().
            \param A The object to test.
            \sa isColliding(), testCollisions(), phoenix::PhStaticGeometry, phoenix::PhCollisionObject
        */
        void testObjectCollidingStatic(PhCollisionObject* A);

        //! Is colliding (object to object).
        /*!
            Does collision testing between two objects, calls both callbacks for the objects.
            can be called directly, but this function is called by testObjectCollisions().
            \sa isColliding(), testCollisions(), phoenix::PhCollisionObject
        */
        bool isColliding(PhCollisionObject* A, PhCollisionObject* B);

        //! Test collisions.
        /*!
            This is the main function of the collision manager. This goes through all the collision objects
            and tests them against each other and the list of static geometry. It does callbacks and if used
            in conjuction with the scenemanager can do it nearly transparently.
            \sa phoenix::PhSceneManager::setCollisionHandler
        */
        void testCollisions();

        //! Add object
        /*!
            \param a The object to be added to the list.
            \sa removeObject(), phoenix::PhCollisionObject
        */
        void addObject(PhCollisionObject* a);

        //! Remove object
        /*!
            \param a The object to be removed from the list.
            \sa addObject(), phoenix::PhCollisionObject
        */
        void removeObject(PhCollisionObject* a);

        //! Add static geometry.
        /*!
            Adds static geometry given a polygon and a type. Usually a type of 1 is treated as a solid block and
            it is the defualt for this function.
            \param p The polygon to be added as static geometry.
            \param t The type.
            \sa removeStaticGeometry(), phoenix::PhStaticGeometry
        */
        void addStaticGeometry(PhPolygon p, int t = 1);

        //! Add static geometry.
        /*!
            \param g The static geometry to be added to the list.
            \sa removeStaticGeometry(), phoenix::PhStaticGeometry
        */
        void addStaticGeometry(PhStaticGeometry g);

        //! Remove static geometry.
        /*!
            \param g The static geometry to be removed.
            \sa addStaticGeometry(), clearStaticGeometry, phoenix::PhStaticGeometry
        */
        void removeStaticGeometry(PhStaticGeometry g);

        //! Get static geometry.
        /*!
            This returns a list of all the static geometry. This can be used to draw all the static geometry
            if you really wanted to.
            \return a std::vector list of all the static geometry.
        */
        vector<PhStaticGeometry> getStaticGeometry();

        //! Clear static geometry.
        /*!
            Removes all the static geometry from the list.
        */
        void clearStaticGeometry();

    };

    //! Static geomery
    /*!
        Static geometry does not have callbacks or userdata,
        it's simple a polygon and a type. This can be used for walls, or pretty much anything that doesn't
        really change. Also note that static geometry can be added and removed dynamically, so it isn't really
        static. I've also used it to represent grass (which can be cut and destroyed) in the zelda demo.
    */
    struct PhStaticGeometry
    {

        //! Polygon
        PhPolygon polygon;

        //! Type
        int type;

        PhStaticGeometry operator= (const PhStaticGeometry other)
        {
            polygon = other.polygon;
            type = other.type;
            return *this;
        }

        bool operator== (PhStaticGeometry other)
        {
            if (((other.polygon)==polygon)&&(other.type==type))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

}

#endif
