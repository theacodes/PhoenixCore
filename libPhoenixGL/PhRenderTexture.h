#ifndef PHRENDERTEXTURE_H
#define PHRENDERTEXTURE_H

#include "PhRenderSystem.h"

namespace phoenix
{

    //! Render texture.
    /*!
        Provides methods of rendering to a texture. This is intended for advanced effects, and is used by
        phoenix::PhLightManager.
        \sa phoenix::PhTexture
    */
    class PhRenderTexture
    {
    public:

        //! Constructor
        /*!
            Creates a new render texture and also creates a new texture to render to. The default
            size is 512x512.
            \param r A pointer to the rendersystem.
        */
        PhRenderTexture(PhRenderSystem* r);

        //! Constructor
        /*!
            Creates a new render texture for rendering to the given texture.
            \param r A pointer the rendersystem.
            \param t A pointer to the texture to render to.
        */
        PhRenderTexture(PhRenderSystem* r, PhTexture* t);

        virtual ~PhRenderTexture();

        //! Set texture.
        /*!
            Sets the texture that things are rendered to.
            \param t A pointer to the new target texture.
        */
        inline void setTexture(PhTexture* t) { texture = t; }

        //! Get texture.
        /*!
            \return A pointer to the texture object.
        */
        inline PhTexture* getTexture() const { return texture; }

        //! Start render.
        /*!
            Performs all the steps needed to begin rendering objects to the texture. All geometry
            rendered after this call will not be render to the screen, but to the texture.
            \note This function clears the screen.
        */
        void startRender();

        //! End render.
        /*!
            Copies the backbuffer to the texture object, and then clears the screen.
        */
        void endRender();

    protected:

        PhRenderSystem* system;
        PhTexture* texture;

    private:
    };
}

#endif // PHRENDERTEXTURE_H
