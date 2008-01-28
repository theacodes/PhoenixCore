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

#include "PhGravityEffector.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Construct
////////////////////////////////////////////////////////////////////////////////

PhGravityEffector::PhGravityEffector(PhSceneManager* s,PhParticleEmitter* e,int xx, int yy,int a,int b) 
	: PhParticleEffector(s,e), x(xx), y(yy), force(a), reach(b*b)
{
}

////////////////////////////////////////////////////////////////////////////////
// Functions for rectangle stuff
////////////////////////////////////////////////////////////////////////////////

int PhGravityEffector::getX()
{
    return x;
}

void PhGravityEffector::setX(int a)
{
    x = a;
}

int PhGravityEffector::getY()
{
    return y;
}

void PhGravityEffector::setY(int a)
{
    y = a;
}

////////////////////////////////////////////////////////////////////////////////
//Set and get force
////////////////////////////////////////////////////////////////////////////////

int PhGravityEffector::getForce ()
{
    return force;
}

void PhGravityEffector::setForce(int a)
{
    force=a;
}

////////////////////////////////////////////////////////////////////////////////
//Set and get reach
////////////////////////////////////////////////////////////////////////////////

int PhGravityEffector::getReach()
{
    return reach;
}

void PhGravityEffector::setReach(int a)
{
    reach=a*a;
}

////////////////////////////////////////////////////////////////////////////////
// on pre render, this does most of the work
////////////////////////////////////////////////////////////////////////////////

void PhGravityEffector::onPreRender()
{

    PhParticle* temp;

    for(int i=0; i<emitter->getParticles(); i++)
    {

        temp = emitter->getParticle(i);

        if(temp != 0)
        {

            if( getDistance(x,y,temp->x,temp->y) < reach ){

                if(temp->x < x)
                {
                    temp->hspeed+=force;
                }

                if(temp->y < y)
                {
                    temp->vspeed+=force;
                }

                if(temp->y > y )
                {
                    temp->vspeed-=force;
                }

                if(temp->x > x )
                {
                    temp->hspeed-=force;
                }

            }

        }

    }

}
