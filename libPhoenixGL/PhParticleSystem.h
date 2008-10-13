#ifndef PHPARTICLESYSTEM_H
#define PHPARTICLESYSTEM_H

#include "PhSceneManager.h"
#include <vector>

namespace phoenix
{

    class PhParticle;
    class PhEmitter;
    class PhEffector;

    //! Abstract Particle System
    /*!
        The particle system provides an abstract way to create, manage, and effect particles.
        The user creates new particles by overloading PhParticle, adds them to the system by
        overloading PhEmitter, and controls them using PhEffector.
        \sa PhParticle, PhEffector, PhEmitter
    */
    class PhParticleSystem : public PhSceneNode
    {

    public:

        //! Constructor
        /*!
            \param s Pointer to the Scene Manager
        */
        PhParticleSystem(PhSceneManager* s);
        ~PhParticleSystem();

        //! Add particle
        /*!
            Adds a particle to the management list
            \param p Pointer to the particle
            \sa removeParticle(), deleteParticles()
        */
        void addParticle(PhParticle* p);

        //! Add emitter
        /*!
            Adds an emitter to the management list
            \param e Pointer to the emitter
            \sa removeEmitter(), deleteEmitters()
        */
        void addEmitter(PhEmitter* e);

        //! Add effector
        /*!
            Adds an effector to the management list
            \param f Pointer to the effector
            \sa removeEffector(), deleteEffector()
        */
        void addEffector(PhEffector* f);

        //! Remove particle
        /*!
            Removes a particle from the management list (does not delete the pointer).
            \param p Pointer to the particle.
            \sa addParticle(), deleteParticles()
        */
        void removeParticle(PhParticle* p);

        //! Remove emitter
        /*!
            Removes an emitter from the management list (does not delete the pointer).
            \param f Pointer to the emitter
            \sa addEmitter(), deleteEmitter()
        */
        void removeEmitter(PhEmitter* e);

        //! Remove effector
        /*!
            Removes an effector from the management list (does not delete the pointer).
            \param f Pointer to the effector
            \sa addEffector(), deleteEffector()
        */
        void removeEffector(PhEffector* f);

        //! Delete particles
        /*!
            Deletes every particle in the list and clears it.
            \sa addParticle(), removeParticle()
        */
        void deleteParticles();

        //! Delete emitters
        /*!
            Deletes every emitter in the list and clears it.
            \sa addEmitter(), removeEmitter()
        */
        void deleteEmitters();

        //! Delete effectors
        /*!
            Deletes every effectors in the list and clears it.
            \sa addEffectors(), removeEffectors()
        */
        void deleteEffectors();

        //! Pre render
        /*!
            Calls all the effectors' preStep() call.
            \sa onRender(), onPostRender(), PhEffector::preStep()
        */
        void onPreRender();

        //! Render
        /*!
            Calls the draw() function for every particle.
            \sa onPreRender(), onPostRender(), PhParticle::draw()
        */
        void onRender();

        //! Post render
        /*!
            Calls the step() function for every emitter then every effector.
            \sa onPreRender, onRender, PhEffector::step(), PhEmitter::step()
        */
        void onPostRender();

        //! Get render system
        /*!
            Used by PhParticle to draw itself.
            \return A pointer to the render system
        */
        PhRenderSystem* getRenderSystem();

        //! Get scene manager
        /*!
            Used by PhParticle to get scene information
            \return A pointer to the scenemanager
        */
        PhSceneManager* getSceneManager();

        //! Get particle count
        /*!
            Used by PhEffector to know how many particles to effect.
            \return The current number of particles
        */
        int getParticleCount();

        //! Get particle list
        /*!
            Used by more advanced effectors that require direct access to the vector of particles.
            \return A pointer to the particle vector
            \sa getParticle()
        */
        std::vector<PhParticle*>* getParticleList();

        //! Get particle
        /*!
            Used by effectors to change the properties of a particular particle.
            \param n The index number of the particle
            \return A pointer to the particle at index n
            \sa getParticleCount(), getParticleList()
        */
        PhParticle* getParticle(unsigned int n);

    protected:

        PhSceneManager* smgr;
        std::vector<PhParticle*> particles;
        std::vector<PhEmitter*> emitters;
        std::vector<PhEffector*> effectors;

    private:

    };

}

#include "PhParticle.h"
#include "PhEmitter.h"
#include "PhEffector.h"

#endif // PHPARTICLESYSTEM_H
