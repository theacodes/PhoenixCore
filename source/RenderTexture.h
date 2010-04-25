/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHRENDERTEXTURE_H__
#define __PHRENDERTEXTURE_H__

#include "config.h"
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

		//! Constructor
        /*!
			Requires a ResourceManager and a BatchRenderer to attach to.
			\param _sz The size of the render target. must be a power of two.
		*/
        RenderTexture( ResourceManager& r, BatchRenderer& s, const Vector2d& _sz = Vector2d(512,512) )
                : Texture(r), batcher(s), sview()
        {
            setName( "Untitled Render Target" );
            build( _sz );
        }

        virtual ~RenderTexture()
        {
        }

        //! Start render.
        /*!
            Performs all the steps needed to begin rendering geometry to the texture. This
            function modifies the viewport on the BatchRenderer, so it is not a good idea
            to call View::setSize() while a RenderTexture is active. Remember, you must
			called whatever BatchRenderer's draw() function between start() and end();
            \note This function clears the screen.
        */
        inline void start()
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
        inline void end()
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

    };

    typedef boost::intrusive_ptr<RenderTexture> RenderTexturePtr;
} //namespace phoenix

#endif // __PHRENDERTEXTURE_H__
