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

#ifndef PHBACKGROUND_H
#define PHBACKGROUND_H

#include "PhSceneManager.h"
#include "PhSceneNode.h"

namespace phoenix
{

    //!  Simple background implementation.
    /*!
    This class gives a simple scene node interface to draw a background that consists of a texture that
    is repeated over the whole screen.
    \sa phoenix::PhSolidBackground, phoenix::PhSceneNode
    */

    class PhBackground : public PhSceneNode
    {

    protected:

        //! Color.
        /*!
        Colorizes the texture, default is (255,255,255).
        \sa setColor(), getColor(), phoenix::PhColor
        */
        PhColor color;

        //! Scenemager.
        /*!
        Pointer to the scenemanger, this is required by all scene nodes.
        \sa phoenix::PhSceneManager
        */
        PhSceneManager* smgr;

        //! Texture.
        /*!
        Pointer to the texture to fill the screen with.
        \sa phoenix::PhTexture
        */
        PhTexture* texture;

    public:

        //! Constructor.
        /*!
        Builds the simple background scene node.
        \param s A pointer to the scene manger, required.
        \param t A pointer to the texture, required.
        \param c The color to colorize the texture with, defualts to (255,255,255).
        \param d The depth to be drawn at, defualts at -100.0f, but as long as it's beind all objects you should be fine.
        */
        PhBackground(PhSceneManager* s, PhTexture* t, PhColor c = PhColor(255,255,255), float d = -100.0f);

        //! Destructor.
        /*!
        Destructs the node, nothing to see here...
        */
        ~PhBackground();

        //! Set color function.
        /*!
        Sets the color used to colorize the texture.
        \param c The new color.
        */
        void setColor(PhColor c);

        //! Get color function.
        /*!
        Get the current color used to colorize the texture.
        \return The current color.
        */
        PhColor getColor();

        //! Set texture function.
        /*!
        Sets the texture used by this node.
        \param t The new texture.
        */
        void setTexture(PhTexture* t);

        //! Get texture function.
        /*!
        Gets the current texture used by this node.
        \return The current texture.
        */
        PhTexture* getTexture();

        //! Overloaded onPreRender
        /*!
        Simply registers the node for rendering, as prescribed in
        PhSceneNode.
        \sa phoenix::PhSceneNode::onPreRender()
        */
        void onPreRender();

        //! Overloaded onRender
        /*!
        This draws the background using VBOs with the current texture
        and color.
        \sa phoenix::PhSceneNode::onRender()
        */
        void onRender();

        //! Overloaded onPostRender
        /*!
        Blank overload of PhSceneNode::onPostRender(), this class does
        not need to do anything after it draws.
        \sa phoenix::PhSceneNode::onPostRender()
        */
        void onPostRender();

    };

}

#endif
