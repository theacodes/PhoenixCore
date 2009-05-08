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

#ifndef PHLIGHTMANAGER_H
#define PHLIGHTMANAGER_H

#include <vector>
#include "PhRenderTexture.h"
#include "PhSceneManager.h"

using namespace std;

namespace phoenix
{

    class PhLight;

    //! Pixel-Based Light Manager.
    /*!
        This is the advanced pixel-based light manager, it provides ways to draw and manage pixel-based lights.
        The pixel-based light manager works like this: PhSceneManager calls generateBuffer() at the
        beginning of drawing, which goes through each light and draws them on the backbuffer. The light
        manager then copies that buffer to a texture. After PhSceneManager is finished drawing all the nodes,
        it calls drawBuffer(), which overlays the lights over the whole scene.
        \sa PhVertexLightManager
    */
    class PhLightManager
    {
    public:

        //! Constructor.
        /*!
            Creates a new light manager. A light manager is usually automatically created by the scenemanager at initialization time.
            \param s Pointer to the Scenemanager that manages this.
            \param ts The size of the texture buffer that stores the light data.
            \sa PhSceneManager::getLightManager()
        */
        PhLightManager(PhSceneManager* s, PhVector2d ts = PhVector2d(256,256));

        //! Dtor.
        /*!
            Deletes all the lights in the list.
        */
        virtual ~PhLightManager();

        //! Add light.
        /*!
            Adds a light to the manager, this is usually taken care of the the Light itself: Created lights
            must register themselves with the light manager to be drawn (Similar to scenenodes).
            \param l Pointer the the light to add.
            \sa removeLight(),clearLights()
        */
        void addLight(PhLight* l);

        //! Remove light.
        /*!
            Removes a light from the manager, this is usually taken care of the Light when it is
            destructed, similar to scenenodes.
            \param l Pointer to the light to remove.
            \sa addLight(),clearLights()
        */
        void removeLight(PhLight* l);

        //! Clear light.
        /*!
            Removes all the lights from the manager.
            \sa addLight(),clearLights()
        */
        void clearLights();

        //! Generate buffer.
        /*!
            This draws all the lights on to the texture buffer to later be overlayed over the scene.
            This function should be called before anything else is drawn, as it clears the backbuffer.
            This function is automatically called by PhSceneManager at the right time if lights are enabled.
            \sa PhSceneManager::drawAll(), renderBuffer()
        */
        void generateBuffer();

        //! Render buffer.
        /*!
            This renders the buffer that all the lights were rendered to over the scene (at a depth of 99.0f by default).
            This should be called after everything else is drawn. This function is automatically called by
            PhSceneeManager after the onRender() step and before the onPostRender() step if lights are
            enabled.
            \param depth The depth at which to draw the light buffer.s
            \sa PhSceneManager::drawAll(), generateBuffer()
        */
        void renderBuffer( float depth = 99.0f );

        //! Get buffer.
        /*!
            \return A pointer to the texture currently being used as a buffer for drawing lights.
            \sa generateBuffer(), renderBuffer()
        */
        inline PhTexture* getBuffer() const { return rtexture->getTexture(); }

        //! Get scenemanager.
        /*!
            \return A pointer to the scenemanager that manages us.
        */
        inline PhSceneManager* getSceneManager() const { return smgr; }

    protected:

        PhRenderTexture* rtexture;
        PhSceneManager* smgr;
        vector<PhLight*> lights;

    private:
    };

}

#include "PhLight.h"

#endif // PHLIGHTMANAGER_H
