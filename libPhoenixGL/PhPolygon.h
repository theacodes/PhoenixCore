/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

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

	//forward decl of PhRect
	class PhRect;

    //! Polygon class.
    /*!
        This class represents polygons for drawing and collision detection.
		A polygon is basically any geometric object that can be represented by a
        triangle fan. Polygons are constructed with vertices, vertices can be
        defined as a vector from the center of the polygon or a vector from
        world coordinates.
        \sa phoenix::PhPolygonCollisionHandler
    */
    class PhPolygon
    {

    private:

        std::vector<PhVector2d> verts; //stores the list of verticies.
        PhVector2d pos; //the vector representing the position of this polygon
        float radius; //the magnitude of the largest vector in the polygon, use for circle-exclusions.

    public:

        //! Constructor.
        PhPolygon();

        //! Constructor.
        /*!
            \param a Vector representing the center (position) of the polygon.
        */
        PhPolygon(const PhVector2d& a);

        //! Implict conversion from PhRect
        /*!
			This constructor makes a polygon from the given rectangle.
        */
        PhPolygon(const PhRect& other);

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
        inline const PhVector2d& getPosition() const { return pos; }

        //! Set position.
        /*!
            Sets the center (position) of the polygon. Note that the vertices are relative to the center
            of the polygon, therefore changing this value will not effect the shape of the polygon.
            \param a The new center of the polygon.
            \sa getPosition()
        */
        inline void setPosition(const PhVector2d& a) { pos = a; }

        //! Add vertex.
        /*!
            Adds a vertex to the polygon. It doesn't take into account the position of
            the polygon, so PhVector2d(0.0f,10.0f) would push an vector that's 10 units
            above the polygon's center.
            \note This function does not sort the verticles by angle.
            \param a Vertex to add.
            \sa addPoint()
        */
        void addVertex(const PhVector2d& a);

        //! Add point.
        /*!
            Adds a point to the polygon by making a vertex based on the position of the point and the center
            point of the polygon. Add point does care about where the polygon is:
            it takes the vector between our position and where the point is and puts it
            onto the polygon. Basically, it translates world coordiates to polygon coordinates.
            \note This function does not sort the verticles by angle.
            \param a Point to add.
            \sa addVertex()
        */
        void addPoint(const PhVector2d& a);

        //! Get vertex count.
        /*!
            \return The current number of vertices in the polygon.
        */
        inline const unsigned int getVertexCount() const { return verts.size(); }

        //! Get vertex.
        /*!
            \param a The index of the vertex wanted.
            \return The vertex at index a.
        */
        inline const PhVector2d& getVertex(const unsigned int& a) const
        {
			if (a < verts.size())
			{
				return verts[a];
			}
			return *verts.end();
		}

        //! Set vertex.
        /*!
            \param a The index of the vertex to set.
            \param v What to set it to.
        */
        inline void setVertex(const unsigned int& a, const PhVector2d& v)
		{
			if (a < verts.size())
			{
				verts[a] = v;
			}
		}

        //! Get radius.
        /*!
            \return The magnitude of the largest vertex in the polygon.
        */
        inline const float& getRadius() const { return radius; }

        //! Rotate
        /*!
            Rotates the polygon by the given measurement.
            \param rad Angle measurement in Radians.
        */
        inline void rotate(const float& rad)
		{
			PhRotationMatrix m(rad);
			rotate(m);
		}

        //! Rotate (Matrix)
        /*!
            Rotates the polygon by the given matrix.
            \param m The matrix.
        */
        void rotate(const PhRotationMatrix& m);

        //! Array operator
        /*!
            This allows you to treat the polygon like a const array of vectors.
            \param a The index wanted.
            \return A vector representing the vertex at the given index.
        */
        inline const PhVector2d& operator[] (const unsigned int& a)
        {
            return getVertex(a);
        }

        const PhPolygon operator* (const float& scalar) const;
        const PhPolygon& operator*= (const float& scalar);
        const PhPolygon operator* (const PhRotationMatrix& other) const;
        const PhPolygon& operator*= (const PhRotationMatrix& other);

        const PhPolygon& operator= (const PhPolygon& other);
        const bool operator== (const PhPolygon& other) const;

    };

}

#include "PhRect.h"

#endif
