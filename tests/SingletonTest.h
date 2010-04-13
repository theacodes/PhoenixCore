/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "Phoenix.h"

using namespace phoenix;

class SingletonTest
{
    public:

        SingletonTest() : system(), changed(false)
        {
			system = RenderSystem::Initialize();
        }

        virtual ~SingletonTest()
        {
        }

        int run()
        {


            //! Now just draw some stuff.
            while( system->run() )
            {

                //! Draw some info.
				if( !changed )
					system->drawText( "Press space to change the rendersystem.", Vector2d(16,16) );
				else
					system->drawText( "Ta-da!", Vector2d(16,16) );

				if( !changed && EventReceiver::Instance()->getKeyPressed( PHK_SPACE ) ){
					try{

						system = RenderSystemPtr();
						if( ! RenderSystem::Release() ) throw std::exception( "Not unique instance!" );
						system = RenderSystem::Initialize( Vector2d( 800,600 ) );
						std::cout<< system->getFont()->getTexture()->getName() << system->getFont()->getTexture()->getTextureId() << std::endl;

					}catch( std::exception e ){
						std::cout<< e.what() << std::endl;
						throw;
					}catch( RenderSystem::BadInstance e ){
						std::cout<<"Bad instance"<<std::endl;
						throw;
					}catch( WindowManager::BadInstance e ){
						std::cout<<"Window manager bad instance."<<std::endl;
						throw;
					}
				}


            }

            return 0;

        }// Run

    protected:
        RenderSystemPtr system;
		bool changed;
    private:
};