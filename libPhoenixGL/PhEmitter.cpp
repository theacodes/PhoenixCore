#include "PhEmitter.h"

using namespace phoenix;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	Just adds us to the particle system
*/
PhEmitter::PhEmitter(PhParticleSystem* p)
	: partsys(p)
{
    if(partsys != NULL )
		partsys->addEmitter(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Dtor
	Just removes us from the particle system
*/
PhEmitter::~PhEmitter()
{
    if(partsys!=NULL)
        partsys->removeEmitter(this);
}
