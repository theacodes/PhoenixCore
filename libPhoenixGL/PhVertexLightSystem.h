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

#ifndef __PhVertexLightSYSTEM_H__
#define __PhVertexLightSYSTEM_H__

#include <vector>

#include <GL/gl.h>

using namespace std;

namespace phoenix
{

    class PhVertexLight;

    //! Light System class.
    /*!
        This class provides a way of managing opengl lights, this class is provided for advanced users and is not
        recommended for average users, we suggest using phoenix::PhLightManager instead.
        \sa phoenix::PhVertexLight, phoenix::PhLightManager
    */
    class PhVertexLightSystem
    {
    public:

        //! Constructor.
        /*!
            Constructs a new light system. Usually you have no need to call this manually, as the render
            system makes one for you.
        */
        PhVertexLightSystem();

        //! Destructor.
        /*!
            Deletes all the currents lights and closes the light system. Usually no need to call this manually.
        */
        virtual ~PhVertexLightSystem();

        //! Add light.
        /*!
            Adds a light to the light system. Please note that if you add more lights than the current
            opengl implementation supports, you won't notice any difference.
            \param l Pointer to the light to add.
        */
        inline void addLight(PhVertexLight* l) { lights.push_back(l);}

        //! Remove light.
        /*!
            Removes a light from the light system.
            \param l Pointer to the light to remove.
        */
        void removeLight(PhVertexLight* l);

        //! Clear lights.
        /*!
            Deletes all the lights in the system.
        */
        void clearLights();

        //! Set lights.
        /*!
            Updates the opengl state machine with all the current lights. There is usually no need to call this manually,
            the render system calls it automatically during PhRenderSystem::run().
        */
        void setLights();

    protected:

        vector<PhVertexLight*> lights;

    private:
    };

}

#include "PhVertexLight.h"

#endif // PhVertexLightSYSTEM_H
