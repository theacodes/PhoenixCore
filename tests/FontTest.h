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
			BitmapFontPtr font = new BitmapFont( system, "droid sans mono.fnt" );

			system.getDebugConsole().setFont( font );

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
                font->drawText( "Font Test \nKerning, anyone? lorem ipsum. \nMulti-line text FTW!", Vector2d(16,16) )->colorize(Color(127,127,255));
				//font->drawText( "", Vector2d(16,64) )->colorize(Color(255,0,0));

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};