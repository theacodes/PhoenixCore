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
        PhEmitter();

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
        virtual void step();

    protected:

        //! Pointer to the particle system
        PhParticleSystem* partsys;

    private:
    };

}

#endif // PHEMITTER_H
