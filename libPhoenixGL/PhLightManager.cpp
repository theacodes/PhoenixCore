/*

Copyright (c) 2008, Jonathan Wayne Parrott, Denzel Morris.

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

#include "PhLightManager.h"

using namespace phoenix;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	Just make our render target
*/
PhLightManager::PhLightManager(PhSceneManager* s, PhVector2d ts) :
	smgr(s)
{
    PhTexture* target = new PhTexture(smgr->getRenderSystem()->getTextureManager(), (int)ts.getX(), (int)ts.getY());
    rtexture = new PhRenderTexture(smgr->getRenderSystem(), target);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Dtor
	Just delete all the lights.
*/
PhLightManager::~PhLightManager()
{
	if( rtexture!=NULL ) delete rtexture;
    clearLights();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Add light
*/
void PhLightManager::addLight(PhLight* l)
{
    lights.push_back(l);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Remove light
*/
void PhLightManager::removeLight(PhLight* l)
{
    for (unsigned int i = 0; i < lights.size(); ++i)
    {
        if (lights[i] == l)
        {
            lights.erase(lights.begin()+i,lights.begin()+i+1);
        }
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Clear lights
	Deletes every light in the list.
*/
void PhLightManager::clearLights()
{
    for (unsigned int i = 0; i < lights.size(); ++i)
    {
        if (lights[i]!=NULL)
        {
            delete lights[i];
            --i;
        }
    }
    lights.clear();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Generate the light buffer.
*/
void PhLightManager::generateBuffer()
{

	//start rendering to our render texture
    rtexture->startRender();

    //set the blend mode
    smgr->getRenderSystem()->setBlendMode(GL_SRC_ALPHA,GL_ONE);

	// iterate through the lights and draw them all.
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i]!=NULL)
        {
            lights[i]->draw();
        }
    }

    // restore the blend mode.
    smgr->getRenderSystem()->setDefaultBlendMode();

    // End our rendering.
    rtexture->endRender();

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Render the buffer.
*/
void PhLightManager::renderBuffer( float depth )
{

	// This blend mode allows lights.
    smgr->getRenderSystem()->setBlendMode(GL_DST_COLOR, GL_ZERO);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    glScalef(1.0f/smgr->getView()->getScale().getX(),1.0f/smgr->getView()->getScale().getY(),1.0f);

    glTranslatef(smgr->getView()->getPosition().getX(),smgr->getView()->getPosition().getY(),depth);

    glEnable(GL_TEXTURE_2D); //enable textures

    rtexture->getTexture()->bindTexture(); //bind the texture.

    //get our width and height
    float width = smgr->getRenderSystem()->getScreenSize().getX();
    float height = smgr->getRenderSystem()->getScreenSize().getY();

    //colors
    GLuint color = PhColor(255,255,255,255).toGLColor();
    GLuint colorarray[] = {color,color,color,color};

    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};

    //vertices
    GLfloat vertices[] =  {0.0f,0.0f,0.0f,
                           width,0.0f,0.0f,
                           width,height,0.0f,
                           0.0f,height,0.0f
                          };
    GLfloat tcoords[] = {
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f};

    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    smgr->getRenderSystem()->drawIndexedTriangleList(vertices,normals,tcoords,colorarray,indexlist, 2 );

    //restore our matricies.

    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    smgr->getRenderSystem()->setDefaultBlendMode();

}
