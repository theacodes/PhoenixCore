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

#ifndef PHOENIXTILE
#define PHOENIXTILE

#include "PhSceneManager.h"
#include "PhSceneNode.h"

#include <vector>

using namespace std;

namespace phoenix
{

    //! Tile map.
    /*!
        A (somewhat) simple yet highly effective tilemap scene node. Once it is created it's self-contained.
        The scene manager takes care of rendering it, all you really have to do is create the map
        and load it.
    */
    class PhTileMap: public PhSceneNode
    {

    protected:

        //! Stores the values of the tiles.
        vector<char> map;

        //! Stores the size of each tile (in pixels).
        PhVector2d tilesize;

        //! Stores the size of the map itself (in tiles).
        PhVector2d tilemapsize;

        //! Texture that is used to peice together the map.
        PhTexture* texture;

        //! Allocates the map vector.
        void allocateTiles();

    public:

        //! Construct.
        /*!
            Builds a tilemap scene node.
            \param sc Pointer to the scene manager.
            \param s Size of the tilemap (in tiles).
            \param ts Size of each tile in the tilemap (in pixels).
            \param t Texture where the tiles will come from.
            \param d Depth of the tile map (default -100.0f).
        */
        PhTileMap(PhSceneManager* sc, PhVector2d s, PhVector2d ts, PhTexture* t, float d = -100.0f);

        //!Destruct
        virtual ~PhTileMap();

        //! Set tile (1D).
        /*!
            Sets the tile at the given index to the given value.
            \param x Index of the tile.
            \param t New value of the tile.
            \sa getTile()
        */
        void setTile(int x, int t);

        //! Set tile (2D).
        /*!
            Sets the tile at the given position to the given value.
            \param pos The position of the tile, ie <2,2> is the second tile from the top, second tile from the left.
            \param t The new value of the tile.
            \sa getTile()
        */
        void setTile(PhVector2d pos, int t);

        //! Get tile (1D)
        /*!
            \param x Index of the tile.
            \return The value of the tile at index X.
            \sa setTile()
        */
        int getTile(int x);

        //! Get tile (2D)
        /*!
            \param pos Position of the tile.
            \return The value of the tile at the given position.
            \sa setTile()
        */
        int getTile(PhVector2d pos);

        //! Set map size.
        /*!
            \param s The new size of the map, in tiles.
            \sa getMapSize()
        */
        void setMapSize(PhVector2d s);

        //! Get map size.
        /*!
            \return The size of the map, in tiles.
            \sa setMapSize()
        */
        PhVector2d getMapSize();

        //! Set tile size.
        /*!
            \param s The new size of the tiles, in pixels.
            \sa getTileSize()
        */
        void setTileSize(PhVector2d s);

        //! Get tile size.
        /*!
            \return The size of the tiles, in pixels.
            \sa setTileSize()
        */
        PhVector2d getTileSize();

        //! Set texture.
        /*!
            \param t The new tile sheet texture.
            \sa getTexture()
        */
        void setTexture(PhTexture* t);

        //! Get texture.
        /*!
            \return The tile sheet texture.
            \sa setTexture()
        */
        PhTexture* getTexture();

        //! Save map.
        /*!
            Saves the current tilemap to a file. <br>
            File format information: <br>
            first four bytes are the x of the mapsize. <br>
            second four  bytes are the y of the mapsize. <br>
            third set of four bytes is the x of the tilesize. <br>
            fourth set of four bytes is the y of the tilesize. <br>
            remaining sets of four bytes each contain one tile. <br>
            \param f Filename to save it to.
            \sa loadMap()
        */
        void saveMap(string f);

        //! Load map.
        /*!
            Loads a tilemap from a file.
            \param f The filename to load from.
            \sa saveMap()
        */
        void loadMap(string f);

        void onRender();
        void onPreRender();

    };

}

#endif
