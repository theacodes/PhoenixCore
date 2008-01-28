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
	if (mLightList.size() > 8)
	{
		determineDistances();
	}
	
	determineActiveLights();
	
	activateLight(GL_LIGHT0);
}

void PhLightManager::activateLight(GLenum id)
{
	int realNum = int(id - GL_LIGHT0);
	glEnable(id);
	glLightfv(id, GL_AMBIENT, mLightList[realNum]->getAmbient());
	glLightfv(id, GL_DIFFUSE, mLightList[realNum]->getDiffuse());
	glLightfv(id, GL_SPECULAR, mLightList[realNum]->getSpecular());
	glLightfv(id, GL_POSITION, mLightList[realNum]->getPosition());
	glLightf(id, GL_QUADRATIC_ATTENUATION, 3.0f);
}

void PhLightManager::determineActiveLights()
{
	std::sort(mLightList.begin(), mLightList.end(), &distanceSort);
}

void PhLightManager::determineDistances()
{
	GLfloat subX, subY, subZ, distsqr;
	GLfloat* lightPos = (GLfloat*)malloc(4 * sizeof(float));;
	for (unsigned int i = 0; i < mLightList.size(); i++)
	{
		lightPos = mLightList[i]->getPosition();
		subX = lightPos[0] - mCenter[0];
		subY = lightPos[1] - mCenter[1];
		subZ = lightPos[2] - mCenter[2];
		distsqr = ((subX * subX) + (subY * subY) + (subZ * subZ));
		mLightList[i]->setDistance(distsqr);
	}
	free(lightPos);
}
		

void PhLightManager::addLight(PhLight* light)
{
	mLightList.push_back(light);
}

void PhLightManager::setCenter(float x, float y, float z, float t)
{
	mCenter[0] = x;
	mCenter[1] = y;
	mCenter[2] = z;
	mCenter[3] = t;
}

GLfloat* PhLightManager::getCenter()
{
	return mCenter;
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

bool PhLightManager::distanceSort(PhLight* a, PhLight* b)
{
	if (a->getDistance() > b->getDistance())
		return true;
	return false;
}
