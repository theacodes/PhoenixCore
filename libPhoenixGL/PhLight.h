#ifndef PHLIGHT_H
#define PHLIGHT_H

#include "PhLightManager.h"

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
        PhLight(PhLightManager* l, PhTexture* t, PhVector2d p = PhVector2d(0,0), PhColor c = PhColor(255,255,255), PhVector2d s = PhVector2d(1.0f,1.0f) );
        virtual ~PhLight();

        //! Draw.
        /*!
            This function draws the light, it is automatically called by PhLightManager.
            \sa PhLightManager::generateBuffer()
        */
        void draw();

        PhTexture* getTexture() const;
        void setTexture(PhTexture* t);
        const PhVector2d& getPosition() const;
        void setPosition(const PhVector2d& p);
        const PhColor& getColor() const;
        void setColor(const PhColor& c);
		const PhVector2d& getScale() const;
        void setScale(const PhVector2d& s);

    protected:

        PhLightManager* lmgr;
        PhTexture* texture;
        PhVector2d position;
        PhColor color;
        PhVector2d scale;

    private:
    };
}

#endif // PHLIGHT_H
