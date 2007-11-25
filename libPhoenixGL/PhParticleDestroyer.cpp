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

#include "PhParticleDestroyer.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Construct
////////////////////////////////////////////////////////////////////////////////

PhParticleDestroyer::PhParticleDestroyer(PhSceneManager* s,PhParticleEmitter* e,PhRect r) : PhParticleEffector(s,e)
{
    rect=r;
}

////////////////////////////////////////////////////////////////////////////////
// Functions for rectangle stuff
////////////////////////////////////////////////////////////////////////////////

int PhParticleDestroyer::getX()
{
    return rect.getX();
}

void PhParticleDestroyer::setX(int a)
{
    rect.setX(a);
}

int PhParticleDestroyer::getY()
{
    return rect.getY();
}

void PhParticleDestroyer::setY(int a)
{
    rect.setY(a);
}

int PhParticleDestroyer::getWidth ()
{
    return rect.getWidth();
}

void PhParticleDestroyer::setWidth(int a)
{
    rect.setWidth(a);
}

int PhParticleDestroyer::getHeight ()
{
    return rect.getHeight();
}

void PhParticleDestroyer::setHeight(int a)
{
    rect.setHeight(a);
}

////////////////////////////////////////////////////////////////////////////////
// on pre render, this does most of the work
////////////////////////////////////////////////////////////////////////////////

void PhParticleDestroyer::onPreRender()
{

    PhParticle* temp;

    for(int i=0; i<emitter->getParticles(); i++)
    {

        temp = emitter->getParticle(i);

        if(temp != 0)
        {

            if(temp->x > rect.getX())
            {

                if(temp->y > rect.getY())
                {

                    if(temp->y < ( rect.getY() + rect.getHeight() ) )
                    {

                        if(temp->x < ( rect.getX() + rect.getWidth() ) )
                        {

                            emitter->deleteParticle(i);
                            i-=1;

                        }

                    }

                }

            }

        }

    }

}
