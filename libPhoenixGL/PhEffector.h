#ifndef PHEFFECTOR_H
#define PHEFFECTOR_H

#include "PhParticleSystem.h"

namespace phoenix
{

    class PhEffector
    {
    public:

        PhEffector();
        virtual ~PhEffector();

        virtual void preStep();
        virtual void step();

    protected:

        PhParticleSystem* partsys;

    private:
    };

}

#endif // PHEFFECTOR_H
