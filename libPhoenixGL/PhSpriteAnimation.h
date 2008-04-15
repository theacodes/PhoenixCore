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

#ifndef PHOENIXSPR
#define PHOENIXSPR

#include "PhSceneManager.h"
#include "PhSceneNode.h"

namespace phoenix
{
    //! Sprite Animation.
    /*!
        This class provides a simple way to create simple sprite animations from animation cell sheets.
    */
    class PhSpriteAnimation : public PhSceneNode
    {

    protected:

        PhTexture* texture;
        PhVector2d framesize;
        float frame, framerate;
        float rot;
        int mMin,mMax;
        bool flip;
        PhColor color;
        PhVector2d pos;
        PhSceneManager* smgr;
        bool enabled;

    public:

        //! Constructor.
        /*!
            Makes a blank sprite animation.
            \param s A scenemanager.
        */
        PhSpriteAnimation(PhSceneManager* s);

        //! Constructor.
        /*!
            Makes a sprite animation.
            \param s A scenemanager.
            \param t Texture of the sprite sheet.
            \param a Size of one cell (sprite).
            \param p Position.
        */
        PhSpriteAnimation(PhSceneManager* s, PhTexture* t, PhVector2d a, PhVector2d p = PhVector2d(0.0f,0.0f));

        //! Destructor.
        ~PhSpriteAnimation();

        //! Set texture.
        /*!
            \param t New texture.
            \sa getTexture()
        */
        void setTexture(PhTexture* t);

        //! GEt Texture.
        /*!
            \return The current texture.
            \sa setTexture()
        */
        PhTexture* getTexture();

        //! Set animation.
        /*!
            Sets the bounding frames of the animation.
            \param b The begining frame.
            \param e The ending frame.
        */
        void setAnimation(int b, int e);

        //! Set frame.
        /*!
            Forces the frame to change.
            \param a The desired frame number.
            \sa getFrame()
        */
        void setFrame(int a);

        //! Get frame.
        /*!
            \return The current frame.
            \sa setFrame()
        */
        int getFrame();

        //! Set animation speed.
        /*!
            Sets the animation speed, animation speed of 1.0f has no skipping frames. Values
            above 1.0f may skip frames, values below 1.0f will make frames last longer.
            \note The speed is dependent on framerate.
            \param a The animation speed.
            \sa getAnimationSpeed()
        */
        void setAnimationSpeed(float a);

        //! Get animation speed.
        /*!
            \return The current animation speed.
            \sa setAnimationSpeed()
        */
        float getAnimationSpeed();

        //! Set frame size.
        /*!
            Sets the current size of one frame (cell) of animation.
            \param s The new cell size.
            \sa getFrameSize()
        */
        void setFrameSize(PhVector2d s);

        //! Get frame size.
        /*!
            \return The current frame (cell) size.
            \sa setFrameSize()
        */
        PhVector2d getFrameSize();

        //! Set position.
        /*!
            \param s The new position.
            \sa getPosition()
        */
        void setPosition(PhVector2d s);

        //! Get position.
        /*!
            \return The current position.
            \sa setPosition()
        */
        PhVector2d getPosition();

        //! Get rotation.
        /*!
            \return The current rotation (in degrees).
        */
        float getRotation();

        //! Set rotation.
        /*!
            \param r New rotation (in degrees).
        */
        void setRotation(float r);

        //! Get flip.
        /*!
            \return If the sprite is being flipped (horizontally).
        */
        bool getFlip();

        //! Set flip.
        /*!
            \param f Pass true to flip the sprite (horizontally).
        */
        void setFlip(bool f);

        //! Get color.
        /*!
            \return The current blending color.
        */
        PhColor getColor();

        //! Set color.
        /*!
            \param c The new blending color.
        */
        void setColor(PhColor c);

        //! Enable
        /*!
            Enables this sprite.
        */
        void enable();

        //! Disable
        /*!
            Disables this sprite.
        */
        void disable();

        void onPreRender();

        void onRender();

        void onPostRender();
    };

}

#endif
