#include "PhParticleSystem.h"

using namespace phoenix;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	The particle system behaves much like any
	other scene node, save for the fact that
	it also manages children.
*/
PhParticleSystem::PhParticleSystem(PhSceneManager* s)
	: PhSceneNode( s, 0.0f)
{
    particles.clear();
    emitters.clear();
    effectors.clear();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	Just deletes all particles, effectors and emitters.
*/
PhParticleSystem::~PhParticleSystem()
{
    deleteEmitters();
    deleteParticles();
    deleteEffectors();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Much like addSceneNode, this just adds a particle
	to the list
*/
void PhParticleSystem::addParticle(PhParticle* p)
{
    particles.push_back(p);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	And the removal of a particle.
*/
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Repeat the same concept for the next couple of functions.
*/
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	And once more for effectors.
*/
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	These functions delete every particle,
	emitter, or effector, respectively.
*/
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Pre render call we go through every effector
	and call preStep().
	We'll also register to render just like
	every other scene node
*/
void PhParticleSystem::onPreRender()
{

    for (unsigned int i = 0; i < effectors.size(); i++)
    {
        (effectors[i])->preStep();
    }

    smanager->registerForRendering(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Render call time. All we need to do is draw
	every particle.
*/
void PhParticleSystem::onRender()
{
    for (unsigned int i = 0; i < particles.size(); i++)
    {
        (particles[i])->draw();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Post render. All emitters are called,
	Then all effectors.
*/
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Member access functions.
*/

PhRenderSystem* PhParticleSystem::getRenderSystem() const
{
    return smanager->getRenderSystem();
}

const int PhParticleSystem::getParticleCount() const
{
    return particles.size();
}

vector<PhParticle*>* PhParticleSystem::getParticleList(){
    return &particles;
}

PhParticle* PhParticleSystem::getParticle(const unsigned int& n)
{
    return particles[n];
}
