/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "EventReceiver.h"

using namespace phoenix;

//! Singleton Instance.
boost::shared_ptr<EventReceiver> EventReceiver::instance = boost::shared_ptr<EventReceiver>();

////////////////////////////////////////////////////////////////////////////////
// Resets arrays
////////////////////////////////////////////////////////////////////////////////

void EventReceiver::resetArrays( const bool all ){
	 for (int i=0;i<512;i++)
    {
        if( all == true ) keys[i]=0;
        keysdown[i]=0;
    }

    for (int i=0;i<16;i++)
    {
        if( all == true ) mousebutton[i]=0;
        mousebuttondown[i]=0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// On event
////////////////////////////////////////////////////////////////////////////////
void EventReceiver::onWindowEvent( const WindowEvent& e )
{
	switch( e.type ){

		case WET_UPDATE:
			resetArrays();
			break;

		case WET_KEY:
			{
				if( e.key > 15 ) //Keyboard
				{
					if (e.state == true) {
						keysdown[e.key]=true;
						keys[e.key]=true;

						//backspace for keyboard strings.
						if( e.key == PHK_BACKSPACE ){
							keyboardstring = keyboardstring.substr(0, keyboardstring.length() - 1);
						}

					} else {
						keys[e.key] = false;
						keysdown[e.key] = true;
					}
				}else{ //Mouse
					if ( e.state == true ) {
						mousebutton[ e.key ]=true;
						mousebuttondown[ e.key ]=true;
					} else if ( e.state == false) {
						mousebutton[ e.key ] = false;
						mousebuttondown[ e.key ]=true;
					}
				}
			} break;

		case WET_CHAR:
			{
				keyboardstring += e.key;
			}break;

		case WET_MOUSE_POSITION:
			{
				mousepos = e.mouse_position;
			}break;

		case WET_MOUSE_WHEEL:
			{
				mousewheelpos = e.mouse_wheel;
			}

		default:
			break;
	}
}