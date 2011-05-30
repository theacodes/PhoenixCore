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
			BitmapFontPtr font = new BitmapFont( system, "arial.fnt" );

			//! Font
            BitmapFontPtr bluefont = new BitmapFont( system, "arial.fnt" );

			bluefont->setColor( Color(200,200,255) );
			bluefont->setScale( Vector2d(5, 2.5) );
			BatchGeometryPtr hellotext = bluefont->drawText( "Hello, World!", Vector2d( 50,50 ) );
			hellotext->setImmediate( false );


            //! Now just draw some stuff.
            while( system.run() )
            {

				hellotext->rotate( 0.001f );

                //! Draw some info.
                font->drawText( "Font Test", Vector2d(16,16) );

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};