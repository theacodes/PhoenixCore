/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "Phoenix.h"

using namespace phoenix;
using namespace std;

class TextureTest
{
    public:

        TextureTest() : system( )
        {
        }

        virtual ~TextureTest()
        {
        }

        /*!
            This actually runs this test. It verifies:
            *) That the default font is loaded and named correctly.
            *) That TextureManager (and ResourceManager) can find textures correctly.
            *) That textures can be manipulated.
            *) That the system can draw the texture.
        */
        int run()
        {

            //print out all the resources
            BOOST_FOREACH( ResourcePtr& resource, system.getResourceManager().getList() )
            {
                system.getDebugConsole()<<"\n Resource "<<resource.get()<<" with name '"<<resource->getName()<<"'";
            }

            //! Print out the font texture's name.
            system.getDebugConsole()<<"\nFont Name: "<<system.getFont()->grab<BitmapFont>()->getTexture()->getName()<<" Pointer: "<< system.getFont().get();

            //! Find the font texture in the resource manager.
            TexturePtr testfind = system.findTexture( "deffont.png" );

            //! Print out if we actually found a texture.
            system.getDebugConsole()<<"\nTest find is valid: "<< testfind;

            //! If we did, print out the name ( should be deffont.png ).
            if(testfind)
            {
                system.getDebugConsole()<<"\nFound font name: "<<testfind->getName();
            }

            //! Now see if we can manipulate textures.
            testfind->lock();
            for( unsigned int i = 0; i < testfind->getSize().getX(); ++i )
            {
                for( unsigned int j = 0; j < testfind->getSize().getY(); ++j)
                {
                    if( testfind->getPixel( Vector2d( (float) i, (float) j) ).getAlpha() < 100 )
                    {
                        testfind->setPixel( Vector2d( (float) i, (float) j), Color(100,200,255,25) );
                    }
                }
            }
            testfind->unlock();

            //! Now see if we can create a custom texture.
            TexturePtr newtexture = new Texture( system.getResourceManager(), Vector2d(512,512) );

            //! Tell me something about it.
            system.getDebugConsole()<<"\nNew texture name: "<<newtexture->getName()<<"Size: "<<newtexture->getSize().getX()<<","<<newtexture->getSize().getY();

            //! Now lets put some color in it!
            newtexture->lock();
            for( unsigned int i = 0; i < newtexture->getSize().getX(); ++i )
            {
                for( unsigned int j = 0; j < newtexture->getSize().getY(); ++j)
                {
                    newtexture->setPixel( Vector2d( (float)i, (float)j ), Color( i,i*2, j) );
                }
            }
            newtexture->unlock();

            //! Now just for fun, how about a render texture?
            BatchRenderer tbatch; // we need a separate renderer for it.
            GraphicsFactory2d tfactory( tbatch ); //and factory.
            RenderTexturePtr rendertexture = new RenderTexture( system.getResourceManager(), tbatch, Vector2d(256,256));
            system.getDebugConsole()<<"\nRender Target Size: "<<rendertexture->getSize().getX()<<","<<rendertexture->getSize().getY();
            system.getDebugConsole()<<"\nRender Target Texture ID: "<<rendertexture->getTextureId();


            //! Now just draw some stuff.
            while( system.run() )
            {   

                

                //! Draw some text to it.
                rendertexture->start();
                tfactory.drawRectangle( phoenix::Rectangle(50,50,150,150), Color(255,0,0) );
                tbatch.draw();
                rendertexture->end();

                //! Draw our textures and some info
                system.drawTexture( newtexture, Vector2d(32,32), 0.0f, Vector2d(1,1), Color(255,255,255,255), ( EventReceiver::getKey(PHK_Q) ? EGF_HFLIP : EGF_NONE )&( EventReceiver::getKey(PHK_W) ? EGF_VFLIP : EGF_NONE ) );
                system.setDepth( 1.0f );
                system.drawTexturePart( system.getFont()->grab<BitmapFont>()->getTexture() , Vector2d(32,32), phoenix::Rectangle( EventReceiver::getMousePosition() , Vector2d( 256,256 ) ), 0.0f, Vector2d(1,1), Color(), ( EventReceiver::getKey(PHK_Q) ? EGF_HFLIP : EGF_NONE )&( EventReceiver::getKey(PHK_W) ? EGF_VFLIP : EGF_NONE ) );
                system.drawTexture( rendertexture, EventReceiver::getMousePosition(), 0.0f, Vector2d(2,2), Color(255,255,255), EGF_VFLIP );
                
                system.drawText( "Texture Test: you should see white text", Vector2d(16,16) );
                system.drawText( "with a semi-transparent blue background.", Vector2d(16,32) );
                system.drawText( "You should see a multicolored texture below.", Vector2d(16,48) );
                system.setDepth( 0.0f );


            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};
