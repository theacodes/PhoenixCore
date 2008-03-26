#ifndef PHPARTICLESYSTEM_H
#define PHPARTICLESYSTEM_H

#include "PhSceneManager.h"
#include <vector>

namespace phoenix
{

    class PhParticle;
    class PhEmitter;
    class PhEffector;

    class PhParticleSystem : public PhSceneNode
    {

    public:

        PhParticleSystem(PhSceneManager* s);
        virtual ~PhParticleSystem();

        void addParticle(PhParticle* p);
        void addEmitter(PhEmitter* e);
        void addEffector(PhEffector* f);

        void removeParticle(PhParticle* p);
        void removeEmitter(PhEmitter* e);
        void removeEffector(PhEffector* f);

        void deleteParticles();
        void deleteEmitters();
        void deleteEffectors();

        void onPreRender();
        void onRender();
        void onPostRender();

        PhRenderSystem* getRenderSystem();
        int getParticleCount();

        std::vector<PhParticle*>* getParticleList();
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
