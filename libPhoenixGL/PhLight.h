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

#ifndef __PHOENIXLIGHTS__
#define __PHOENIXLIGHTS__

#include <string>
#include "PhColor.h"
#include "GL/gl.h"
#include "PhLightManager.h"

namespace phoenix
{
	
	class PhLight
	{
		protected:
			std::string mName;
			GLfloat mAmbient[4];
			GLfloat mDiffuse[4];
			GLfloat mSpecular[4];
			GLfloat mPosition[4];
			GLfloat mDirection[4];
			PhLightManager* lightMgr;
			GLfloat mDistance;
			
		public:
			//! Constructor
			PhLight(PhLightManager* lMgr);
			
			//! Destructor
			~PhLight();
			
			void setName(std::string n);
			std::string getName();
			
			void setAmbient(PhColor color);
			void setDiffuse(PhColor color);
			void setSpecular(PhColor color);
			void setPosition(float x, float y, float z, float t);
			void setDirection(float x, float y, float z, float t);
			void setDistance(GLfloat dist);
			
			GLfloat* getAmbient();
			GLfloat* getDiffuse();
			GLfloat* getSpecular();
			GLfloat* getPosition();
			GLfloat* getDirection();
			GLfloat getDistance();
			
	};
		
}

#endif
