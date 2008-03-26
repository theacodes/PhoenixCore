#include "PhParticle.h"

using namespace phoenix;

PhParticle::PhParticle()
{
    partsys = NULL;
    type = 0;
}

PhParticle::~PhParticle()
{
    if(partsys != NULL)
    {
        partsys->removeParticle(this);
    }
}

int PhParticle::getType()
{
    return type;
}

void PhParticle::setType(int t)
{
    type = t;
}

void PhParticle::draw()
{

}

void PhParticle::destroy()
{
    delete this;
}
