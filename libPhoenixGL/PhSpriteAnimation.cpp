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


void PhSpriteAnimation::setAnimation(const int& b, const int& e)
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

