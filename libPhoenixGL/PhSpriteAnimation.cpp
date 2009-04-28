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

#include "PhSpriteAnimation.h"

using namespace phoenix;

PhSpriteAnimation::PhSpriteAnimation(PhSceneManager* s)
	: PhSceneNode(s,0.0f), texture(NULL), framesize(0,0), frame(0), framerate(0), rot(0.0f), mMin(0), mMax(0), flip(false),
	color(255,255,255), pos(0,0), enabled(true), scale(1.0f,1.0f)
{
}

PhSpriteAnimation::PhSpriteAnimation(PhSceneManager* s, PhTexture* t, PhVector2d a, PhVector2d p)
	: PhSceneNode(s,0.0f), texture(t), framesize(a), frame(0), framerate(1.0f), rot(0.0f), mMin(0), mMax(0), flip(false),
	color(255,255,255), pos(p), enabled(true), scale(1.0f,1.0f)
{
}

void PhSpriteAnimation::setTexture(PhTexture* t)
{
    texture = t;
}

PhTexture* PhSpriteAnimation::getTexture()
{
    return texture;
}

void PhSpriteAnimation::setAnimation(int b, int e)
{
    mMin = b;
    mMax = e;
    if (frame > mMax)
    {
        frame = (float)mMin;
    }
    if (frame < mMin)
    {
        frame = (float)mMax;
    }
}

void PhSpriteAnimation::setFrame(int a)
{
    frame = float(a);
}

int PhSpriteAnimation::getFrame()
{
    return int(floor(frame));
}

void PhSpriteAnimation::setAnimationSpeed(float a)
{
    framerate = a;
}

float PhSpriteAnimation::getAnimationSpeed()
{
    return framerate;
}

void PhSpriteAnimation::setFrameSize(PhVector2d s)
{
    framesize = s;
}

PhVector2d PhSpriteAnimation::getFrameSize()
{
    return framesize;
}

void PhSpriteAnimation::setPosition(PhVector2d s)
{
    pos = s;
}

PhVector2d PhSpriteAnimation::getPosition()
{
    return pos;
}

float PhSpriteAnimation::getRotation()
{
    return rot;
}

void PhSpriteAnimation::setRotation(float r)
{
    rot = r;
}

bool PhSpriteAnimation::getFlip()
{
    return flip;
}

void PhSpriteAnimation::setFlip(bool f)
{
    flip = f;
}

PhColor PhSpriteAnimation::getColor()
{
    return color;
}

void PhSpriteAnimation::setColor(PhColor c)
{
    color = c;
}

PhVector2d PhSpriteAnimation::getScale()
{
    return scale;
}

void PhSpriteAnimation::setScale( PhVector2d s )
{
    scale = s;
}

void PhSpriteAnimation::enable() {
    enabled = true;
}

void PhSpriteAnimation::disable() {
    enabled = false;
}

void PhSpriteAnimation::onPreRender()
{
    if(enabled) {
        smanager->registerForRendering(this);
    }
}

void PhSpriteAnimation::onRender()
{

    float x,y;
    x =  floor(frame) * framesize.getX();
    y = (floor(frame/(texture->getWidth()/framesize.getX()))) * framesize.getY();

    smanager->getRenderSystem()->drawTexturePart( texture, pos, PhRect( x, y, framesize.getX(), framesize.getY() ), depth, rot, scale, color, flip );

}

void PhSpriteAnimation::onPostRender()
{

    //advance the animation
    frame += framerate;
    if (frame > mMax)
    {
        frame = (float)mMin;
    }
    if (frame < mMin)
    {
        frame = (float)mMax;
    }

}

