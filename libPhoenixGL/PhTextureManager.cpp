/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

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

#include "PhTextureManager.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Construct and Destruct
////////////////////////////////////////////////////////////////////////////////

PhTextureManager::PhTextureManager()
{
}

PhTextureManager::~PhTextureManager()
{
    deleteTextures();
}

////////////////////////////////////////////////////////////////////////////////
// add and remove texture
////////////////////////////////////////////////////////////////////////////////

void PhTextureManager::addTexture(PhTexture* texture)
{
    texturelist.push_back(texture);
}

void PhTextureManager::removeTexture(PhTexture* texture)
{
    for (unsigned int i = 0; i < texturelist.size(); i++)
    {
        if (texturelist[i] == texture)
        {
            texturelist.erase(texturelist.begin()+i,texturelist.begin()+i+1);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// deletes all the textures.
////////////////////////////////////////////////////////////////////////////////

void PhTextureManager::deleteTextures()
{
    for (unsigned int i = 0; i < texturelist.size(); ++i)
    {
        if (texturelist[i]!=NULL)
        {
            delete texturelist[i];
            --i;
        }
    }
    texturelist.clear();
}


//! Find texture.
/*!
    \param n The name of the texture you want to find.
    \return A pointer to the texture if found, else NULL.
*/
PhTexture* PhTextureManager::findTexture(const std::string& n)
{
    for (unsigned int i=0;i<texturelist.size();i++)
    {
        if ( (texturelist[i]!=NULL) && (texturelist[i]->getName() == n) )
        {
            return texturelist[i];
        }
    }
    return NULL;
}

//! Find texture.
/*!
    \param n The GL id of the texture you want to find.
    \return A pointer to the texture if found, else NULL.
*/
PhTexture* PhTextureManager::findTexture(const GLuint& n)
{
    for (unsigned int i=0;i<texturelist.size();i++)
    {
        if ( (texturelist[i]!=NULL) && (texturelist[i]->getTexture() == n) )
        {
            return texturelist[i];
        }
    }
    return NULL;
}
