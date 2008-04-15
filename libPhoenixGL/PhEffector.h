#ifndef PHEFFECTOR_H
#define PHEFFECTOR_H

#include "PhParticleSystem.h"

namespace phoenix
{

    //! Abstract particle effector class
    /*!
        This is an abstract base class for creating particle effectors.
        \sa PhParticleSystem(), PhParticle(), PhEmitter()
    */
    class PhEffector
    {
    public:

        //! Constructor
        /*!
            Default constructor, it sets partsys to NULL. In order for your effector to work,
            you must add it to a particle system by calling PhParticleSystem::addEffector() in
            your overloaded constructor.
        */
        PhEffector();

        //! Destructor
        /*!
            The default destructor calls PhParticleSystem::removeEffector() if partsys is not null.
            Please note that if you delete an instance of this class without removing it from
            the particle system you will get a segfault.
        */
        virtual ~PhEffector();

        //! Pre step function
        /*!
            This function is called once per frame in PhParticleSystem::onPreRender().
            \sa step()
        */
        virtual void preStep();

        //! Post step function
        /*!
            This function is called once per frame in PhParticleSystem::onPostRender().
            \sa preStep()
        */
        virtual void step();

    protected:

        //! Pointer to the particle system
        PhParticleSystem* partsys;

    private:
    };

}

#endif // PHEFFECTOR_H
