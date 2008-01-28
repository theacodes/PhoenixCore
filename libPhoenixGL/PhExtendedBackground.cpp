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

#include "PhExtendedBackground.h"

using namespace phoenix;

//! Constuctor.
/*!
\param s Pointer to the scenemanager.
\param t Texture to use.
\param c Color to use. Default white.
\param d Depth. Default -100.0f.
\param xt Horizontal tile. Default true.
\param yt Vertical tile. Default true.
\param sp Scroll speed. Defualt [0,0].
\param o Texture offset. Default [0,0].
*/
PhExtendedBackground::PhExtendedBackground(PhSceneManager* s, PhTexture* t, PhColor c, float d, bool xt, bool yt, PhVector2d sp, PhVector2d po, PhVector2d o)
	: PhSceneNode(d), smgr(s), source(t), color(c), tilex(xt), tiley(yt), position(po), offset(o), speed(sp)
{
    //register us with the scenemanager
    smgr->addNode( this );

}

PhExtendedBackground::~PhExtendedBackground()
{
    smgr->removeNode( this );
}

//! Set color function.
/*!
Sets the color used to colorize the texture.
\param c The new color.
\sa getColor()
*/
void PhExtendedBackground::setColor(PhColor c)
{
    color = c;
}

//! Get color function.
/*!
Get the current color used to colorize the texture.
\return The current color.
\sa setColor()
*/
PhColor PhExtendedBackground::getColor(){
    return color;
}

//! Set texture function.
/*!
Sets the texture used by this node.
\param t The new texture.
\sa getTexture()
*/
void PhExtendedBackground::setTexture(PhTexture* t)
{
    source = t;
}

//! Get texture function.
/*!
Gets the current texture used by this node.
\return The current texture.
\sa setTexture()
*/
PhTexture* PhExtendedBackground::getTexture()
{
    return source;
}

//! Set horizontal tile.
/*!
Sets whether of not to tile this background horizontally.
\param b Tile boolean.
\sa setVerticalTile()
*/
void PhExtendedBackground::setHorizontalTile(bool b)
{
    tilex = b;
}

//! Set vertical tile.
/*!
Sets whether of not to tile this background vertically.
\param b Tile boolean.
\sa setVerticalTile()
*/
void PhExtendedBackground::setVerticalTile(bool b)
{
    tiley = b;
}

//! Set position.
/*!
Sets the position of this background.
\note Position is relative to the top-left corner of the VIEW, it is a relative position, not an absolute one.
\param v New position.
\sa getPosition()
*/
void PhExtendedBackground::setPosition(PhVector2d v)
{
    position = v;
}

//! Get position.
/*!
\note Position is relative to the top-left corner of the VIEW, it is a relative position, not an absolute one.
\return The current position of the background.
\sa setPosition()
*/
PhVector2d PhExtendedBackground::getPosition()
{
    return position;
}

//! Set texture offset.
/*!
Sets the texture offset of the background. The texture offset is a normalized value and simply modifies
The texture coords of the background. Can be use to achieve effects such as paralax and scrolling backgrounds.
\param v The new texture offset.
\sa getTextureOffset()
*/
void PhExtendedBackground::setTextureOffset(PhVector2d v)
{
    offset = v;
}

//! Get texture offset.
/*!
\return The texture offset.
\sa setTextureOffset()
*/
PhVector2d PhExtendedBackground::getTextureOffset(){
    return offset;
}

//! Set scroll speed.
/*!
Using scroll speed the background will automatically change its texture offset every frame,
creating the illusion of moving backgrounds.
\param v The new speed;
\sa setTextureOffset(), getScrollSpeed()
*/
void PhExtendedBackground::setScrollSpeed(PhVector2d v)
{
    speed = v;
}

//! Get scroll speed.
/*!
    \return The current scroll speed.
    \sa setTextureOffset(), setScrollSpeed()
*/
PhVector2d PhExtendedBackground::getScrollSpeed()
{
    return speed;
}

void PhExtendedBackground::onPreRender()
{

    // Add to our offset.
    offset += speed;

    smgr->registerForRendering(this);

}

void PhExtendedBackground::onRender()
{

    glMatrixMode(GL_TEXTURE);

    glPushMatrix();

    glTranslatef(offset.getX(),offset.getY(),0.0f);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslatef(smgr->getView()->getX()+position.getX(),smgr->getView()->getY()+position.getY(),depth);

    glEnable(GL_TEXTURE_2D); //enable textures

    source->bindTexture(); //bind the texture.

    //get our width and height, and do tests to see if we're tiling.
    float width = smgr->getRenderSystem()->getScreenSize().getX();
    float height = smgr->getRenderSystem()->getScreenSize().getY();

    if(!tilex){
        width = (float)source->getWidth();
    }

    if(!tiley){
        height = (float)source->getHeight();
    }

    //colors
    GLuint colorarray[] = {color.toGLColor(), color.toGLColor(), color.toGLColor(), color.toGLColor()};

    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};

    //vertices
    GLfloat vertices[] =  {0.0f,0.0f,0.0f,
                           width,0.0f,0.0f,
                           width,height,0.0f,
                           0.0f,height,0.0f
                          };
    //tcoords
    float tx = (width)/(source->getWidth());
    float ty = (height)/(source->getHeight());
    GLfloat tcoords[] = {
        0.0f,0.0f,
        tx,0.0f,
        tx,ty,
        0.0f,ty};

    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    smgr->getRenderSystem()->drawIndexedTriangleList(vertices,normals,tcoords,colorarray,indexlist, 2 );

    //restore our matricies.

    glMatrixMode(GL_TEXTURE);

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();


}

void PhExtendedBackground::onPostRender()
{

}
