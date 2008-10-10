#ifndef PHLIGHTMANAGER_H
#define PHLIGHTMANAGER_H

#include <vector>
#include "PhRenderTexture.h"
#include "PhSceneManager.h"

using namespace phoenix;
using namespace std;

namespace phoenix
{

    class PhLight;

    //! Pixel-Based Light Manager.
    /*!
        This is the advanced pixel-based light manager, it provides ways to draw and manage pixel-based lights.
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

        //! Destructor.
        /*!
            Deletes all the lights in the list.
        */
        virtual ~PhLightManager();

        //! Add light.
        /*!
            Adds a light to the manager, this is usually taken care of the the Light itself: Created lights
            must register themselves with the light manager to be down (Similar to scenenodes).
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
            This renders the buffer that all the lights were rendered to over the scene (at a depth of 99.0f).
            This should be called after everything else is draw. This function is automatically called by
            PhSceneeManager after the onRender() step and before the onPostRender() step if lights are
            enabled.
            \sa PhSceneManager::drawAll(), generateBuffer()
        */
        void renderBuffer();

        //! Get buffer.
        /*!
            \return A pointer to the texture currently being used as a buffer for drawing lights.
            \sa generateBuffer(), renderBuffer()
        */
        PhTexture* getBuffer();

        //! Get scenemanager.
        /*!
            \return A pointer to the scenemanager that manages us.
        */
        PhSceneManager* getSceneManager();

    protected:

        PhRenderTexture* rtexture;
        PhSceneManager* smgr;
        vector<PhLight*> lights;

    private:
    };

}

#include "PhLight.h"

#endif // PHLIGHTMANAGER_H
