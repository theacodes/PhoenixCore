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
        bool enabled;
        PhVector2d scale;

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
        PhSpriteAnimation(PhSceneManager* s, PhTexture* t, const PhVector2d a, const PhVector2d p = PhVector2d(0.0f,0.0f));

        //! Set texture.
        /*!
            \param t New texture.
            \sa getTexture()
        */
        inline void setTexture(PhTexture* t) { texture = t; }

        //! GEt Texture.
        /*!
            \return The current texture.
            \sa setTexture()
        */
        inline PhTexture* getTexture() const { return texture; }

        //! Set animation.
        /*!
            Sets the bounding frames of the animation.
            \param b The begining frame.
            \param e The ending frame.
        */
        void setAnimation(const int& b, const int& e);

        //! Set frame.
        /*!
            Forces the frame to change.
            \param a The desired frame number.
            \sa getFrame()
        */
        inline void setFrame(const float& a) { frame = a; }

        //! Get frame.
        /*!
            \return The current frame.
            \sa setFrame()
        */
        inline const float& getFrame() const { return frame; }

        //! Set animation speed.
        /*!
            Sets the animation speed, animation speed of 1.0f has no skipping frames. Values
            above 1.0f may skip frames, values below 1.0f will make frames last longer.
            \note The speed is dependent on framerate.
            \param a The animation speed.
            \sa getAnimationSpeed()
        */
        inline void setAnimationSpeed(const float& a) { framerate = a; }

        //! Get animation speed.
        /*!
            \return The current animation speed.
            \sa setAnimationSpeed()
        */
        inline const float& getAnimationSpeed() const { return framerate; }

        //! Set frame size.
        /*!
            Sets the current size of one frame (cell) of animation.
            \param s The new cell size.
            \sa getFrameSize()
        */
        inline void setFrameSize(const PhVector2d& s) { framesize = s; }

        //! Get frame size.
        /*!
            \return The current frame (cell) size.
            \sa setFrameSize()
        */
        inline const PhVector2d& getFrameSize() const { return framesize; }

        //! Set position.
        /*!
            \param s The new position.
            \sa getPosition()
        */
        inline void setPosition(const PhVector2d& s) { pos = s; }

        //! Get position.
        /*!
            \return The current position.
            \sa setPosition()
        */
        inline const PhVector2d& getPosition() const { return pos; }

        //! Get rotation.
        /*!
            \return The current rotation (in degrees).
        */
        inline const float& getRotation() const { return rot; }

        //! Set rotation.
        /*!
            \param r New rotation (in degrees).
        */
        inline void setRotation(const float& r) { rot = r; }

        //! Get flip.
        /*!
            \return If the sprite is being flipped (horizontally).
        */
        inline const bool& getFlip() const { return flip; }

        //! Set flip.
        /*!
            \param f Pass true to flip the sprite (horizontally).
        */
        inline void setFlip(const bool& f) { flip = f; }

        //! Get color.
        /*!
            \return The current blending color.
        */
        inline const PhColor& getColor() const { return color; }

        //! Set color.
        /*!
            \param c The new blending color.
        */
        inline void setColor(const PhColor& c) { color = c; }

        //! Get scale
        /*!
            \return The current scale of the sprite.
        */
        inline const PhVector2d& getScale() const { return scale; }

        //! Set scale
        /*!
            \param s The new scale.
        */
        inline void setScale( const PhVector2d& s ) { scale = s; }

        //! Set enabled
        /*!
            Enables or disables this sprite.
            \sa getEnabled()
        */
        inline void setEnabled(  const bool& e ) {  enabled = e; }

        //! Get enabled
        /*!
            \return True if the sprite is enabled
            \sa setEnabled()
        */
        inline const bool& getEnabled() const { return enabled;}

        void onPreRender();

        void onRender();

        void onPostRender();
    };

}

#endif
