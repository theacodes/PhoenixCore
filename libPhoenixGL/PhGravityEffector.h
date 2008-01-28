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

#ifndef PHOENIXPGE
#define PHOENIXPGE

#include "PhSceneManager.h"
#include "PhParticleSystem.h"

#include <math.h>

namespace phoenix
{

class PhGravityEffector : public PhParticleEffector
{

protected:

    //position
    int x,y;

    //force
    int force;

    //reach
    int reach;

    //distance function
    double getDistance( int x1, int y1, int x2, int y2 ) {
        //Return the distance between the two points
		int i_x = x2 - x1;
		int i_y = y2 - y1;
		return (i_x * i_x) + (i_y * i_y);
    }

public:

    //construct  & destruct
    PhGravityEffector(PhSceneManager*,PhParticleEmitter*,int,int,int,int);
    ~PhGravityEffector();

    //functions for getting rectangle stuff
    int getX();
    void setX(int);
    int getY();
    void setY(int);

    //functiosn to get and set force
    int getForce();
    void setForce(int);

    //functiosn to get and set reach
    int getReach();
    void setReach(int);

    //REnder stuff
    void onPreRender();
    void onRender()
    {}
    void onPostRender()
    {}


};

}

#endif
