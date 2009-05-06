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

#include "PhExtendedBackground.h"

using namespace phoenix;

//! Constuctor.
PhExtendedBackground::PhExtendedBackground(PhSceneManager* s, PhTexture* t, PhColor c, float d, bool xt, bool yt, PhVector2d sp, PhVector2d po, PhVector2d o)
	: PhSceneNode(s,d), source(t), color(c), tilex(xt), tiley(yt), position(po), offset(o), speed(sp)
{
}

void PhExtendedBackground::onPreRender()
{

    // Add to our offset.
    offset += speed;

    smanager->registerForRendering(this);

}

void PhExtendedBackground::onRender()
{

    glMatrixMode(GL_TEXTURE);

    glPushMatrix();

    glTranslatef(offset.getX(),offset.getY(),0.0f);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslatef(smanager->getView()->getPosition().getX()+position.getX(),smanager->getView()->getPosition().getY()+position.getY(),depth);

    glEnable(GL_TEXTURE_2D); //enable textures

    source->bindTexture(); //bind the texture.

    //get our width and height, and do tests to see if we're tiling.
    float width = smanager->getRenderSystem()->getScreenSize().getX();
    float height = smanager->getRenderSystem()->getScreenSize().getY();

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
    smanager->getRenderSystem()->drawIndexedTriangleList(vertices,normals,tcoords,colorarray,indexlist, 2 );

    //restore our matricies.

    glMatrixMode(GL_TEXTURE);

    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();


}
