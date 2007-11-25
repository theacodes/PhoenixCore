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
#include "SDL/SDL_OpenGL.h" //SDL's openGL header
#include "PhColor.h"
#include "PhTextureManager.h"

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
        unsigned char* data;

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
        PhTexture(PhTextureManager* t, int a, int b);

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
        void setTexture(GLuint text);

        //! Get texture.
        /*!
            \return The openGL texture identifier stored by this object.
        */
        GLuint getTexture();

        //! Set name.
        /*!
            Sets a name for this texture, can be used by the user to keep track of textures.
            \param nm The name of the string (It is usually the filename of the texture loaded).
            \sa setName(), phoenix::PhTextureManager
        */
        void setName(std::string nm);

        //! Get name.
        /*!
            Gets the name of this texture.
            \return A string containing the name of this texture.
            \sa getName(), phoenix::PhTextureManager
        */
        std::string getName();

        //! Set modified.
        /*!
            Overrides the modifed value.
            \param a The new modified value.
            \sa getModified()
        */
        void setModified(bool a);

        //! Get modified.
        /*!
            Returns true if the texture has been modified by the setPixel() command.
            \return True if the texture has been modified.
            \sa setModified(), setPixel()
        */
        bool getModified();

        //! Set width.
        /*!
            Changes the width of the current texture (Power of 2).
            \param var The new width.
            \sa getWidth()
        */
        void setWidth(int var);

        //! Get width.
        /*!
            \return The current width of the texture.
            \sa setWidth()
        */
        int getWidth();

        //! Set height.
        /*!
            Changes the height of the current texture (Power of 2).
            \param var The new height.
            \sa getHeight()
        */
        void setHeight(int var);

        //! Get height.
        /*!
            \return The current height of the texture.
            \sa setHeight()
        */
        int getHeight();

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
        */
        void setPixel(int x, int y, PhColor col);

        //! Get pixel.
        /*!
            Gives the color of the given pixel. lockTexture() must be called before this is possible.
            \param x X value of the pixel.
            \param y Y value of the pixel.
            \return The color of the pixel at position (x,y)
            \sa setPixel(), lockTexture()
        */
        PhColor getPixel(int x, int y);

        //! Bind texture.
        /*!
            Binds this texture as the current openGL texture use for drawing.
            \return True if it was able to bind.
        */
        bool bindTexture();

    };

}

#endif
