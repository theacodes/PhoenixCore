/*

Copyright (c) 2008, Jonathan Wayne Parrott, Denzel Morris.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

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
        inline PhTexture* getTexture() const { return texture; }

        //! Set texture.
        /*!
			Sets the texture of the light.
			\sa getTexture()
        */
        inline void setTexture(PhTexture* t) { texture = t; }

        //! Get position.
        /*!
			Gets the position of the light. The texture is drawn centered on this position
			\sa setPosition()
        */
        inline const PhVector2d& getPosition() const { return position; }

        //! Set position.
        /*!
			Sets the position of the light. The texture is drawn centered on this position
			\sa setPosition()
        */
        inline void setPosition(const PhVector2d& p) { position = p; }

        //! Get color.
        /*!
			\sa setColor()
        */
        inline const PhColor& getColor() const { return color; }

        //! Set color.
        /*!
			\sa getColor()
        */
        inline void setColor(const PhColor& c) { color = c; }

        //! Get scale.
        /*!
			\sa setScale()
        */
		inline const PhVector2d& getScale() const { return scale; }

		//! Set scale.
        /*!
			\sa getScale()
        */
        inline void setScale(const PhVector2d& s) { scale = s; }

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
