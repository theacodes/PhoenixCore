#include "PhEffector.h"

using namespace phoenix;

PhEffector::PhEffector()
{
    partsys = NULL;
}

PhEffector::~PhEffector()
{
    if(partsys!=NULL)
    {
        partsys->removeEffector(this);
    }
}

void PhEffector::preStep()
{

}

void PhEffector::step()
{

}
