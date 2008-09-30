#ifndef PHRENDERTEXTURE_H
#define PHRENDERTEXTURE_H

#include "PhRenderSystem.h"

namespace phoenix
{
    class PhRenderTexture
    {
    public:

        PhRenderTexture(PhRenderSystem* r);
        PhRenderTexture(PhRenderSystem* r, PhTexture* t);
        virtual ~PhRenderTexture();

        void setTexture(PhTexture* t);
        PhTexture* getTexture();

        void startRender();
        void endRender();

    protected:

        PhRenderSystem* system;
        PhTexture* texture;

    private:
    };
}

#endif // PHRENDERTEXTURE_H
