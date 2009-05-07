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
        overloading PhEmitter, and controls them using PhEffector. It's a fairly high-level
        way of doing advanced efffects.
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

        //! Destructor
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
        inline PhRenderSystem* getRenderSystem() const { return smanager->getRenderSystem(); }

		//! Get particle count
        /*!
            Used by PhEffector to know how many particles to effect.
            \return The current number of particles
        */
        inline const int getParticleCount() const { return particles.size(); }

        //! Get particle list
        /*!
            Used by more advanced effectors that require direct access to the vector of particles.
            \return A pointer to the particle vector
            \sa getParticle()
        */
        inline std::vector<PhParticle*>* getParticleList() { return &particles; }

        //! Get particle
        /*!
            Used by effectors to change the properties of a particular particle.
            \param n The index number of the particle
            \return A pointer to the particle at index n
            \sa getParticleCount(), getParticleList()
        */
        inline PhParticle* getParticle(const unsigned int& n) const { return particles[n]; }

    protected:

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
