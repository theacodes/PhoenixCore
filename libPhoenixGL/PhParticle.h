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

#ifndef PHPARTICLE_H
#define PHPARTICLE_H

#include "PhParticleSystem.h"

namespace phoenix
{

    //! Abstract Particle
    /*!
        This class is a simple abstract base class for deriving particles. By overloading this class
        the user can create particles that can do anything they can imagine, even create other
        particles.
        \sa PhParticleSystem, PhEffector, PhEmitter
    */
    class PhParticle
    {
    public:

        //! Constructor
        /*!
            The default constructor initializes the type to zero and the partsys pointer to null.
            In order for your particle to be managed by the partsys, you must set the pointer and
            call PhParticleSystem::addParticle(). This is done automatically by the default
            constructor.
            \param p The particle system that will manage this particle.
            \param t The particle type
            \sa getType(), setType()
        */
        PhParticle( PhParticleSystem* p = NULL, const int t = 0);

        //! Destructor
        /*!
            The default destructor calls PhParticleSystem::removeParticle() if partsys is not NULL.
            Usually you will not need to overload this, but you may want to overload destroy(). Please
            be aware that if you delete the particle without removing it from the particle system,
            your program will segfault.
            \sa destroy()
        */
        virtual ~PhParticle();

        //! Draw function
        /*!
            This function is called once every frame by the particle system during it's onRender() call, in this function you
            do all the particle behavior, including drawing itself.
            \sa destroy()
        */
        virtual void draw() = 0;

        //! Destroy function
        /*!
            This function is the prefered method of destroying a particle. By defualt this just
            makes the particle delete itself. However, overloading this can allow you to create
            other particles then this particle dies.
            \sa draw()
        */
        virtual void destroy();

        //! Get user-defined type
        /*!
            This returns the type of the particle that was set by the user (defualt 0).
            \sa type
        */
        inline const int& getType() const { return type; }

        //! Set user-defined type
        /*!
            This set the type of the particle (defualt 0).
            \sa type
        */
        void setType(const int& i) { type = i; }

    protected:

        //! Pointer to the particle system
        PhParticleSystem* partsys;

        //! User-defined type
        int type;

    private:
    };

}

#endif // PHPARTICLE_H
