#include "PhLightSystem.h"

PhLightSystem::PhLightSystem()
{

}

PhLightSystem::~PhLightSystem()
{
    clearLights();
}

void PhLightSystem::addLight(PhLight* l)
{
    lights.push_back(l);
}

void PhLightSystem::removeLight(PhLight* l)
{
    for (unsigned int i = 0; i < lights.size(); i++)
    {
        if (lights[i] == l)
        {
            lights.erase(lights.begin()+i,lights.begin()+i+1);
        }
    }
}

void PhLightSystem::clearLights()
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

void PhLightSystem::setLights()
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
