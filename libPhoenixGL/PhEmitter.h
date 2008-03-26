#ifndef PHEMITTER_H
#define PHEMITTER_H

#include "PhParticleSystem.h"

namespace phoenix
{

    class PhEmitter
    {
    public:

        PhEmitter();
        virtual ~PhEmitter();

        virtual void step();

    protected:

        PhParticleSystem* partsys;

    private:
    };

}

#endif // PHEMITTER_H
