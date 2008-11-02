#include "PhVertexLightSystem.h"

using namespace phoenix;

PhVertexLightSystem::PhVertexLightSystem()
{

}

PhVertexLightSystem::~PhVertexLightSystem()
{
    clearLights();
}

void PhVertexLightSystem::addLight(PhVertexLight* l)
{
    lights.push_back(l);
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
