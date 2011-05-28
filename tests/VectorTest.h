/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#include "Phoenix.h"

using namespace phoenix;

class VectorTest
{
    public:

        VectorTest() : 
			system()
        {
            system.setResizeBehavior(RZB_EXPAND);
        }

        virtual ~VectorTest()
        {
        }

        int run()
        {

            //! Vector of Vectors.
            std::vector<Vector2d> vectorlist;

            //! Add some vectors backwards.
            for( int i = 360; i>0; i-=45 )
            {
                vectorlist.push_back( Vector2d( 100, 0 ).rotate( DegreesToRadians( (float) i ) ) );
            }

            //! Sort them.
            std::sort( vectorlist.begin(), vectorlist.end(), &Vector2d::AngleSort );


            //! Now just draw some stuff.
            while( system.run() )
            {

                //! Events

                if(EventReceiver::Instance()->getMouseButtonPressed(PHK_MB_LEFT) )
                {
                    vectorlist.push_back(EventReceiver::Instance()->getMousePosition() - Vector2d(320,240) );
                    std::sort( vectorlist.begin(), vectorlist.end(), &Vector2d::AngleSort );
                }

                //! Draw stuff
                Vector2d MouseVector = EventReceiver::Instance()->getMousePosition() -  Vector2d(320,240);

                system.drawRay( Vector2d(320,240), MouseVector );


                //! Draw the vector of vectors
                for( unsigned int i = 0; i < vectorlist.size(); ++i )
                {
					system.drawRay( Vector2d(320,240), vectorlist[i], Color(255,255,255).interpolate( Color(255,127,127), (float)i*4 ), Color(127,255,127).interpolate( Color(127,127,255), (float)i*4 ) );
                    char tbuffer[32];
                    sprintf(tbuffer,"%i",i);
                    system.drawText( tbuffer, Vector2d(320,240)+vectorlist[i] * 1.1f - Vector2d(8,8), Color(127,255,127).interpolate( Color(127,127,255), (float)i*4 ) );
                }

                //! Draw some info.
                system.drawText( "Vector Test", Vector2d(16,16) );

                system.getDebugConsole()<<"\nNumber of Vectors: "<<vectorlist.size();
                system.getDebugConsole()<<"\nFrames Per Second: "<<system.getFPS();

            }

            return 0;

        }// Run

    protected:
        RenderSystem system;
    private:
};


