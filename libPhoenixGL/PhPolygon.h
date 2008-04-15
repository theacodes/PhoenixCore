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

#ifndef PHOENIXPOLY
#define PHOENIXPOLY

#include <vector>
#include "PhVector2d.h"
#include "PhRotationMatrix.h"

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

namespace phoenix
{
    //! Polygon class.
    /*!
        This class represents polygons for collision detection. They can be used for
        drawing primitives. a polygon is basically any geometric object that can be represented by a
        triangle fan. the vertices are basically the definitions of the vectors that
        make up the triangle fan.
        \sa phoenix::PhPolygonCollisionHandler
    */
    class PhPolygon
    {

    private:

        std::vector<PhVector2d> verts; //stores the list of verticies.
        int vertcount; //the number of verticles, this isn't need !
        PhVector2d pos; //the vector representing the position of this polygon
        float radius; //the magnitude of the largest vector in the polygon, usef for circle-exclusions. see
        //PhPolygonCollisionHandle sources.

    public:

        //! Constructor.
        PhPolygon();

        //! Constructor.
        /*!
            \param a Vector representing the center (position) of the polygon.
        */
        PhPolygon(PhVector2d a);

        //! Destructor.
        ~PhPolygon();

        //! Clear.
        /*!
            Removes all the vertices from the polygon.
        */
        void clear();

        //! Get position.
        /*!
            \return The center of the polygon (The position).
            \sa setPosition()
        */
        PhVector2d getPosition();

        //! Set position.
        /*!
            Sets the center (position) of the polygon. Note that the vertices are relative to the center
            of the polygon, therefore changing this value will not effect the shape of the polygon.
            \param a The new center of the polygon.
            \sa getPosition()
        */
        void setPosition(PhVector2d a);

        //! Push vertex.
        /*!
            Adds a vertex to the polygon. It doesn't care were the polygon is, so PhVector2d(0.0f,10.0f) would
            push an vector that's 10 units above the polygon's center.
            \param a Vertex to add.
            \sa pushPoint()
        */
        void pushVertex(PhVector2d a);

        //! Push point.
        /*!
            Adds a point to the polygon by making a vertex based on the position of the point and the center
            point of the polygon. Push point does care about where the polygon is:
            it takes the vector between our position and where the point is and puts it
            onto the polygon.
            \param a Point to add.
            \sa pushVertex()
        */
        void pushPoint(PhVector2d a);

        //! Get vertex count.
        /*!
            \return The current number of vertices in the polygon.
        */
        int getVertexCount();

        //! Get vertex.
        /*!
            \param a The index of the vertex wanted.
            \return The vertex at index a.
        */
        PhVector2d getVertex(int a);

        //! Set vertex.
        /*!
            \param a The index of the vertex to set.
            \param v What to set it to.
        */
        void setVertex(int a, PhVector2d v);

        //! Get radius.
        /*!
            \return The magnitude of the largest vertex in the polygon.
        */
        float getRadius();

        //! Rotate
        /*!
            Rotates the polygon by the given measurement.
            \param rad Angle measurement in Radians.
        */
        void rotate(float rad);

        //! Rotate (Matrix)
        /*!
            Rotates the polygon by the given matrix.
            \param m The matrix.
        */
        void rotate(PhRotationMatrix& m);

        //! Array operator
        /*!
            This allows you to treat the polygon like a const array of vectors.
            \param a The index wanted.
            \return A vector representing the vertex at the given index.
        */
        inline PhVector2d operator[] (int a)
        {
            return getVertex(a);
        }

        PhPolygon operator* (float scalar);
        PhPolygon& operator*= (float scalar);
        PhPolygon operator* (PhRotationMatrix& other);
        PhPolygon& operator*= (PhRotationMatrix& other);

        PhPolygon& operator= (const PhPolygon other);
        bool operator== (PhPolygon other);

    };

}

#endif
