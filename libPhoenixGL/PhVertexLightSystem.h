#ifndef PhVertexLightSYSTEM_H
#define PhVertexLightSYSTEM_H

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
        void addLight(PhVertexLight* l);

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
