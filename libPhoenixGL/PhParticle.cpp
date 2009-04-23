#include "PhParticle.h"

using namespace phoenix;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	Just adds us to the list of particles
*/
PhParticle::PhParticle(PhParticleSystem* p, const int t)
	: partsys(p), type(t)
{
	if(partsys != NULL)
		partsys->addParticle(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Dtor
	Just removes us from the particle system.
*/
PhParticle::~PhParticle()
{
    if(partsys != NULL)
        partsys->removeParticle(this);
}

const int& PhParticle::getType()
{
    return type;
}

void PhParticle::setType(const int& t)
{
    type = t;
}

void PhParticle::destroy()
{
    delete this;
}
