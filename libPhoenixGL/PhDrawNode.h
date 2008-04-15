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

#ifndef PHOENIXDSN
#define PHOENIXDSN

#include "PhSceneManager.h"

namespace phoenix
{

    //! Draw scene node
    /*!
        Created more as an example than anything, this is a simple scene node that draws a texture.
    */
    class PhDrawSceneNode : public PhSceneNode
    {

    protected:

        //! Position.
        PhVector2d pos;

        //! Texture.
        PhTexture* image;

        //! Free on destroy.
        bool fod;

        //! Scene manager.
        PhSceneManager* smgr;

        //! Render system.
        PhRenderSystem* system;

    public:

        //! Construct.
        /*!
            \param s Pointer to the scene manager.
            \param i Texture to draw.
            \param p Position.
            \param c Determines if the node deletes the texture when the node is deleted.
        */
        PhDrawSceneNode(PhSceneManager* s, PhTexture* i, PhVector2d p = PhVector2d(0,0), bool c = false);

        //! Destruct.
        ~PhDrawSceneNode();

        //! Get position.
        /*!
            \return The position of the node.
            \sa setPosition()
        */
        PhVector2d getPosition (void);

        //! Set position.
        /*!
            \param a The new position of the node.
            \sa getPosition()
        */
        void setPosition(PhVector2d a);

        //! Set texture.
        /*!
            \param img The new texture of the node.
            \sa getTexture()
        */
        bool setTexture(PhTexture* img);

        //! Get texture.
        /*!
            \return The current texture of the node.
            \sa setTexture()
        */
        PhTexture* getTexture();

        //! Free on destroy.
        /*!
            If this is true then the node will automatically delete the texture when the node is
            destroyed.
            \param a Free on destroy.
        */
        void setFod(bool a);

        //! Pre render.
        void onPreRender();

        //! Render.
        void onRender();

        //! Post render.
        void onPostRender();

    };

}

#endif
