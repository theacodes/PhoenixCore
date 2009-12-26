/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHRENDERTEXTURE_H__
#define __PHRENDERTEXTURE_H__

#include "RenderSystem.h"

namespace phoenix
{

    //! Render Texture.
    /*!
        This is a derived Texture that provides facilities for rendering the screen to a texture. It must be bound
        to a different BatchRenderer than RenderSystem. It provides methods for starting and ending render-to-texture
        drawing.
    */
    class RenderTexture
                : public Texture
    {

    public:

        //! Create
        /*!
            This factory generates a new RenderTexture. It must be bound to a different BatchRenderer than RenderSystem.
            It can use RenderSystem's resource manager.
            \param _r A resource manager.
            \param _s A pointer to the batch render.
            \param _sz The size of the texture.
        */
        inline static boost::shared_ptr<RenderTexture> create( ResourceManager& _r, BatchRenderer& _s, const Vector2d& _sz = Vector2d(512,512) )
        {
            boost::shared_ptr<RenderTexture> newtexture( new RenderTexture( _r, _s ) );
            _r.addResource( newtexture );
            newtexture->setName( "Untitled Render Target" );
            newtexture->buildTexture( _sz );
            return newtexture;
        }

        virtual ~RenderTexture()
        {
        }

        //! Start render.
        /*!
            Performs all the steps needed to begin rendering geometry to the texture. This
            function modifies the viewport on the BatchRenderer, so it is not a good idea
            to call View::setSize() while a RenderTexture is active. All geometry
            rendered after this call  and before endRender()
            will not be rendered to the screen, but to the texture.
            \note This function clears the screen.
        */
        inline void startRender()
		{

            // Our view port has to be the same size as the texture.
            View tview;
            tview.setSize( getSize() );
            sview = batcher.getView();
            batcher.setView( tview );

            //clear the screen
            RenderSystem::clearScreen( Color(0,0,0,0) );

		}


        //! End render.
        /*!
            Copies the backbuffer to the texture object, restores the viewport,
            and then clears the screen.
        */
        inline void endRender()
		{
			// copy the framebuffer pixels to a texture
			this->bind();

			// Copy Our ViewPort
			glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, getWidth(), getHeight(), 0);

			// restore the viewport.
			batcher.setView( sview );

            // clear the screen.
            RenderSystem::clearScreen();
		}


	protected:

        BatchRenderer& batcher;
        View sview;

        //! Private constructor
        RenderTexture( ResourceManager& r, BatchRenderer& s )
                : Texture(r), batcher(s), sview()
        {
        }

    };

} //namespace phoenix

#endif // __PHRENDERTEXTURE_H__
