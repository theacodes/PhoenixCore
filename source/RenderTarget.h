/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHRENDETARGET_H__
#define __PHRENDETARGET_H__

#include <boost/unordered_map.hpp>
#include "config.h"
#include "View.h"
#include "Resource.h"
#include "Texture.h"

namespace phoenix
{

    //! Render Target
    /*!
        This class provides the ability to bind textures as the current render target. 
    */
    class RenderTarget
                : public Resource
    {

    public:

		//! Default Constructor
        /*!
			Create a framebuffer object, but does not create a texture. A texture must be attached before this can be used.
		*/
        RenderTarget( ResourceManager& r )
                : Resource(r), FBO_id(0), textures(32)
        {
            setName( "RenderTarget" );
			generateFramebufferObject();
        }

		//! Quick Constructor
        /*!
			Create a framebuffer object and a texture with the given size, and attaches the texture.
		*/
        RenderTarget( ResourceManager& r, Vector2d size )
                : Resource(r), FBO_id(0), textures(32)
        {
            setName( "RenderTarget" );
			generateFramebufferObject();

			TexturePtr t = new Texture( r, size );
			attach( t );
        }

        virtual ~RenderTarget()
        {
			if( GLEW_VERSION_2_0 && FBO_id){
				glDeleteFramebuffersEXT( 1, &FBO_id );
			}
        }

		//! Attaches a texture to the FBO.
		inline void attach( TexturePtr t, const GLuint _where = GL_COLOR_ATTACHMENT0_EXT ){

			textures[_where] = t;

			if( GLEW_VERSION_2_0  && FBO_id ){
				bind();
					glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
								  (GLuint) _where,
								  GL_TEXTURE_2D,
								  t->getTextureId(),
								  0);
				unbind();
			}
		}
		
		//! Gets the currently attached texture
		inline TexturePtr getTexture( const GLuint _where = GL_COLOR_ATTACHMENT0_EXT ) { return textures[_where]; }

		//! Binds the FBO
		inline void bind(){ glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, FBO_id); }

		//! Unbinds the FBO
		inline void unbind(){ glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); }

        //! Binds the FBO and prepares to render, returns false if anything went wrong.
        inline bool start()
		{

			if( GLEW_VERSION_2_0  && FBO_id ){
				bind();

				if( glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT ) != GL_FRAMEBUFFER_COMPLETE_EXT ) return false;

				return true;
			}

			return false;

		}


        //! Unbinds the FBO
        inline void end()
		{
			if( GLEW_VERSION_2_0){
				unbind();
			}
		}


	protected:

		//! Generate Framebuffer Object Id, returns true if everything was okay, or false if it was unable to do so.
		bool generateFramebufferObject(){
			if( GLEW_VERSION_2_0 ){
				glGenFramebuffersEXT( 1, &FBO_id );
				return FBO_id ? true : false;
			}
			return true;
		}

		GLuint FBO_id;
		boost::unordered_map<GLuint, TexturePtr> textures;
    };

    typedef boost::intrusive_ptr<RenderTarget> RenderTargetPtr;
} //namespace phoenix

#endif // __PHRENDETARGET_H__
