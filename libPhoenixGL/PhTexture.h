/*

Copyright (c) 2007, Jonathan Wayne Parrott.

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

#ifndef PHOENIXTEX
#define PHOENIXTEX

#include <string>
#include "GL/gl.h"
#include "PhColor.h"
#include "PhTextureManager.h"
#include "PhVector2d.h"

namespace phoenix
{

    //! Texture class.
    /*!
        Provides a wrapper to OpenGL textures.
    */
    class PhTexture
    {

    protected:

        //! Pointer to the OpenGL Texture.
        GLuint texture;

        //! Pointer to the texture manager.
        PhTextureManager* txtmgr;

        //! Width of the texture.
        int width;

        //! Height of the texture.
        int height;

        //! Data used during texture manipulation.
        /*!
            \sa lockTexture(),unlockTexture(),setPixel(),getPixel()
        */
        GLubyte* data;

        //! The texture's name.
        std::string name;


    public:

        //! Constructor.
        /*!
            Simple constructor that makes a texture object that contains no texture.
            \param t A pointer to the texture manager (for garbage collection).
        */
        PhTexture(PhTextureManager* t);

        //! Constructor.
        /*!
            Constructor that creates a texture object with the given dimensions.
            \param t A pointer to the texture manager (for garbage collection).
            \param a The width of the texture.
            \param b The height of the texture.
        */
        PhTexture(PhTextureManager* t, const int& a, const int& b);

        //! Destructor.
        /*!
            Destroys this texture object and deletes the OpenGL texture.
        */
        ~PhTexture();

        //! Set texture.
        /*!
            Sets the OpenGL texture identifier of this texture object. Should never be called directly by the user, but
            can be used by custom image loading routines.
            \param text An OpenGL texture identifier.
            \sa getTexture()
        */
        inline void setTextureId(const GLuint& text) { texture = text; }

        //! Get texture.
        /*!
            \return The openGL texture identifier stored by this object.
        */
        inline const GLuint& getTexture() const { return texture; }

        //! Set name.
        /*!
            Sets a name for this texture, can be used by the user to keep track of textures.
            \param nm The name of the string (It is usually the filename of the texture loaded).
            \sa setName(), phoenix::PhTextureManager
        */
        inline void setName(const std::string& nm) { name = nm; }

        //! Get name.
        /*!
            Gets the name of this texture.
            \return A string containing the name of this texture.
            \sa getName(), phoenix::PhTextureManager
        */
        inline const std::string& getName() const { return name; }

        //! Set width.
        /*!
            Changes the width of the current texture (Power of 2).
            \param var The new width.
            \sa getWidth()
        */
        inline void setWidth(const int& var) { width = var; }

        //! Get width.
        /*!
            \return The current width of the texture.
            \sa setWidth()
        */
        inline const int& getWidth() const { return width; }

        //! Set height.
        /*!
            Changes the height of the current texture (Power of 2).
            \param var The new height.
            \sa getHeight()
        */
        inline void setHeight(const int& var) { height = var; }

        //! Get height.
        /*!
            \return The current height of the texture.
            \sa setHeight()
        */
        inline const int& getHeight() const { return height; }

        //! Get size.
        /*!
            \return The current size of the texture
            \sa setSize()
        */
        inline const PhVector2d getSize() const { return PhVector2d( width, height ); }

        //! Set size.
        /*!
            Sets the current size of the texture.
            \note Be careful
            \sa getSize()
        */
        inline void setSize(const PhVector2d& sz)
        {
			width = int(sz.getX());
			height = int(sz.getY());
		}

        //! Lock texture.
        /*!
            Locks the texture. Before getPixel() or setPixel() can be called, this must be called first.
            \return True if it was able to lock the texture.
            \sa unlockTexture(), setPixel(), getPixel()
        */
        bool lockTexture();

        //! Unlock texture.
        /*!
            Unlocks the texture. It transfers all the texture data back into video memory. This must be called
            after the user is done modifying the texture with setPixel().
            \sa lockTexture(), setPixel(), getPixel()
        */
        void unlockTexture();

        //! Set pixel.
        /*!
            Changes a pixel to the given color. lockTexture() must be called before this is possible.
            \param x X value of the pixel.
            \param y Y value of the pixel.
            \param col The new color of the pixel.
            \sa getPixel(), lockTexture()
            \note This function takes a long time, as it reconstructs the texture.
        */
        void setPixel(const int& x, const int& y, const PhColor& col);

        //! Get pixel.
        /*!
            Gives the color of the given pixel. lockTexture() must be called before this is possible.
            \param x X value of the pixel.
            \param y Y value of the pixel.
            \return The color of the pixel at position (x,y)
            \sa setPixel(), lockTexture()
        */
        const PhColor getPixel(const int& x, const int& y) const;

        //! Bind texture.
        /*!
            Binds this texture as the current openGL texture use for drawing.
            \return True if it was able to bind.
        */
        bool bindTexture();

    };

}

#endif
