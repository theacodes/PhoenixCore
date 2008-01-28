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

#include "PhParticleSystem.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct: Needs a pointer to the scenemanager. other arguments are image,
//x, y, and free on destroy.
////////////////////////////////////////////////////////////////////////////////

PhParticleEmitter::PhParticleEmitter(PhSceneManager* s, PhTexture* i, PhParticleType pt, int p, float d, bool c)
{
    //set all over out variables
    image=i;
    fod=c;
    smgr=s;
    system=smgr->getRenderSystem();
    depth=d;
    //tell the scenemanager that we exist.
    smgr->addNode((PhSceneNode*)this);
    //Particles
    particlecount=0;
    maxparts = p;
    partype = pt;
}

////////////////////////////////////////////////////////////////////////////////
//Destruct
////////////////////////////////////////////////////////////////////////////////

PhParticleEmitter::~PhParticleEmitter()
{

    //delete our image
    if(fod&&image!=NULL)
    {
        delete image;
    }

    //remove ourselves from the node list
    smgr->removeNode(this);

    //delete all of the particles
    for(int i = 0; i < particlecount; i++)
    {
        if(particles[i]!=NULL)
        {
            delete particles[i];
        }
    }
    particles.clear();
}

////////////////////////////////////////////////////////////////////////////////
//This sets the render system, this should automatically be taken care of.
////////////////////////////////////////////////////////////////////////////////

void PhParticleEmitter::setRenderSystem(PhRenderSystem* sys)
{
    system=sys;
}

////////////////////////////////////////////////////////////////////////////////
//Gets the number of particles
////////////////////////////////////////////////////////////////////////////////

int PhParticleEmitter::getParticles()
{
    return particlecount;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set the max number of particles.
////////////////////////////////////////////////////////////////////////////////

int PhParticleEmitter::getMaxParticles()
{
    return maxparts;
}

void PhParticleEmitter::setMaxParticles(int a)
{
    maxparts = a;
}

////////////////////////////////////////////////////////////////////////////////
//This returns a pointer to a particle
////////////////////////////////////////////////////////////////////////////////

PhParticle* PhParticleEmitter::getParticle(int a)
{
    if(a<particlecount)
    {
        return particles[a];
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//Deletes a particle
////////////////////////////////////////////////////////////////////////////////

void PhParticleEmitter::deleteParticle(int a)
{
    if(a<particlecount)
    {
        //delete it
        delete particles[a];
        //erase it form the list
        particles.erase(particles.begin()+a);
        //duh
        particlecount-=1;
    }
}

////////////////////////////////////////////////////////////////////////////////
//Get and set the max  and min hspeed & vspeed
////////////////////////////////////////////////////////////////////////////////

int PhParticleEmitter::getMaxHSpeed()
{
    return partype.maxhs;
}

void PhParticleEmitter::setMaxHSpeed(int a)
{
    partype.maxhs = a;
}

int PhParticleEmitter::getMaxVSpeed()
{
    return partype.maxvs;
}

void PhParticleEmitter::setMaxVSpeed(int a)
{
    partype.maxvs = a;
}

int PhParticleEmitter::getMinHSpeed()
{
    return partype.minhs;
}

void PhParticleEmitter::setMinHSpeed(int a)
{
    partype.minhs = a;
}

int PhParticleEmitter::getMinVSpeed()
{
    return partype.minvs;
}

void PhParticleEmitter::setMinVSpeed(int a)
{
    partype.minvs = a;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set the max and min life
////////////////////////////////////////////////////////////////////////////////

int PhParticleEmitter::getMaxLife()
{
    return partype.maxlife;
}

void PhParticleEmitter::setMaxLife(int a)
{
    partype.maxlife = a;
}

int PhParticleEmitter::getMinLife()
{
    return partype.minlife;
}

void PhParticleEmitter::setMinLife(int a)
{
    partype.minlife = a;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set the max and min rotation speed
////////////////////////////////////////////////////////////////////////////////

float PhParticleEmitter::getMaxRotationSpeed()
{
    return partype.maxrs;
}

void PhParticleEmitter::setMaxRotationSpeed(float a)
{
    partype.maxrs = a;
}

float PhParticleEmitter::getMinRotationSpeed()
{
    return partype.minrs;
}

void PhParticleEmitter::setMinRotationSpeed(float a)
{
    partype.minrs = a;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set the max and min color stuff
////////////////////////////////////////////////////////////////////////////////

int PhParticleEmitter::getMinAlpha()
{
    return partype.minalpha;
}

void PhParticleEmitter::setMinAlpha(int a)
{
    partype.minalpha = a;
}

int PhParticleEmitter::getMinRed()
{
    return partype.minred;
}

void PhParticleEmitter::setMinRed(int a)
{
    partype.minred = a;
}

int PhParticleEmitter::getMinGreen()
{
    return partype.minalpha;
}

void PhParticleEmitter::setMinGreen(int a)
{
    partype.mingreen = a;
}

int PhParticleEmitter::getMinBlue()
{
    return partype.minblue;
}

void PhParticleEmitter::setMinBlue(int a)
{
    partype.minblue = a;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set the max and min rotation speed
////////////////////////////////////////////////////////////////////////////////

float PhParticleEmitter::getMaxScale()
{
    return partype.maxscale;
}

void PhParticleEmitter::setMaxScale(float a)
{
    partype.maxscale = a;
}

float PhParticleEmitter::getMinScale()
{
    return partype.minscale;
}

void PhParticleEmitter::setMinScale(float a)
{
    partype.minscale = a;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set image functions
////////////////////////////////////////////////////////////////////////////////

bool PhParticleEmitter::setTexture(PhTexture* img)
{
    if(img!=NULL)
    {
        image=img;
        return true;
    }
    else
    {
        return false;
    }
}

PhTexture* PhParticleEmitter::getTexture()
{
    return image;
}

////////////////////////////////////////////////////////////////////////////////
//This sets free on destroy to true of false. Free on destroy removes the image
//when the node is destroyed.
////////////////////////////////////////////////////////////////////////////////

void PhParticleEmitter::setFod(bool a)
{
    fod=a;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//Constructor
////////////////////////////////////////////////////////////////////////////////

PhParticleEffector::PhParticleEffector(PhSceneManager* s, PhParticleEmitter* e)
	: smgr(s), emitter(e), PhSceneNode(emitter->getDepth())
{
    //add ourselves to the node list
    smgr->addNode((PhSceneNode*)this);
}

////////////////////////////////////////////////////////////////////////////////
//Destructor
////////////////////////////////////////////////////////////////////////////////

PhParticleEffector::~PhParticleEffector()
{
    //remove ourselves from the node list
    smgr->removeNode(this);
}


