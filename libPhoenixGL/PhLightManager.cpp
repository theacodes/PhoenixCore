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

#include "PhLightManager.h"
using namespace phoenix;
using namespace std;

PhLightManager::PhLightManager()
{
}

PhLightManager::~PhLightManager()
{
	deleteLights();
}

void PhLightManager::updateLights()
{	
	activateLight(GL_LIGHT0);
	activateLight(GL_LIGHT1);
	activateLight(GL_LIGHT2);
	activateLight(GL_LIGHT3);
	activateLight(GL_LIGHT4);
	activateLight(GL_LIGHT5);
	activateLight(GL_LIGHT6);
	activateLight(GL_LIGHT7);
}

void PhLightManager::activateLight(GLenum id)
{
	int realNum = int(id - GL_LIGHT0);
	if (mLightList[realNum] == NULL)
		return;
	
	glEnable(id);
	glLightfv(id, GL_AMBIENT, mLightList[realNum]->getAmbient());
	glLightfv(id, GL_DIFFUSE, mLightList[realNum]->getDiffuse());
	glLightfv(id, GL_SPECULAR, mLightList[realNum]->getSpecular());
	glLightfv(id, GL_POSITION, mLightList[realNum]->getPosition());
	glLightf(id, GL_QUADRATIC_ATTENUATION, 1.0f);
}
		

void PhLightManager::addLight(PhLight* light)
{
	if (mLightList.size() > 7)
		return;
	
	mLightList.push_back(light);
}

void PhLightManager::removeLight(PhLight* light)
{
	for (unsigned int i = 0; i < mLightList.size(); i++)
	{
		if (mLightList[i] == light)
		{
			mLightList.erase(mLightList.begin()+i, mLightList.begin()+i+1);
		}
	}
}

void PhLightManager::deleteLights()
{
	for (unsigned int i = 0; i < mLightList.size(); i++)
	{
		if (mLightList[i] != NULL)
		{
			delete mLightList[i];
		}
	}
	
	mLightList.clear();
}

PhLight* PhLightManager::findLight(string name)
{
	for (unsigned int i = 0; i < mLightList.size(); i++)
	{
		if (mLightList[i] != NULL && mLightList[i]->getName() == name)
		{
			return mLightList[i];
		}
	}
	
	return NULL;
}
