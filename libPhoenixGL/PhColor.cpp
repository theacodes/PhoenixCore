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

#include "SDL/SDL_OpenGL.h" //SDL's openGL header
#include "PhColor.h"
#include "PhFunctions.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct
////////////////////////////////////////////////////////////////////////////////

PhColor::PhColor()
{
    red=0;
    green=0;
    blue=0;
    alpha=255;
}

////////////////////////////////////////////////////////////////////////////////
//Construct
////////////////////////////////////////////////////////////////////////////////

PhColor::PhColor( int x, int y, int z, int a )
{
    red=x;
    green=y;
    blue=z;
    alpha=a;
}

////////////////////////////////////////////////////////////////////////////////
//gets the values of red, green, and blue
////////////////////////////////////////////////////////////////////////////////

int PhColor::getRed()
{
    return red;
}

int PhColor::getGreen()
{
    return green;
}

int PhColor::getBlue()
{
    return blue;
}

int PhColor::getAlpha()
{
    return alpha;
}

////////////////////////////////////////////////////////////////////////////////
//sets the values of red, green, and blue
////////////////////////////////////////////////////////////////////////////////

void PhColor::setRed(int a)
{
    red=a;
}

void PhColor::setGreen(int a)
{
    green=a;
}

void PhColor::setBlue(int a)
{
    blue=a;
}

void PhColor::setAlpha(int a)
{
    alpha=a;
}

////////////////////////////////////////////////////////////////////////////////
//Sets this color to the active OpenGL color
////////////////////////////////////////////////////////////////////////////////

void PhColor::setActiveColor()
{
    glColor4f(float(red)/255.0f,float(green)/255.0f,float(blue)/255.0f,float(alpha)/255.0f);
}

////////////////////////////////////////////////////////////////////////////////
//returns this color as an opengl color
////////////////////////////////////////////////////////////////////////////////

int PhColor::toGLColor(){
    int color = (((alpha & 0xff)<<24) | ((red & 0xff)<<16) | ((green & 0xff)<<8) | (blue & 0xff));
    return (((color>>24) & 0xff)<<24) |
					(((color)& 0xff)<<16) |
					((color>>8 & 0xff)<<8) |
					((color>>16) & 0xff);
}

////////////////////////////////////////////////////////////////////////////////
//interpolates between this and another color
////////////////////////////////////////////////////////////////////////////////

PhColor PhColor::interpolate(PhColor dest,float percent){
    PhColor temp;
    temp.red = red + int(porportion(0.0f,float(dest.red-red),percent,100.0f,0));
    temp.green = green + int(porportion(0.0f,float(dest.green-green),percent,100.0f,0));
    temp.blue = blue + int(porportion(0.0f,float(dest.blue-blue),percent,100.0f,0));
    temp.alpha = alpha + int(porportion(0.0f,float(dest.alpha-alpha),percent,100.0f,0));
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
//Equal to operator
////////////////////////////////////////////////////////////////////////////////

PhColor& PhColor::operator = (const PhColor other)
{
    red = other.red;
    green = other.green;
    blue = other.blue;
    alpha = other.alpha;
    return *this;
}
