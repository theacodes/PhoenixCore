#include "PhParticleSystem.h"

using namespace phoenix;

PhParticleSystem::PhParticleSystem(PhSceneManager* s)
{
    smgr = s;
    smgr->addNode((PhSceneNode*)this);
    depth = 0.0f;
    particles.clear();
    emitters.clear();
}

PhParticleSystem::~PhParticleSystem()
{
    deleteEmitters();
    deleteParticles();
    smgr->removeNode(this);
}

void PhParticleSystem::addParticle(PhParticle* p)
{
    particles.push_back(p);
}

void PhParticleSystem::removeParticle(PhParticle* p)
{
    for (unsigned int i = 0; i < particles.size(); i++)
    {
        if (particles[i] == p)
        {
            particles.erase(particles.begin()+i,particles.begin()+i+1);
        }
    }
}

void PhParticleSystem::addEmitter(PhEmitter* e)
{
    emitters.push_back(e);
}

void PhParticleSystem::removeEmitter(PhEmitter* e)
{
    for (unsigned int i = 0; i < emitters.size(); i++)
    {
        if (emitters[i] == e)
        {
            emitters.erase(emitters.begin()+i,emitters.begin()+i+1);
        }
    }
}

void PhParticleSystem::addEffector(PhEffector* f)
{
    effectors.push_back(f);
}

void PhParticleSystem::removeEffector(PhEffector* f)
{
    for (unsigned int i = 0; i < effectors.size(); i++)
    {
        if (effectors[i] == f)
        {
            effectors.erase(effectors.begin()+i,effectors.begin()+i+1);
        }
    }
}

void PhParticleSystem::deleteParticles()
{
    for (unsigned int i = 0; i < particles.size(); i++)
    {
        delete particles[i];
    }
    particles.clear();
}

void PhParticleSystem::deleteEmitters()
{
    for (unsigned int i = 0; i < emitters.size(); i++)
    {
        delete emitters[i];
    }
    emitters.clear();
}

void PhParticleSystem::deleteEffectors()
{
    for (unsigned int i = 0; i < effectors.size(); i++)
    {
        delete effectors[i];
    }
    effectors.clear();
}

void PhParticleSystem::onPreRender()
{

    for (unsigned int i = 0; i < effectors.size(); i++)
    {
        (effectors[i])->preStep();
    }

    smgr->registerForRendering(this);
}

void PhParticleSystem::onRender()
{
    for (unsigned int i = 0; i < particles.size(); i++)
    {
        (particles[i])->draw();
    }
}

void PhParticleSystem::onPostRender()
{
    for (unsigned int i = 0; i < emitters.size(); i++)
    {
        (emitters[i])->step();
    }
    for (unsigned int i = 0; i < effectors.size(); i++)
    {
        (effectors[i])->step();
    }
}

PhRenderSystem* PhParticleSystem::getRenderSystem()
{
    return smgr->getRenderSystem();
}

int PhParticleSystem::getParticleCount()
{
    return particles.size();
}

vector<PhParticle*>* PhParticleSystem::getParticleList(){
    return &particles;
}

PhParticle* PhParticleSystem::getParticle(unsigned int n)
{
    return particles[n];
}
