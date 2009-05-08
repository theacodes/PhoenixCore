/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

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

#ifndef PHOENIXRS
#define PHOENIXRS

#include <GL/glu.h>
#include <GL/glfw.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "PhTextureManager.h"
#include "PhLogManager.h"
#include "PhTimer.h"
#include "PhVector2d.h"
#include "PhEventHandle.h"
#include "PhRect.h"
#include "PhPolygon.h"
#include "PhVertexLightSystem.h"

//! The phoenix namespace.
/*!
Copyright (c) 2007, Jonathan Wayne Parrott.

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
namespace phoenix
{

    //! The render system.
    /*!
        This is the heart of phoenix. On the basic level it provides a layer over OpenGL. It provides
        primitive drawing functions as well as functions for drawing textures and text. It provides
        functions for loading textures, as well as manipulating the window.
    */
    class PhRenderSystem
    {

    private:

        //Event handler
        PhEventHandler* events;

        //Texture manager
        PhTextureManager* textures;

        //Log manager
        PhLogManager* logs;

        //Timer for FPS and getTicks()
        PhTimer fpstimer;

        //Counts the number of frames, width, height
        int frame;

        //stores the size of the screen
        PhVector2d screensize;

        //The font used to draw text
        PhTexture* font;

        //determines if vertexlighting is enable
        bool vertexlighting;

        //Light system
        PhVertexLightSystem* vlsys;

        //Glyph structure
        struct PhGlyph
        {
            PhVector2d t;
        };

        //Array of glyphs
        PhGlyph glyphs[256];


    public:

        //! Construct.
        PhRenderSystem();

        //! Destruct.
        ~PhRenderSystem();

        //! Set window caption.
        /*!
            \param str The new caption of the window.
        */
        inline void setWindowCaption(const std::string& str) { glfwSetWindowTitle(str.c_str()); }

        //! Run.
        /*!
            This is one of the required functions of the render system. This should be called before
            all drawing functions and should be called once per frame. (perferably in a while loop).
        */
        const bool run();

        //! Get frames per second.
        /*!
            \return The average FPS over the total run time of the program.
        */
        inline const float getFPS() const { return ( float(frame) / float(fpstimer.getTicks()) ); }

        //! Get ticks.
        /*!
            \return The number of ticks (ms) that have occured since the engine started.
        */
        inline const double getTicks() const { return fpstimer.getTicks(); }

        //! Init system
        /*!
            Sets up everything needed by the render system. This should be called at the beginning of
            the program and is required to use any of the render system's functions.
            \param sc The size of the screen (default 640,480).
            \param fs Full screen (default false).
            \return True if it succeeded in creating a window & an opengl render context.
        */
        const bool initSystem( const PhVector2d& sc = PhVector2d(640,480),const bool& fs = false);

        //! Get screen size.
        /*!
            \return The size of the screen.
        */
        inline const PhVector2d& getScreenSize() const { return screensize; }

        //! Load texture.
        /*!
            Loads an image as a texture and adds it to the texture manager for garbage collection.
            Currently only .png files are supported. More formats are planned.
            \param filename The filename of the image to load.
            \param linear Tells the loader to use linear filtering or not. (default true).
            \note Use nearest filtering for tilemaps, or anything that may look bad when scaled.
            \note Textures must be sizes that are a power of two. NPOT textures will experience artifacts.
        */
        PhTexture* loadTexture( const std::string& filename , const bool& linear = true);

        //! Draw indexed trangle list.
        /*!
            Provides the ability to quickly draw an indexed triangle list to OpenGL.
            \param vertices The list of vertices in the triangle list.
            \param normals The list of normals for each vertex (this is usually just <0,0,1>).
            \param tcoords The list of texture coords for each vertex.
            \param colors The list of colors for each vertex.
            \param indexlist The list of each vertex that makes up each triangle.
            \param tricount The number of trangles.
            \sa drawIndexedTriangleFan(), drawIndexedLine()
        */
        void drawIndexedTriangleList(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, const int& tricount );

        //! Draw indexed trangle fan.
        /*!
            Provides the ability to quickly draw an indexed triangle fan to OpenGL.
            \param vertices The list of vertices in the triangle fan.
            \param normals The list of normals for each vertex (this is usually just <0,0,1>).
            \param tcoords The list of texture coords for each vertex.
            \param colors The list of colors for each vertex.
            \param indexlist The order of the vertices.
            \param vertcount The number of vertices.
            \sa drawIndexedTriangleList(), drawIndexedLine()
        */
        void drawIndexedTriangleFan(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, const int& vertcount );

        //! Draw indexed line.
        /*!
            Provides the ability to quickly draw an indexed line to OpenGL.
            \param vertices The list of vertices in the triangle list.
            \param normals The list of normals for each vertex (this is usually just <0,0,1>).
            \param tcoords The list of texture coords for each vertex.
            \param colors The list of colors for each vertex.
            \param indexlist The order of the vertices.
            \param vertcount The number of vertices.
            \sa drawIndexedTriangleFran(), drawIndexedTriangleList(), drawLine(), drawRay()
        */
        void drawIndexedLine(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, const int& vertcount );

		//! Draw line.
		/*!
			Draws a 2D line with a color for each vertex.
			\param v1 The vector to the first point of the line.
			\param v2 The vector to the second point of the line.
			\param depth The depth of the line.
			\param a Color of the first vertex.
			\param b Color of the second vertex.
			\sa drawRay()
		*/
		void drawLine(const PhVector2d& v1 = PhVector2d(0,0), const PhVector2d& v2 = PhVector2d(0,0), const float& depth = 0.0f, const PhColor& a = PhColor(255,255,255), const PhColor& b = PhColor(255,255,255,255));

		//! Draw ray.
		/*!
			Draws a 2D ray with a color for each vertex starting from the origin.
			\param origin The vector to the origin.
			\param ray The vector trepresentation of the ray.
			\param depth The depth of the ray.
			\param a Color of the first vertex.
			\param b Color of the second vertex.
			\sa drawLine()
		*/
		void drawRay(const PhVector2d& origin = PhVector2d(0,0), const PhVector2d& ray = PhVector2d(0,0), const float& depth = 0.0f, const PhColor& a = PhColor(255,255,255), const PhColor& b = PhColor(255,255,255,255));

		//! Draw rectangle.
        /*!
            Draws a rectangle with a color for each corner.
            \param r The rectangle to be drawn.
            \param depth The depth of the rectangle.
            \param a Color of the top-left corner.
            \param b Color of the top-right corner.
            \param c Color of the bottom-right corner.
            \param d Color of the bottom-left corner.
        */
        void drawRectangle( const PhRect& r = PhRect(0,0,0,0), const float& depth = 0.0f, const PhColor& a = PhColor(255,255,255), const PhColor& b = PhColor(255,255,255), const PhColor& c = PhColor(255,255,255), const PhColor& d = PhColor(255,255,255) );

        //! Draws a polygon.
        /*!
            Simply draws a polygon with the given depth and color.
            \param P Polygon to draw.
            \param depth Depth to draw it at.
            \param a Color to draw it with.
            \param textured If this is false, then texturing will be disabled while this polygon is draw. If it is enabled then the currently binded texture will be used.
        */
        void drawPolygon (const PhPolygon& P, const float& depth = 0.0f, const PhColor& a = PhColor(255,255,255));

        //! Draws a textured polygon.
        /*!
            Draws a polygon with the given depth and color and applies the given texture to the polygon.
            \param P Polygon to draw.
            \param texture The texture that will be applied to the polygon.
            \param depth Depth to draw it at.
            \param a Color to draw it with.
            \param eyespace If true, it generates texture coordinates in eyespace instead of object space.
        */
        void drawTexturedPolygon (const PhPolygon& P, PhTexture* texture, const float& depth = 0.0f, const PhColor& a = PhColor(255,255,255), const bool& eyespace = false);

        //! Draw texture.
        /*!
            \param source The texture to draw.
            \param pos Where to draw it at.
            \param depth The depth to draw it at.
            \param rot Rotation (in degrees).
            \param scale Scale.
            \param color Color.
            \param hflip If true, flip horizontally.
            \param vflip If true, vertically.
            \sa drawTexturePart()
        */
        void drawTexture( PhTexture* source, const PhVector2d& pos, const float& depth = 0.0f, const float& rot = 0.0f, const PhVector2d& scale = PhVector2d(1.0f,1.0f), const PhColor& color = PhColor(255,255,255), const bool& hflip = false, const bool& vflip = false);

        //! Draw texture part.
        /*!
            Draws a texture with a clipping rectangle.
            \param source The texture to draw.
            \param pos Where to draw it at.
            \param rect The clipping rectangle.
            \param depth The depth to draw it at.
            \param rot Rotation (in degrees).
            \param scale Scale.
            \param color Color.
            \param hflip If true, flip horizontally.
            \param vflip If true, vertically.
            \sa drawTexture()
        */
        void drawTexturePart( PhTexture* source, const PhVector2d& pos, const PhRect& rect, const float& depth = 0.0f, const float& rot = 0.0f, const PhVector2d& scale=PhVector2d(1.0f,1.0f), const PhColor& color=PhColor(255,255,255), const bool& hflip = false, const bool& vflip =false);

        //! Draw text
        /*!
            Draws a texture using the current font.
            \param text The text to draw.
            \param pos Where to draw it at.
            \param color The color of the font.
            \param depth The depth to draw it at.
            \sa loadFont()
        */
        void drawText( const std::string& text, const PhVector2d& pos, const PhColor& color=PhColor(255,255,255), const float& depth = 0.0f);

        //! Set font.
        /*!
            Sets the font to the given texture.
            \param t The new font.
            \sa getFont()
        */
        inline void setFont( PhTexture* t ) { font = t; }

        //! Get font.
        /*!
            \return The current textured used as a font.
            \sa setFont()
        */
        inline PhTexture* getFont() const { return font; }

        //! Get event handler.
        /*!
            \return A pointer to the event handler used by the system.
        */
        inline PhEventHandler* getEventHandler() const { return events; }

        //! Get texture manager.
        /*!
            \return A pointer to the texture manager.
        */
        inline PhTextureManager* getTextureManager() const { return textures; }

        //! Get log manager.
        /*!
        	\return A pointer to the log manager.
        */
        inline PhLogManager* getLogManager() const { return logs; }

        //! Get vertex light system.
        /*!
        	\return A pointer to vertex light system.
        */
        inline PhVertexLightSystem* getVertexLightSystem() const { return vlsys; }

        //! Set vertex light system.
        /*!
			Allows you to change the light system to another
        */
        inline void setVertexLightSystem( PhVertexLightSystem* v ) { vlsys = v; }

        //! Set blend mode.
        /*!
            Sets the blend mode for opengl. The defualt blend mode is GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA.
            \param src The source factor, can be GL_ZERO, GL_ONE,
            GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
            GL_ONE_MINUS_DST_ALPHA, and GL_SRC_ALPHA_SATURATE
            \param dst The destination factor, can be GL_ZERO, GL_ONE,
            GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, and
            GL_ONE_MINUS_DST_ALPHA
            \sa setDefaultBlendMode()
        */
        inline void setBlendMode(const GLenum& src, const GLenum& dst) { glBlendFunc(src,dst); }

        //! Set defualt blend mode.
        /*!
            Restores the engine to it's default blend mode (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA).
            \sa setBlendMode()
        */
        inline void setDefaultBlendMode() { setBlendMode(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); }

        //! Set vertex light state.
        /*!
			Enables or disables vertex lighting.
        */
        inline void setVertexLighting(const bool& a)
        {
			if (a)
			{
				glEnable(GL_LIGHTING);
				vertexlighting = true;
			}
			else
			{
				glDisable(GL_LIGHTING);
				vertexlighting = false;
			}
		}

        //! Get vertex light state.
        /*!
			Gets the current state of vertex lighting.
        */
        const bool& getVertexLighting() const { return vertexlighting; }

    };

}

#endif
