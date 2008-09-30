#ifndef PHLIGHT_H
#define PHLIGHT_H

#include "PhLightManager.h"

using namespace phoenix;

namespace phoenix
{
    class PhLight
    {

    public:

        PhLight(PhLightManager* l, PhTexture* t, PhVector2d position = PhVector2d(0,0), PhColor c = PhColor(255,255,255), float s = 1.0f);
        virtual ~PhLight();

        void draw();

        PhTexture* getTexture();
        void setTexture(PhTexture* t);
        PhVector2d getPosition();
        void setPosition(PhVector2d p);
        PhColor getColor();
        void setColor(PhColor c);
        float getScale();
        void setScale(float s);

    protected:

        PhLightManager* lmgr;
        PhTexture* texture;
        PhVector2d position;
        PhColor color;
        float scale;

    private:
    };
}

#endif // PHLIGHT_H
