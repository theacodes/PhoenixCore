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

#include "PhVertexLightSystem.h"

using namespace phoenix;

PhVertexLightSystem::PhVertexLightSystem()
{

}

PhVertexLightSystem::~PhVertexLightSystem()
{
    clearLights();
}

void PhVertexLightSystem::removeLight(PhVertexLight* l)
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i] == l)
        {
            lights.erase(lights.begin()+i,lights.begin()+i+1);
        }
    }
}

void PhVertexLightSystem::clearLights()
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i]!=NULL)
        {
            delete lights[i];
            i--;
        }
    }
    lights.clear();
}

void PhVertexLightSystem::setLights()
{
    // save the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // reset the lights
    for (unsigned int i = 0; i < 8; i++)
    {
        glDisable(GL_LIGHT0+i);
    }

    for (unsigned int i = 0; i < lights.size(); i++)
    {
        lights[i]->setLight(i);
    }

    //restore the matrix
    glPopMatrix();
}
