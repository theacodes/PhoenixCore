#ifndef PHLIGHTSYSTEM_H
#define PHLIGHTSYSTEM_H

#include <vector>

#include <gl/gl.h>

using namespace std;

class PhLight;

//! Light System class.
/*!
    This class provides a way of managing opengl lights.
    \sa PhLight
*/
class PhLightSystem
{
    public:

        //! Constructor.
        /*!
            Constructs a new light system. Usually you have no need to call this manually, as the render
            system makes one for you.
        */
        PhLightSystem();

        //! Destructor.
        /*!
            Deletes all the currents lights and closes the light system. Usually no need to call this manually.
        */
        virtual ~PhLightSystem();

        //! Add light.
        /*!
            Adds a light to the light system. Please note that if you add more lights than the current
            opengl implementation supports, you won't notice any difference.
            \param l Pointer to the light to add.
        */
        void addLight(PhLight* l);

        //! Remove light.
        /*!
            Removes a light from the light system.
            \param l Pointer to the light to remove.
        */
        void removeLight(PhLight* l);

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

        vector<PhLight*> lights;

    private:
};

#include "PhLight.h"

#endif // PHLIGHTSYSTEM_H
