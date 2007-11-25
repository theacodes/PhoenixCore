/*

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

#ifndef PHOENIXRS
#define PHOENIXRS

#include "SDL/SDL.h"
#include "SDL/SDL_Image.h" //SDL's image loader
#include "SDL/SDL_OpenGL.h"
#include <gl/glu.h>
#include "PhTextureManager.h"
#include "PhTimer.h"
#include "PhVector2d.h"
#include "PhEventHandle.h"
#include "PhRect.h"
#include "PhPolygon.h"

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
        This is the heart of phoenix. On the basic level it provides a layer over OpenGL. It also provides
        many facilities needed for 2D games.
    */
    class PhRenderSystem
    {

    private:

        //This is a pointer to the screen
        SDL_Surface* screen;

        //Event handler
        PhEventHandler* events;

        //Texture manager
        PhTextureManager* textures;

        //Timer for FPS and getTicks()
        PhTimer fpstimer;

        //Counts the number of frames, width, height
        int frame;

        //stores the size of the screen
        PhVector2d screensize;

        //The font used to draw text
        PhTexture* font;

        //determines if lighting is enable
        bool lighting;

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
        void setWindowCaption(std::string str);

        //! Run.
        /*!
            This is one of the required functions of the render system. This should be called before
            all drawing functions and should be called once per frame. (perferably in a while loop).
        */
        bool run();

        //! Get frames per second.
        /*!
            \return The average FPS over the total run time of the program.
        */
        float getFPS();

        //! Get ticks.
        /*!
            \return The number of ticks (ms) that have occured since the engine started.
        */
        int getTicks();

        //! Init system
        /*!
            Sets up everything needed by the render system. This should be called at the beginning of
            this program and is required to use any of the render system's functions.
            \param sc The size of the screen (defualt 640,480).
        */
        bool initSystem( PhVector2d sc = PhVector2d(640,480) );

        //! Get screen size.
        /*!
            \return The size of the screen.
        */
        PhVector2d getScreenSize();

        //! Load texture.
        /*!
            Loads an image as a and adds it to the texture manager for garbage collection.
            Currently on RGBA .png files are supported. DevIL implementation is planned, no
            other file formats will be officially supported until then.
            \param filename The filename of the image to load.
            \param linear Tells the loader to use linear filtering or not. (default false).
        */
        PhTexture* loadTexture( std::string filename , bool linear = false);

        //! Draw indexed trangle list.
        /*!
            Provides the ability to quickly draw an indexed triangle list to OpenGL.
            \param vertices The list of vertices in the triangle list.
            \param normals The list of normals for each vertex (this is usually just <0,0,1>).
            \param tcoords The list of texture coords for each vertex.
            \param colors The list of colors for each vertex.
            \param indexlist The list of each vertex that makes up each triangle.
            \param tricount The number of trangles.
            \todo Add drawIndexedTriangleFan()
        */
        void PhRenderSystem::drawIndexedTriangleList(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, int tricount );

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
        void drawRectangle( PhRect r = PhRect(0,0,0,0), float depth = 0.0f, PhColor a = PhColor(255,255,255), PhColor b = PhColor(255,255,255), PhColor c = PhColor(255,255,255), PhColor d = PhColor(255,255,255) );

        //! Draws a polygon.
        /*!
            Simply draws a polygon with the given depth and color.
            \param P Polygon to draw.
            \param depth Depth to draw it at.
            \param a Color to draw it with.
        */
        void drawPolygon (PhPolygon P, float depth = 0.0f, PhColor a = PhColor(255,255,255));

        //! Draw vector.
        /*!
            Draws the given vector starting from the origin.
            \param origin The place to start from.
            \param vect The vector to draw.
            \note You must set an active color before calling this function.
            \sa drawVector2()
        */
        void drawVector(PhVector2d origin,PhVector2d vect);

        //! Draw vector 2.
        /*!
            Draws a line from origin to vect.
            \param origin The place to start from.
            \param vect The place to end.
            \note You must set an active color before calling this function.
            \sa drawVector()
        */
        void drawVector2(PhVector2d origin,PhVector2d vect);

        //! Draw texture.
        /*!
            \param source The texture to draw.
            \param pos Where to draw it at.
            \param depth The depth to draw it at.
            \param rot Rotation (in degrees).
            \param scale Scale.
            \param color Color.
            \param flip If true, flip horizontally.
            \sa drawTexturePart()
        */
        void drawTexture( PhTexture* source, PhVector2d pos, float depth = 0.0f, float rot = 0.0f, float scale = 1.0f, PhColor color=PhColor(255,255,255), bool flip = false);

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
            \param flip If true, flip horizontally.
            \sa drawTexture()
        */
        void drawTexturePart( PhTexture* source, PhVector2d pos, PhRect rect,  float depth = 0.0f, float rot = 0.0f, float scale = 1.0f, PhColor color=PhColor(255,255,255), bool flip = false);

        //! Draw text
        /*!
            Draws a texture using the current font.
            \param text The text to draw.
            \param pos Where to draw it at.
            \param color The color of the font.
            \param depth The depth to draw it at.
            \sa loadFont()
        */
        void drawText( std::string text, PhVector2d pos, PhColor color=PhColor(255,255,255), float depth = 0.0f);

        //! Set font.
        /*!
            Sets the font to the given texture.
            \param t The new font.
            \sa getFont()
        */
        void setFont( PhTexture* t );

        //! Get font.
        /*!
            \return The current textured used as a font.
            \sa setFont()
        */
        PhTexture* getFont();

        //! Get event handler.
        /*!
            \return A pointer to the event handler used by the system.
        */
        PhEventHandler* getEventHandler();

        //! Get texture manager.
        /*!
            \return A pointer to the texture manager.
        */
        PhTextureManager* getTextureManager();

        void setLighting(bool a);
        bool getLighting();

    };

}

#endif
