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

#include "PhTileMap.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Allocates the map vector to store the proper amount of tiles
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::allocateTiles()
{
    //simply resize the vector to the proper size
    map.resize( int ( tilemapsize.getX() * tilemapsize.getY() ));
}

////////////////////////////////////////////////////////////////////////////////
//General constructor
////////////////////////////////////////////////////////////////////////////////

PhTileMap::PhTileMap(PhSceneManager* sc , PhVector2d s, PhVector2d ts /*tilesize*/, PhTexture* t /*texture*/, float d /*DEPTH*/)
	:  PhSceneNode(d), tilesize(ts), tilemapsize(s), texture(t), smgr(sc)
{
    allocateTiles();
    smgr->addNode((PhSceneNode*)this);
}

////////////////////////////////////////////////////////////////////////////////
//General destructor
////////////////////////////////////////////////////////////////////////////////

PhTileMap::~PhTileMap()
{
    map.clear(); //clear the map
    smgr->removeNode(this); //remove us from the scenegraph
}

////////////////////////////////////////////////////////////////////////////////
//setTile function that accesses the tiles as a one-dimensional array
//sets tile x to value t
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::setTile(int x, int t)
{
    if (x < tilemapsize.getX() * tilemapsize.getY())
    {
        map[x] = t;
    }
}

////////////////////////////////////////////////////////////////////////////////
//setTile function that accesses the tiles as a two-dimensional array
//sets tile pos(x,y) to value t
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::setTile(PhVector2d pos, int t)
{
    if (pos.getX() < tilemapsize.getX() && pos.getY() < tilemapsize.getY())
    {
        map[int ( (pos.getY()*tilemapsize.getX())+pos.getX() )] = t;
    }
}

////////////////////////////////////////////////////////////////////////////////
//getTile function that accesses the tiles as a one-dimensional array
//returns tile x
////////////////////////////////////////////////////////////////////////////////

int PhTileMap::getTile(int x)
{
    if (x < tilemapsize.getX() * tilemapsize.getY())
    {
        return map[x];
    }
    else
    {
        return -1;
    }
}

////////////////////////////////////////////////////////////////////////////////
//getTile function that accesses the tiles as a two-dimensional array
//returns tile pos(x,y)
////////////////////////////////////////////////////////////////////////////////

int PhTileMap::getTile(PhVector2d pos)
{
    if (pos.getX() < tilemapsize.getX() && pos.getY() < tilemapsize.getY())
    {
        return map[int ( (pos.getY()*tilemapsize.getX())+pos.getX() )];
    }
    else
    {
        return -1;
    }
}

////////////////////////////////////////////////////////////////////////////////
//sets and gets the tilemap size, pretty self explainitory
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::setMapSize(PhVector2d s)
{
    tilemapsize = s;
    allocateTiles(); //we need to make (or reduce) room for the new tiles, so allocate
}

PhVector2d PhTileMap::getMapSize()
{
    return tilemapsize;
}

////////////////////////////////////////////////////////////////////////////////
//set and get tile size, also easily understood
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::setTileSize(PhVector2d s)
{
    tilesize = s;
}

PhVector2d PhTileMap::getTileSize()
{
    return tilesize;
}

////////////////////////////////////////////////////////////////////////////////
//set and get the texture, simple.
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::setTexture(PhTexture* t)
{
    texture = t;
}

PhTexture* PhTileMap::getTexture()
{
    return texture;
}

////////////////////////////////////////////////////////////////////////////////
//load map function, simply loads the encoded tile map from the file named f
// ex: loadMap("map.mp");
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::loadMap(string f)
{

    FILE* file; //we need the file

    file = fopen(f.c_str(),"rb"); //open it
    if (file!=NULL)
    {
        //if it opened

        //first get the mapsize
        int tx,ty; //temp ints
        fread(&tx,sizeof(int),1,file);
        fread(&ty,sizeof(int),1,file);
        setMapSize(PhVector2d((float)tx,(float)ty)); //set the mapsize to the read values

        //now get the tilesize
        fread(&tx,sizeof(int),1,file);
        fread(&ty,sizeof(int),1,file);
        setTileSize(PhVector2d((float)tx,(float)ty)); //set the tilesize to the read values

        //now get the tiles themselves
        for (int i = 0; i < ( tilemapsize.getX() * tilemapsize.getY() ); i ++)
        {
            fread(&tx,sizeof(int),1,file);
            setTile(i,tx); //set the tile
        }
        fclose(file); //finally, close the file
    }

}

////////////////////////////////////////////////////////////////////////////////
//save map function, saves the tilemap in an encode file format to file f
//ex: saveMap("map.mp")
//
// File format information:
// first two bytes are the x of the mapsize
// second two bytes are the y of the mapsize
// third set of bytes is the x of the tilesize
// fourth set of bytes is the y of the tilesize
// remaining bytes each contain one tile
//
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::saveMap(string f)
{

    FILE* file;

    file = fopen(f.c_str(),"wb");

    if (file!=NULL)
    {
        //first two chars are the mapsize x
        int t = int(tilemapsize.getX());
        fwrite(&t,sizeof(int),1,file);
        //next two chars are the mapsize y
        t = int(tilemapsize.getY());
        fwrite(&t,sizeof(int),1,file);
        //next two chars are the tilesize x
        t = int(tilesize.getX());
        fwrite(&t,sizeof(int),1,file);
        //next two chars are the tilesize y
        t = int(tilesize.getY());
        fwrite(&t,sizeof(int),1,file);

        //now write the tile data
        for (int i = 0; i < ( tilemapsize.getX() * tilemapsize.getY() ); i ++)
        {
            t = getTile(i);
            fwrite(&t,sizeof(int),1,file);
        }
        fclose(file);
    }

}

////////////////////////////////////////////////////////////////////////////////
//Render, simply (or not so simply) draws the tilemap
////////////////////////////////////////////////////////////////////////////////

void PhTileMap::onPreRender()
{
    smgr->registerForRendering(this); //register us for rendering
};

void PhTileMap::onRender()
{

    for (int i = 0; i < tilemapsize.getY(); i++) //step through each tile
    {

        for (int j =0; j <tilemapsize.getX(); j++)
        {

            if (texture)
            {

                //texture manipulations
                glMatrixMode(GL_TEXTURE);

                glPushMatrix();

                float x,y;
                int frame = map[int ( (i*tilemapsize.getX())+j )]; //get the number of the current tile
                //move to the tile needed
                x =  floor((float)frame) * tilesize.getX();
                y = (floor(frame/floor((texture->getWidth()/tilesize.getX())))) * tilesize.getY();

                glTranslatef(  x / texture->getWidth() ,  y / texture->getHeight() ,0.0f);

                //now scale it to where we need it
                glScalef( (tilesize.getX()/texture->getWidth()), (tilesize.getY()/texture->getHeight()), 1.0f);

                //load the idenity
                glMatrixMode(GL_MODELVIEW);

                glPushMatrix();

                //Move the the center of the image
                glTranslatef( (j*tilesize.getX()) + (tilesize.getX()/2) , (i*tilesize.getY()) + (tilesize.getY()/2), depth);

                //Enable texturing
                glEnable(GL_TEXTURE_2D);

                texture->bindTexture();

                //colors
                PhColor color(255,255,255);
                GLuint colors[] = {color.toGLColor(), color.toGLColor(), color.toGLColor(), color.toGLColor()};
                //normals (each vector is (0.0f,0.0f,1.0f) )
                GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
                //vertices
                x = tilesize.getX() / 2.0f;
                y = tilesize.getY() / 2.0f;
                GLfloat vertices[] =  {-x,-y,0.0f,
                                       x,-y,0.0f,
                                       x,y,0.0f,
                                       -x,y,0.0f
                                      };
                //tcoords, little more difficult
                GLfloat tcoords[] = {0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};
                //indexlist, pretty simple
                GLuint indexlist[] = {0,1,3,1,2,3};

                //make the engine draw it
                smgr->getRenderSystem()->drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );

                //Disable texturing
                glDisable(GL_TEXTURE_2D);

                //Move back to the top of the screen
                glPopMatrix();

                glMatrixMode(GL_TEXTURE);

                glPopMatrix();

            }
        }
    }
}
