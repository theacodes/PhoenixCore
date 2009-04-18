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

#include "PhBackground.h"

using namespace phoenix;

PhBackground::PhBackground(PhSceneManager* s, PhTexture* t, const PhColor& c, const float& d)
	: PhSceneNode(d), color(c), smgr(s), texture(t)
{
    smgr->addNode((PhSceneNode*)this);
}

PhBackground::~PhBackground()
{
    smgr->removeNode(this);
}

void PhBackground::setColor(const PhColor& c)
{
    color = c;
}

const PhColor& PhBackground::getColor() const
{
    return color;
}

void PhBackground::setTexture(PhTexture* t)
{
    texture = t;
}

PhTexture* PhBackground::getTexture() const
{
    return texture;
}

void PhBackground::onPreRender()
{
    smgr->registerForRendering(this);
}

void PhBackground::onRender()
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glTranslatef(smgr->getView()->getX(),smgr->getView()->getY(),depth);

    glEnable(GL_TEXTURE_2D); //enable textures

    texture->bindTexture(); //bind the texture.

    //colors
    GLuint colorarray[] = {color.toGLColor(), color.toGLColor(), color.toGLColor(), color.toGLColor()};
    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
    //vertices
    GLfloat vertices[] =  {0.0f,0.0f,0.0f,
                           smgr->getRenderSystem()->getScreenSize().getX(),0.0f,0.0f,
                           smgr->getRenderSystem()->getScreenSize().getX(),smgr->getRenderSystem()->getScreenSize().getY(),0.0f,
                           0.0f,smgr->getRenderSystem()->getScreenSize().getY(),0.0f
                          };
    //tcoords
    float tx = (smgr->getRenderSystem()->getScreenSize().getX())/(texture->getWidth());
    float ty = (smgr->getRenderSystem()->getScreenSize().getY())/(texture->getHeight());
    GLfloat tcoords[] = {
        0.0f,0.0f,
        tx,0.0f,
        tx,ty,
        0.0f,ty};
    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    smgr->getRenderSystem()->drawIndexedTriangleList(vertices,normals,tcoords,colorarray,indexlist, 2 );

    glPopMatrix();

}

void PhBackground::onPostRender(){}

