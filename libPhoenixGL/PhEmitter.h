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

#ifndef PHEMITTER_H
#define PHEMITTER_H

#include "PhParticleSystem.h"

namespace phoenix
{

    //! Abstract Particle Emitter
    /*!
        This is an abstract base class for creating particle emitters that create
        particles to be added to the particle system.
        \sa PhParticle, PhParticleSystem
    */
    class PhEmitter
    {
    public:

        //! Constructor
        /*!
            Default constructor, it sets partsys to NULL. In order for your emitter to work,
            you must add it to a particle system by calling PhParticleSystem::addEmiter() in
            your overloaded constructor.
        */
        PhEmitter(PhParticleSystem* p = NULL);

        //! Destructor
        /*!
            The default destructor calls PhParticleSystem::removeEmitter() if partsys is not null.
            Please note that if you delete an instance of this class without removing it from
            the particle system you will get a segfault.
        */
        virtual ~PhEmitter();

        //! Step
        /*!
            This function is called once every frame from PhParticleSystem::onPostRender(), this
            is where you put your code to create new particles.
            \sa PhParticleSystem::onPostRender()
        */
        virtual void step() = 0;

    protected:

        //! Pointer to the particle system
        PhParticleSystem* partsys;

    private:
    };

}

#endif // PHEMITTER_H
