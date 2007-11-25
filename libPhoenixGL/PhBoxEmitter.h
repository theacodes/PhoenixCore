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

#ifndef PHOENIXPBE
#define PHOENIXPBE

#include "PhSceneManager.h"
#include "PhParticleSystem.h"

////////////////////////////////////////////////////////////////////////////////
// Box Emitter (Easy to turn this into a point emitter)
////////////////////////////////////////////////////////////////////////////////

namespace phoenix
{

class PhBoxEmitter : public PhParticleEmitter
{

protected:

    //rectangle to create the particles in
    PhRect rect;

    //random function
    template <class a_type> a_type random(a_type low,a_type high)
    {
        return (a_type(rand()) % (high - low + a_type(1)) + low);
    }

public:

    //construct and destruct
    PhBoxEmitter(PhSceneManager* s, PhTexture* i, PhRect rt, PhParticleType pt, int p, float d, bool c);
    ~PhBoxEmitter();

    //functions for getting rectangle stuff
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    int getWidth();
    void setWidth(int);
    int getHeight();
    void setHeight(int);

    //PreRender function (Should only be called by scene manager)
    void onPreRender();

    //Render function (should only be called by scene manager)
    void onRender();

    //Postrender (should only be called by scene manager)
    void onPostRender();

};

}

#endif
