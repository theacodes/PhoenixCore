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

//! The phoenix namespace.
namespace phoenix
{

	class Font;

    //! Standard Resource Types
    enum E_RESOURCE_TYPES
    {
        ERT_TEXTURE = 1,
        ERT_FONT = 2,
        ERT_BITMAP_FONT = 3
    };

    //! Geometry Factory Flags
    enum E_GEOMETRY_FLAGS
    {
        EGF_NONE = 0x0000,
        EGF_HFLIP = 0x0001, //!< Horizontal Flip
        EGF_VFLIP = 0x0002 //!< Vertical Flip
    };

    //! The render system.
    /*!
        This is the heart of the Core. It ties together a ResourceManager, a BatchRender, Timer, and Fonts
        to provide a simply interface to drawing 2d objects in OpenGL. It provides texture loading and management,
        geometry factories and management, font loading and management, and access to a global resource manager.
        It also provides one entry point to initialize all of phoenix's subsystems.
    */
    class RenderSystem
		: public BatchRenderer, public AbstractGeometryFactory
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

        //! Get a pointer to the system's internal resource manager.
        /*!
            You can add arbitrary resources to the system's resource manager. The system
            uses it to keep track of Textures and Fonts, but it is freely availible for the user
            to stick custom resources in.
        */
        inline ResourceManager& getResourceManager() { return resources; }

        //! Set the system's current font for drawing text.
        inline void setFont( boost::shared_ptr<Font> t ) { font = t; }

        //! Get the current font used for drawing text.
        inline boost::shared_ptr<Font> getFont() const { return font; }

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
        /*!
            \return The FPS since the last time run() was called.
        */
        inline const double getFPS() const { return 1.0f/fpstimer.getTime(); }

        //! Get last FPS
        /*!
			\return The previous FPS. Usually a little bit more stable.
		*/
		inline const double& getLastFPS() const { return framerate; }

        //! Get time.
        /*!
            \return The amout in time (ms) that has occured since the engine started.
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
        boost::shared_ptr<Texture> loadTexture( const std::string& _fn , bool _l = true);

        //! Find texture by name.
        boost::shared_ptr<Texture> findTexture(const std::string& _n);

        //! Find texture by OpenGL Texture ID.
        boost::shared_ptr<Texture> findTexture(const GLuint& _i);

		//! Draws a 2D line segment with a color for each end.
		/*!
            This is a geometry factory.
			\param _v1 The vector to the first point of the line.
			\param _v2 The vector to the second point of the line.
			\param _a Color of the first vertex.
			\param _b Color of the second vertex.
			\sa drawRay()
		*/
		boost::shared_ptr<BatchGeometry> drawLine(const Vector2d& _v1 = Vector2d(0,0), const Vector2d& _v2 = Vector2d(0,0), const Color& _a = Color(255,255,255), const Color& _b = Color(255,255,255,255));

		//! Draws a 2D ray with a color for each end starting from the origin.
		/*!
            This is a geometry factory.
			\param _o The Point of origin.
			\param _r The Ray.
			\param _a Color of the start of the ray.
			\param _b Color of the end of the ray.
			\sa drawLine()
		*/
		inline boost::shared_ptr<BatchGeometry> drawRay(const Vector2d& _o = Vector2d(0,0), const Vector2d& _r = Vector2d(0,0), const Color& _a = Color(255,255,255), const Color& _b = Color(255,255,255,255))
        {
            return drawLine( _o, _o+_r, _a, _b );
        }

		//! Draw rectangle.
        /*!
            Draws a rectangle with a color for each corner. This is a geometry factory.
            \param _r The rectangle to be drawn.
            \param _a Color of the top-left corner.
            \param _b Color of the top-right corner.
            \param _c Color of the bottom-right corner.
            \param _d Color of the bottom-left corner.
        */
        boost::shared_ptr<BatchGeometry> drawRectangle( const Rectangle& _r = Rectangle(0,0,0,0), const Color& _a = Color(255,255,255), const Color& _b = Color(255,255,255), const Color& _c = Color(255,255,255), const Color& _d = Color(255,255,255) );

        //! Draws a polygon.
        /*!
            Simply draws a polygon with the given depth and color. This is a geometry factory.
        */
        boost::shared_ptr<BatchGeometry> drawPolygon (const Polygon& _p, const Color& _a = Color(255,255,255));

        //! Draws a textured polygon.
        /*!
            Draws a polygon with the given depth and color and applies the given texture to the polygon. This function
            automatically generates texture coordinates for the polygon in either eye space or object space.
            By default, it generates them in object space. This is a geometry factory.
            \param _p The Polygon to draw.
            \param _t The Texture of the polygon.
            \param _c The Color to be applied to the polygon.
            \param _e Set to true to generate coordniates in eye space instead of object space.
        */
        boost::shared_ptr<BatchGeometry> drawTexturedPolygon (const Polygon& _p, boost::shared_ptr<Texture> _t, const Color& _c = Color(255,255,255), bool _e = false);

        //! Draw texture.
        /*!
            Draws a textured rectangle with the same dimensions as the given texture at the specified position. This is a geometry factory.
            \param _t The texture to draw.
            \param _p Where to draw it at.
            \param _rot Rotation Matrix.
            \param _scale Scale.
            \param _color Color.
            \param _flags E_GEOMETRY_FLAGS for certain effects.
            \sa drawTexturePart()
        */
        boost::shared_ptr<BatchGeometry> drawTexture( boost::shared_ptr<Texture> _t, const Vector2d& _p, const RotationMatrix& _rot = RotationMatrix( 0.0f ), const Vector2d& _scale = Vector2d(1.0f,1.0f), const Color& _color = Color(255,255,255), unsigned int _flags = EGF_NONE );

        //! Draws a texture with a clipping rectangle.
        /*!
            Draws a textured rectangle with the same dimensions as the given rectangle. This is a geometry factory.
            \param _t The texture to draw.
            \param _p Where to draw it at.
            \param _rect The clipping rectangle, this defines the region of the texture to use.
            \param _rot Rotation.
            \param _scale Scale.
            \param _color Color.
            \param _flags E_GEOMETRY_FLAGS for certain effects.
            \sa drawTexture()
        */
        boost::shared_ptr<BatchGeometry> drawTexturePart( boost::shared_ptr<Texture> _t, const Vector2d& _p, const Rectangle& _rect, const RotationMatrix& _rot = RotationMatrix(0.0f), const Vector2d& _scale=Vector2d(1.0f,1.0f), const Color& _color=Color(255,255,255), unsigned int _flags = EGF_NONE );

        //! Draw text
        /*!
            Draws the given string at the given position with the given color using the current font. This a geometry factory.
            \sa loadFont()
        */
        boost::shared_ptr<BatchGeometry> drawText( const std::string& _s, const Vector2d& _p, const Color& _c=Color(255,255,255));

    private:

        //! The default exit test function.
        /*!
            Checks if the ESC key was press or the Window's close button was clicked.
        */
        inline static bool defaultExitTestFunction( )
        {
            return ( !EventReceiver::getKey( PHK_ESC ) && !EventReceiver::getWindowClosed() );
        }

        //! Resize callback
        void resizeCallback( Vector2d _sz );

        //! Debug Console
        DebugConsole console;

        //! Timer for FPS.
        Timer fpstimer;

        //! Counts the number of frames per second
        double framerate;

        //! The system font used to draw text
        boost::shared_ptr<Font> font;

        //! Resource manager
        ResourceManager resources;

        //! Tests if the system to exit, see run() and setExitTest().
        boost::function< bool ( void ) > exitTest;

    };

} //namespace phoenix

#include "BitmapFont.h"

#endif //__PHOENIXRS__
