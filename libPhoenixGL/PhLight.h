#ifndef PHLIGHT_H
#define PHLIGHT_H

#include "PhLightManager.h"

namespace phoenix
{

    //! Pixel-based light.
    /*!
        This is a basic PhLight class that draw a texture as a light, this class was meant to be very minimalistic and
        we encourage users to overload this class to suit your needs. This class draw the light texture centered
        around it's position.
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
            This function draws the light, it is automatically called by PhLightManager. This class draw the light texture centered
			around it's position.
            \sa PhLightManager::generateBuffer()
        */
        void draw();

        //! Get texture.
        /*!
			Gets the texture of the light.
			\sa setTexture()
        */
        PhTexture* getTexture() const;

        //! Set texture.
        /*!
			Sets the texture of the light.
			\sa getTexture()
        */
        void setTexture(PhTexture* t);

        //! Get position.
        /*!
			Gets the position of the light. The texture is drawn centered on this position
			\sa setPosition()
        */
        const PhVector2d& getPosition() const;

        //! Set position.
        /*!
			Sets the position of the light. The texture is drawn centered on this position
			\sa setPosition()
        */
        void setPosition(const PhVector2d& p);

        //! Get color.
        /*!
			\sa setColor()
        */
        const PhColor& getColor() const;

        //! Set color.
        /*!
			\sa getColor()
        */
        void setColor(const PhColor& c);

        //! Get scale.
        /*!
			\sa setScale()
        */
		const PhVector2d& getScale() const;

		//! Set scale.
        /*!
			\sa getScale()
        */
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
