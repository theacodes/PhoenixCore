/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHOENIXRS__
#define __PHOENIXRS__

#include <GL/glfw.h>
#include <string>
#include <boost/bind.hpp>
#include "config.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Vector2d.h"
#include "EventReceiver.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "WindowManager.h"
#include "BatchRenderer.h"
#include "AbstractGeometryFactory.h"
#include "DebugConsole.h"
#include "2dGraphicsFactory.h"
#include "Font.h"

//! The phoenix namespace.
namespace phoenix
{

    //! Standard Resource Types
    enum E_RESOURCE_TYPES
    {
        ERT_TEXTURE = 1,
        ERT_FONT = 2,
        ERT_BITMAP_FONT = 3
    };

    //! The render system.
    /*!
        This is the heart of the Core. It ties together a ResourceManager, a BatchRender, Timer, and Fonts
        to provide a simply interface to drawing 2d objects in OpenGL. It provides texture loading and management,
        geometry factories and management, font loading and management, and access to a global resource manager.
        It also provides one entry point to initialize all of phoenix's subsystems.
    */
    class RenderSystem
    {

    public:

        //! Constructor
        /*!
            Makes a new system and creates a window and opengl context. Once the system is constructed
           you are ready to start drawing stuff.
           \sa run(), draw()
           \param _sz The size of the screen (default 640,480).
           \param _fs Full screen (default false).
        */
        RenderSystem( const Vector2d& _sz = Vector2d(640,480),bool _fs = false );

        //! Destruct.
        ~RenderSystem();

        //! Enable screen resizing ( disabled by default ).
        inline void enableResize() { WindowManager::setResizeCallback( boost::bind( &RenderSystem::resizeCallback, this, _1 ) ); }

        //! Disable screen resizing
        inline void disableResize() { WindowManager::setResizeCallback(); }

        //! Set blend mode.
        /*!
            Sets the blend mode for opengl. The default blend mode is GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA.
            If this is called without arguments, it restores the default blendmode.
            \param src The source factor, can be GL_ZERO, GL_ONE,
            GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
            GL_ONE_MINUS_DST_ALPHA, and GL_SRC_ALPHA_SATURATE
            \param dst The destination factor, can be GL_ZERO, GL_ONE,
            GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, and
            GL_ONE_MINUS_DST_ALPHA
        */
        inline static void setBlendMode(const GLenum& src = GL_SRC_ALPHA, const GLenum& dst = GL_ONE_MINUS_SRC_ALPHA ) { glBlendFunc(src,dst); }

        //! Get the system's batch renderer.
        inline BatchRenderer& getBatchRenderer() { return renderer; }

        //! Get the system's graphics factory.
        inline GraphicsFactory2d& getGraphicsFactory(){ return factory; }

        //! Get the system's internal resource manager.
        /*!
            You can add arbitrary resources to the system's resource manager. The system
            uses it to keep track of Textures and Fonts, but it is freely availible for the user
            to stick custom resources in.
        */
        inline ResourceManager& getResourceManager() { return resources; }

        //! Set the system's current font for drawing text.
        inline void setFont( FontPtr t ) { font = t; }

        //! Get the current font used for drawing text.
        inline FontPtr getFont() const { return font; }

        //! Get the debug console used by the render system.
        inline DebugConsole& getDebugConsole() { return console; }

        //! Run.
        /*!
            Run takes care of swapping buffers, updating events, clearing the screen, and tracking time.
            It also calls the Exit Test Function to determine if the system should stop.
        */
        bool run();

        //! Set exit test function.
        /*!
            Sets the function that run() will call to test if the engine should exit. If this returns false,
            then run will also return false.
            \sa defaultExitTestFunction()
        */
        inline void setExitTestFunction( const boost::function< bool ( void ) >& _f = boost::function< bool ( void ) >(&RenderSystem::defaultExitTestFunction) ) { exitTest = _f; }

        //! Get exit test function.
        inline const boost::function< bool ( void ) >& getExitTestFunction() { return exitTest; }

        //! Clears the screen to the given color.
        inline static void clearScreen( const Color& _c = Color(0,0,0) )
        {
            glClearColor( _c.getRed()/255.0f,_c.getGreen()/255.0f,_c.getBlue()/255.0f,_c.getAlpha()/255.0f );
            #ifdef DISABLE_DEPTHBUFFER
                glClear(GL_COLOR_BUFFER_BIT);
            #else
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            #endif
        }

        //! Get frames per second.
        inline const double getFPS() const { return framerate; }

        //! Get time.
        /*!
            \return The amout in time ( in seconds ) that has occured since the last time run was called.
        */
        inline const double getTime() const { return fpstimer.getTime(); }

        //! Load texture.
        /*!
            Loads an image as a texture and adds it to the texture manager for garbage collection. Can load .png, .tga, .bmp and .jpg.
            \param _fn The filename of the image to load.
            \param _l Tells the loader to use linear filtering or not. (default true).
            \note Use nearest filtering for tilemaps, or anything that may look bad when scaled.
            \note Textures must be sizes that are a power of two. NPOT textures will experience artifacts (or may fail all together).
        */
        TexturePtr loadTexture( const std::string& _fn , bool _l = true);

        //! Find texture by name.
        TexturePtr findTexture(const std::string& _n);

        //! Find texture by OpenGL Texture ID.
        TexturePtr findTexture(const GLuint& _i);

        //! Draw text
        /*!
            Draws the given string at the given position with the given color using the current font. This a geometry factory.
            \sa loadFont()
        */
        BatchGeometryPtr drawText( const std::string& _s, const Vector2d& _p, const Color& _c=Color(255,255,255));

        //! Delegates to BatchRenderer::getView
        inline View& getView() { return renderer.getView(); }

        //! Delegates to BatchRenderer::setView
        inline void setView( const View& _v ) { renderer.setView( _v ); }

        //! Delegates to GraphicsFactory2d::getDept
        inline float getDepth(){ return factory.getDepth(); }

        //! Delegates to GraphicsFactory2d::setDepth
        inline void setDepth( float _d = 0.0f ) { factory.setDepth( _d ); }
            
        //! Delegates to GraphicsFactory2d::drawLine
	    inline BatchGeometryPtr drawLine(const Vector2d& _v1 = Vector2d(0,0), const Vector2d& _v2 = Vector2d(0,0), const Color& _a = Color(255,255,255), const Color& _b = Color(255,255,255,255))
        {
            return factory.drawLine( _v1, _v2, _a, _b );
        }

	    //! Delegates to GraphicsFactory2d::drawRay
	    inline BatchGeometryPtr drawRay(const Vector2d& _o = Vector2d(0,0), const Vector2d& _r = Vector2d(0,0), const Color& _a = Color(255,255,255), const Color& _b = Color(255,255,255,255))
        {
            return factory.drawRay( _o, _r, _a, _b );
        }

	    //! Delegates to GraphicsFactory2d::drawRectangle
        inline BatchGeometryPtr drawRectangle( const Rectangle& _r = Rectangle(0,0,0,0), const Color& _a = Color(255,255,255), const Color& _b = Color(255,255,255), const Color& _c = Color(255,255,255), const Color& _d = Color(255,255,255) )
        {
            return factory.drawRectangle( _r, _a, _b, _c, _d );
        }

        //! Delegates to GraphicsFactory2d::drawPolygon
        inline BatchGeometryPtr drawPolygon (const Polygon& _p, const Color& _a = Color(255,255,255))
        {
            return factory.drawPolygon( _p, _a );
        }

        //! Delegates to GraphicsFactory2d::drawTexturedPolygon
        inline BatchGeometryPtr drawTexturedPolygon (const Polygon& _p, TexturePtr _t, const Color& _c = Color(255,255,255), bool _e = false)
        {
            return factory.drawTexturedPolygon( _p, _t, _c, _e );
        }

        //! Delegates to GraphicsFactory2d::drawTexture
        inline BatchGeometryPtr drawTexture( TexturePtr _t, const Vector2d& _p, const RotationMatrix& _rot = RotationMatrix( 0.0f ), const Vector2d& _scale = Vector2d(1.0f,1.0f), const Color& _color = Color(255,255,255), unsigned int _flags = EGF_NONE )
        {
            return factory.drawTexture( _t, _p, _rot, _scale, _color, _flags );
        }

        //! Delegates to GraphicsFactory2d::drawTexturePart
        inline BatchGeometryPtr drawTexturePart( TexturePtr _t, const Vector2d& _p, const Rectangle& _rect, const RotationMatrix& _rot = RotationMatrix(0.0f), const Vector2d& _scale=Vector2d(1.0f,1.0f), const Color& _color=Color(255,255,255), unsigned int _flags = EGF_NONE )
        {
            return factory.drawTexturePart( _t, _p, _rect, _rot, _scale, _color, _flags );
        }

    private:

        //! The default exit test function.
        /*!
            Checks if the ESC key was press or the Window's close button was clicked.
        */
        inline static bool defaultExitTestFunction( )
        {
            return ( !EventReceiver::getKey( PHK_ESC ) && !EventReceiver::getWindowClosed() );
        }

        //! Batch Renderer
        BatchRenderer renderer;

        //! Graphics Factory.
        GraphicsFactory2d factory;

        //! Resource manager
        ResourceManager resources;

        //! The system font used to draw text
        FontPtr font;

        //! Debug Console
        DebugConsole console;

        //! Resize callback
        void resizeCallback( Vector2d _sz );

        //! Timer for FPS.
        Timer fpstimer;

        //! Counts the number of frames per second
        double framerate;

        //! Tests if the system to exit, see run() and setExitTest().
        boost::function< bool ( void ) > exitTest;

    };

} //namespace phoenix

#endif //__PHOENIXRS__
