#ifndef PHPARTICLE_H
#define PHPARTICLE_H

#include "PhParticleSystem.h"

namespace phoenix
{

    class PhParticle
    {
    public:

        PhParticle();
        virtual ~PhParticle();

        virtual void draw();
        virtual void destroy();

        int getType();
        void setType(int i);

    protected:

        PhParticleSystem* partsys;
        int type;

    private:
    };

}

#endif // PHPARTICLE_H
