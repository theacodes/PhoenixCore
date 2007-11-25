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

#ifndef PHOENIXTEXM
#define PHOENIXTEXM

#include <string>
#include "SDL/SDL_OpenGL.h" //SDL's openGL header
#include "PhColor.h"
#include <vector>

using namespace std;

namespace phoenix
{

    class PhTexture;

    //! Texture manager.
    /*!
        This class takes care of cleaning up all textures after the program exits.
        \sa PhTexture, PhRenderSystem
    */
    class PhTextureManager
    {

    protected:

        //! List of all the textures currently loaded.
        vector<PhTexture*> texturelist;

    public:

        //! Constructor.
        PhTextureManager();

        //! Destructor.
        /*!
            When this object is destroyed (It will be automatically destroyed when the render
            system is destroyed). It deletes all the textures.
        */
        ~PhTextureManager();

        //! Add texture.
        /*!
            Adds a texture to the list.
            \param texture A pointer to the texture to be stored.
            \sa removeTexture()
        */
        void addTexture(PhTexture* texture);

        //! Remove texture.
        /*!
            Removes a texture to the list. Does not actually delete the texture.
            \param texture A pointer to the texture to be stored.
            \sa addTexture()
        */
        void removeTexture(PhTexture* texture);

        //! Delete textures.
        /*!
            Deletes all the textures in the list.
        */
        void deleteTextures();

        //! Find texture.
        /*!
            \param n The name of the texture you want to find.
            \return A pointer to the texture if found, else NULL.
        */
        PhTexture* findTexture(std::string n);

        //! Find texture.
        /*!
            \param n The GL id of the texture you want to find.
            \return A pointer to the texture if found, else NULL.
        */
        PhTexture* findTexture(GLuint n);

    };

}

#include "PhTexture.h"

#endif
