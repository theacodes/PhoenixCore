#ifndef PHOENIXAUX
#define PHOENIXAUX

#include "PhTileMap.h"
#include "PhPolygonCollision.h"

#include <boost/any.hpp>
#include <string>
#include <vector>
#include <map>

using namespace boost;
using namespace std;
using boost::any_cast;

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

#include <sstream>

namespace phoenix
{

    //! The aux library.
    /*! This is a collection of aux classes and functions
     to aid in the development of games using the phoenix library.
    */
    namespace aux
    {

        //! Random function.
        /*!
            \param low The lowest possible value.
            \param high The highest possible value.
            \return A pseudo random value between low and high.
        */
        ///random function
        template <class a_type> a_type random(a_type low,a_type high)
        {
            return (a_type(rand()) % (high - low + a_type(1)) + low);
        }

        //! Build collision data from tilemap.
        /*!
            Builds collision data from a tilemap, and adds it as static geometry to a collision handler.
            \param tilemap The tilemap to build the data from.
            \param colhandle The collision handler to add the data to.
            \param solidtiles A list of all the tile values that are solid.
            \param geometry A list of geometry: Each index of geometry corresponds to an index in solidtiles.
            Ex. if a tile was found that matched solidtiles[5], then geometry[5] would be added to the list of static geometry.
            \param type The type identified used by the call backs to determine what kind of objects these are, default 1.
            \sa phoenix::PhPolygonCollisionHandler, phoenix::PhTileMap, phoenix::PhStaticGeometry, phoenix::PhPolygon
        */
        void buildCollisionDataFromTileMap(PhTileMap* tilemap,PhPolygonCollisionHandler* colhandle,std::vector<PhVector2d> solidtiles,std::vector<PhPolygon> geometry,int type = 1);

        //! Global Variables.
        /*!
            This class offers a rather simple way for all objects to access a list of global variables.
        */
        class GlobalVariables
        {

        private:

            map<string, any> variables;

        public:

            //! Construct
            GlobalVariables();

            //! Destruct
            ~GlobalVariables();

            //! Set variable.
            /*!
                Sets the value with with given name to the given value.
                \param name Name of the variable.
                \param val Any data type that can be contained by boost::any.
            */
            void setVariable(string name, any val);

            //! Get variable.
            /*!
                Gets the variable with the given name.
                \param name The name of the variable.
                \return A boost::any containing the variable.
            */
            any getVariable(string name);

            //! Clear
            /*!
                Clears all the variables.
            */
            void clear();

        };
    }
}

#endif
