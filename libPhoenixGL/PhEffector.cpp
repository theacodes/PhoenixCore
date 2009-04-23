#include "PhEffector.h"

using namespace phoenix;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Ctor
	just adds us to the partsys
*/
PhEffector::PhEffector(PhParticleSystem* p)
	: partsys(p)
{
    if(partsys != NULL)
		partsys->addEffector(this);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	Dtor
	just removes us.
*/
PhEffector::~PhEffector()
{
    if(partsys!=NULL)
        partsys->removeEffector(this);
}
