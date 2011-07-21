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

            //! Now just draw some stuff.
            while( system.run() )
            {

                //! Draw some info.
                system.drawText( "Shader Test", Vector2d(16,16) );

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};


