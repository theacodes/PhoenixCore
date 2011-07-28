/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#include "Phoenix.h"

using namespace phoenix;

class ShaderTest
{
    public:

        ShaderTest() : 
			system()
        {
        }

        virtual ~ShaderTest()
        {
        }

        int run()
        {

			//! Load the picture
			TexturePtr picture = system.loadTexture("picture.jpg");

			//! Create a basic shader
			ShaderPtr regular_shader  = new Shader( system.getResourceManager() );
			regular_shader->load("vertex.glsl","fragment.glsl");
			
			if( !regular_shader->ready() ){
				std::cout<<regular_shader->getErrors();
			} else {
				system.getBatchRenderer().setShader( regular_shader );
			}

            //! Now just draw some stuff.
            while( system.run() )
            {

                //! Draw some info.
                system.drawText( "Shader Test", Vector2d(16,16) )->colorize( Color(127,127,255,127) );

				system.drawTexture( picture, (system.getView().getSize()/2) - (picture->getSize()/2) );

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};


