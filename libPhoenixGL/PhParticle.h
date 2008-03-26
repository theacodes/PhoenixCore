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
            The defualt constructor initializes the type to zero and the partsys pointer to null.
            In order for your particle to be managed by the partsys, you must set the pointer and
            call PhParticleSystem::addParticle().
            \sa getType(), setType()
        */
        PhParticle();

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
        virtual void draw();

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
        int getType();

        //! Set user-defined type
        /*!
            This set the type of the particle (defualt 0).
            \sa type
        */
        void setType(int i);

    protected:

        //! Pointer to the particle system
        PhParticleSystem* partsys;

        //! User-defined type
        int type;

    private:
    };

}

#endif // PHPARTICLE_H
