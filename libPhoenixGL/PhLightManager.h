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

#ifndef __PHOENIXLIGHTM__
#define __PHOENIXLIGHTM__

#include <string>
#include <vector>
#include <algorithm>
#include "PhColor.h"
#include "GL/gl.h"
#include <math.h>

namespace phoenix
{

	class PhLight;

	class PhLightManager
	{
		protected:
			std::vector<PhLight*> mLightList;

		public:
			//! Constructor
			PhLightManager();

			//! Destructor
			~PhLightManager();

			void updateLights();
			void activateLight(GLenum id);

			void addLight(PhLight* light);
			void removeLight(PhLight* light);
			void deleteLights();
			PhLight* findLight(std::string name);
	};

}

#include "PhLight.h"

#endif
