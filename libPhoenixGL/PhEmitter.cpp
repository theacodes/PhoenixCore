#include "PhEmitter.h"

using namespace phoenix;

PhEmitter::PhEmitter()
{
    partsys = NULL;
}

PhEmitter::~PhEmitter()
{
    if(partsys!=NULL){
        partsys->removeEmitter(this);
    }
}

void PhEmitter::step()
{

}
