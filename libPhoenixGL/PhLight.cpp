/*

Copyright (c) 2008, Jonathan Wayne Parrott, Denzel Morris.

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

#include "PhLight.h"
using namespace phoenix;
using namespace std;

PhLight::PhLight(PhLightManager* lMgr)
{
	lightMgr = lMgr;
	lightMgr->addLight(this);
}

PhLight::~PhLight()
{
	lightMgr->removeLight(this);
}

void PhLight::setName(string name)
{
	mName = name;
}

string PhLight::getName()
{
	return mName;
}

void PhLight::setAmbient(PhColor ambient) 
{
	mAmbient[0] = ambient.getRed()/255;
	mAmbient[1] = ambient.getGreen()/255;
	mAmbient[2] = ambient.getBlue()/255;
	mAmbient[3] = ambient.getAlpha()/255;
}

void PhLight::setDiffuse(PhColor diffuse) 
{ 
	mDiffuse[0] = diffuse.getRed()/255; 
	mDiffuse[1] = diffuse.getGreen()/255;
	mDiffuse[2] = diffuse.getBlue()/255;
	mDiffuse[3] = diffuse.getAlpha()/255;
}

void PhLight::setSpecular(PhColor specular) 
{ 
	mSpecular[0] = specular.getRed()/255;
	mSpecular[1] = specular.getGreen()/255;
	mSpecular[2] = specular.getBlue()/255;
	mSpecular[3] = specular.getAlpha()/255;
}
void PhLight::setDistance(GLfloat dist) { mDistance = dist; }

void PhLight::setPosition(float x, float y, float z, float t)
{
	mPosition[0] = x;
	mPosition[1] = y;
	mPosition[2] = z;
	mPosition[3] = t;
}

void PhLight::setDirection(float x, float y, float z, float t)
{
	mDirection[0] = x;
	mDirection[1] = y;
	mDirection[2] = z;
	mDirection[3] = t;
}

GLfloat* PhLight::getAmbient() { return mAmbient; }
GLfloat* PhLight::getDiffuse() { return mDiffuse; }
GLfloat* PhLight::getSpecular() { return mSpecular; }
GLfloat* PhLight::getPosition() { return mPosition; }
GLfloat* PhLight::getDirection() { return mDirection; }
GLfloat PhLight::getDistance() { return mDistance; }
