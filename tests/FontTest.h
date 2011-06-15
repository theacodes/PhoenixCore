/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "Phoenix.h"
#include "BMFontLoader.h"

using namespace phoenix;

class FontTest
{
    public:

        FontTest() : system()
        {
        }

        virtual ~FontTest()
        {
        }

        int run()
        {

			//! Test
			FontPtr font = system.getFont();

			//! Font
            BitmapFontPtr bluefont = new BitmapFont( system, "arial.fnt" );

			bluefont->setColor( Color(200,200,255) );
			bluefont->setScale( Vector2d(5, 2.5) );
			BatchGeometryPtr hellotext = bluefont->drawText( "Hello, \nWorld!", Vector2d( 50,50 ) );
			hellotext->setImmediate( false );


            //! Now just draw some stuff.
            while( system.run() )
            {

				system.getDebugConsole()<<"\n"<<system.getFPS();

				hellotext->rotate( 0.001f );

                //! Draw some info.
				font->setScale( Vector2d( 0.75f, 0.75f ) );
                font->drawText( "Font Test \nKerning, anyone? lorem ipsum. \nMulti-line text FTW!", Vector2d(16,16), Color(127,127,255) );

				Vector2d dim = font->getTextDimensions("Font Test \nKerning, anyone? lorem ipsum.\nMulti-line text FTW!");

				system.drawRectangle( phoenix::Rectangle( Vector2d(16,16), dim ) )->colorize( Color(127,127,127,120) );

				std::stringstream strm;
				strm<<"Width: "<<dim.getX()<<"\nHeight: "<<dim.getY();

				font->drawText( strm.str(), Vector2d(16,300) );

				//font->drawText( "", Vector2d(16,64) )->colorize(Color(255,0,0));

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};