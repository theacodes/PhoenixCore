/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "Phoenix.h"

using namespace phoenix;

class EventTest
{
    public:

        EventTest() : system()
        {
        }

        virtual ~EventTest()
        {
        }

        /*!
            This actually runs this test. It verifies:
            *) That the event receiver is handling keyboard events.
            *) That the event receiver is handling mouse events.
        */
        int run()
        {

            //! We'll make our font have a colored background, so we can see certain keys when they're pressed.

            // duplicate the system's font.
            TexturePtr newfonttexture = system.getFont()->getTexture()->copy();
            BitmapFontPtr newfont = new BitmapFont( system.getResourceManager(), system, newfonttexture );
            
            // run through and change the background color.
            newfont->getTexture()->lock();
            for( unsigned int i = 0; i < newfont->getTexture()->getSize().getX(); ++i )
            {
                for( unsigned int j = 0; j < newfont->getTexture()->getSize().getY(); ++j)
                {
                    if( newfont->getTexture()->getPixel( Vector2d( (float) i, (float) j) ).getAlpha() < 100 )
                    {
                        newfont->getTexture()->setPixel( Vector2d( (float) i, (float) j), Color(255,255,255,150) );
                    }
                }
            }
            newfont->getTexture()->unlock();

            //! Now just draw some stuff.
            while( true )
            {

                //! limit to 30fps
                if( system.getTime() < 1.0f/30.0f ) continue;

                // Run the system
                if( ! system.run() )
                    break;

                //! For every possible one of the 256 keys, we'll draw a little icon if they've been pressed or not
                for( unsigned char i = 0; i < 16; ++i)
                {
                    for( unsigned char j = 0; j <16; ++j)
                    {
                        Color textcolor;

                        //! If it's down, we'll set the color to blue
                        if(EventReceiver::getKey( Key((j*16)+i) ) ) textcolor = Color(200,200,255);
                        //! If it's up, we'll set the color to gray
                        if( !EventReceiver::getKey( Key((j*16)+i) ) ) textcolor = Color(255,255,255,150);
                        //! If it was just pressed, make it white
                        if(EventReceiver::getKeyPressed( Key((j*16)+i) ) ) textcolor = Color(255,255,255);
                        //! If it was just released, make it red.
                        if(EventReceiver::getKeyReleased( Key((j*16)+i) ) ) textcolor = Color(255,200,200);

                        //! Draw it
                        //use our custom font.
                        newfont->setColor( textcolor );
                        newfont->drawText( "O", Vector2d(200,200)+Vector2d( (float) i*16, (float) j*16 ));
                    }
                }

                //! Draw an @ symbol where the mouse is, and once again use our custom font to do it.
                Color textcolor = Color(255,0,0);
                if(EventReceiver::getMouseButton( PHK_MB_LEFT ) ) textcolor = Color(0,255,0);
                if(EventReceiver::getMouseButton( PHK_MB_RIGHT ) ) textcolor = Color(0,0,255);
                if(EventReceiver::getMouseButton( PHK_MB_MIDDLE ) ) textcolor = Color(255,255,255);
                newfont->setColor( textcolor );
                newfont->drawText( "@",EventReceiver::getMousePosition() );

                //! Draw some info.
                system.drawText( "Event Test: Below is an ASCII Table", Vector2d(16,16) );
                system.drawText( "Not all will change, but you should be able", Vector2d(16,32) );
                system.drawText( "make some pretty colors by mashing keys.", Vector2d(16,48) );

			    system.getDebugConsole()<<"\nGeoms "<<system.geometryCount()<<", FPS: "<<system.getFPS();

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};
