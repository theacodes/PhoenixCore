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

#include "PhBoxEmitter.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct: Needs a pointer to the scenemanager. other arguments are image,
//x, y, and free on destroy.
////////////////////////////////////////////////////////////////////////////////

PhBoxEmitter::PhBoxEmitter(PhSceneManager* s, PhTexture* i, PhRect rt, PhParticleType pt, int p = 1, float d=0.0f, bool c=true) 
	: PhParticleEmitter(s,i,pt,p,d,c), rect(rt)
{
}

////////////////////////////////////////////////////////////////////////////////
//Destruct
////////////////////////////////////////////////////////////////////////////////

PhBoxEmitter::~PhBoxEmitter()
{
}

////////////////////////////////////////////////////////////////////////////////
// Functions for rectangle stuff
////////////////////////////////////////////////////////////////////////////////

int PhBoxEmitter::getX()
{
    return (int)rect.getX();
}

void PhBoxEmitter::setX(int a)
{
    rect.setX((float)a);
}

int PhBoxEmitter::getY()
{
    return (int)rect.getY();
}

void PhBoxEmitter::setY(int a)
{
    rect.setY((float)a);
}

int PhBoxEmitter::getWidth ()
{
    return (int)rect.getWidth();
}

void PhBoxEmitter::setWidth(int a)
{
    rect.setWidth((float)a);
}

int PhBoxEmitter::getHeight ()
{
    return (int)rect.getHeight();
}

void PhBoxEmitter::setHeight(int a)
{
    rect.setHeight((float)a);
}

////////////////////////////////////////////////////////////////////////////////
//PreRender function, this is called before everything is render, and should
//only be called by the scenemanager
////////////////////////////////////////////////////////////////////////////////

void PhBoxEmitter::onPostRender()
{

    //This moves all of our particles
    for(int i=0; i<particlecount; i++)
    {

        particles[i]->x += particles[i]->hspeed;    //hspeed
        particles[i]->y += particles[i]->vspeed;    //vspeed
        particles[i]->rot += particles[i]->rotspeed;//rotation speed
        particles[i]->lifeleft -= 1;                //life

        //if it's time for the particle to die
        if(particles[i]->lifeleft < 0 )
        {

            deleteParticle(i);
            i-=1;

        }

    }


}

////////////////////////////////////////////////////////////////////////////////
//Render call, this is called only if the node was registered. This should only
//be called by the scenemanager
////////////////////////////////////////////////////////////////////////////////

void PhBoxEmitter::onRender()
{
    //if our image exists
    if(image!=NULL)
    {
        //step through the list of particles and draw them
        for(int i=0; i<particlecount; i++)
        {
            system->drawTexture(image,PhVector2d((float)particles[i]->x,(float)particles[i]->y),depth,particles[i]->rot,particles[i]->scale,PhColor(
                                    partype.minred + ((particles[i]->lifeleft)*255/partype.maxlife),
                                    partype.mingreen + ((particles[i]->lifeleft)*255/partype.maxlife),
                                    partype.minblue + ((particles[i]->lifeleft)*255/partype.maxlife),
                                    partype.minalpha + ((particles[i]->lifeleft)*255/partype.maxlife)
                                ));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//PostRender call, this is called after everything is rendered. This should
//only be called by the scenenmanager.
////////////////////////////////////////////////////////////////////////////////

void PhBoxEmitter::onPreRender()
{

    //Add new particles if needed
    while( particlecount < maxparts)
    {

        PhParticle* temp = new PhParticle;                          //make a new particles
        temp->x = random<int>((int)rect.getX(),int(rect.getX()+rect.getWidth()));                                          //x
        temp->y = random<int>((int)rect.getY(),int(rect.getY()+rect.getHeight()));                                          //y
        temp->hspeed = random<int>(partype.minhs,partype.maxhs);                   //hspeed
        temp->vspeed = random<int>(partype.minvs,partype.maxvs);                   //vspeed
        temp->lifeleft = random<int>(partype.minlife,partype.maxlife);            //max life
        temp->rot = 0.0f;                                           //rotation
        temp->rotspeed = float(random(int(partype.minrs*10.0),int(partype.maxrs*10.0)))/10.0f;    //rotation speed
        temp->scale = float(random(int(partype.minscale*10.0),int(partype.maxscale*10.0)))/10.0f;
        particles.push_back(temp);                                  //add it to the list
        particlecount+=1;                                           //duh
    }

    //register for rendering
    smgr->registerForRendering(this);

}
