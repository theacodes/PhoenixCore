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

#ifndef PHEXTENDEDBACKGROUND_H
#define PHEXTENDEDBACKGROUND_H

#include "PhSceneManager.h"

namespace phoenix
{

    //! Extended Background.
    /*!
    This is the extended background class. This is the most advanced background class included with phoenix.
    Extended background allow for the most control over the background. It provides the ability to change
    the texture, color, depth, horizontal tile, vertical tile, scroll speed, relative position, and texture
    offset of a background.
    \sa phoenix::PhSolidBackground, phoenix::PhBackground
    */
    class PhExtendedBackground : public PhSceneNode
    {

    public:

        //! Constuctor.
        /*!
        \param s Pointer to the scenemanager.
        \param t Texture to use.
        \param c Color to use. Default white.
        \param d Depth. Default -100.0f.
        \param xt Horizontal tile. Default true.
        \param yt Vertical tile. Default true.
        \param sp Scroll speed. Defualt [0,0].
        \param po Relative position of the bg. Default [0,0].
        \param o Texture offset. Default [0,0].
        */
        PhExtendedBackground(PhSceneManager* s, PhTexture* t, PhColor c = PhColor(255,255,255,255), float d = -100.0f, bool xt = true, bool yt = true, PhVector2d sp = PhVector2d(0.0f,0.0f), PhVector2d po = PhVector2d(0.0f,0.0f) , PhVector2d o = PhVector2d(0.0f,0.0f) );

        virtual ~PhExtendedBackground();

        //! Set color function.
        /*!
        Sets the color used to colorize the texture.
        \param c The new color.
        \sa getColor()
        */
        void setColor(PhColor c);

        //! Get color function.
        /*!
        Get the current color used to colorize the texture.
        \return The current color.
        \sa setColor()
        */
        PhColor getColor();

        //! Set texture function.
        /*!
        Sets the texture used by this node.
        \param t The new texture.
        \sa getTexture()
        */
        void setTexture(PhTexture* t);

        //! Get texture function.
        /*!
        Gets the current texture used by this node.
        \return The current texture.
        \sa setTexture()
        */
        PhTexture* getTexture();

        //! Set horizontal tile.
        /*!
        Sets whether of not to tile this background horizontally.
        \param b Tile boolean.
        \sa setVerticalTile()
        */
        void setHorizontalTile(bool b);

        //! Set vertical tile.
        /*!
        Sets whether of not to tile this background vertically.
        \param b Tile boolean.
        \sa setVerticalTile()
        */
        void setVerticalTile(bool b);

        //! Set position.
        /*!
        Sets the position of this background.
        \note Position is relative to the top-left corner of the VIEW, it is a relative position, not an absolute one.
        \param v New position.
        \sa getPosition()
        */
        void setPosition(PhVector2d v);

        //! Get position.
        /*!
        \note Position is relative to the top-left corner of the VIEW, it is a relative position, not an absolute one.
        \return The current position of the background.
        \sa setPosition()
        */
        PhVector2d getPosition();

        //! Set texture offset.
        /*!
        Sets the texture offset of the background. The texture offset is a normalized value and simply modifies
        The texture coords of the background. Can be use to achieve effects such as paralax and scrolling backgrounds.
        \param v The new texture offset.
        \sa getTextureOffset()
        */
        void setTextureOffset(PhVector2d v);

        //! Get texture offset.
        /*!
        \return The texture offset.
        \sa setTextureOffset()
        */
        PhVector2d getTextureOffset();

        //! Set scroll speed.
        /*!
        Using scroll speed the background will automatically change its texture offset every frame,
        creating the illusion of moving backgrounds.
        \param v The new speed;
        \sa setTextureOffset(), getScrollSpeed()
        */
        void setScrollSpeed(PhVector2d v);

        //! Get scroll speed.
        /*!
            \return The current scroll speed.
            \sa setTextureOffset(), setScrollSpeed()
        */
        PhVector2d getScrollSpeed();

        void onPreRender();

        void onRender();

        void onPostRender();

    protected:

        PhSceneManager* smgr;
        PhTexture* source;
        PhColor color;
        bool tilex, tiley;
        PhVector2d position;
        PhVector2d offset;
        PhVector2d speed;

    private:

    };

}


#endif // PHEXTENDEDBACKGROUND_H
