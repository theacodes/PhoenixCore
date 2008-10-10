#ifndef PHLIGHT_H
#define PHLIGHT_H

#include "PhLightManager.h"

using namespace phoenix;

namespace phoenix
{

    //! Pixel-based light.
    /*!
        This is a basic PhLight class that draw a texture as a light, this class was meant to be very minimalistic and
        we encourage users to overload this class to suit your needs.
        \sa PhLightManager
    */
    class PhLight
    {

    public:

        //! Constructor.
        /*!
            \param l Pointer to the lightmanager that this light will belong to.
            \param t Texture that this light will draw.
            \param p Position of the light.
            \param c Color of the light.
            \param s Scale of the light.
        */
        PhLight(PhLightManager* l, PhTexture* t, PhVector2d p = PhVector2d(0,0), PhColor c = PhColor(255,255,255), float s = 1.0f);
        virtual ~PhLight();

        //! Draw.
        /*!
            This function draws the light, it is automatically called by PhLightManager.
            \sa PhLightManager::generateBuffer()
        */
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
