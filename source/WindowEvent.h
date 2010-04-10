/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHWINDOWEVENT_H__
#define __PHWINDOWEVENT_H__

#include "config.h"
#include "Vector2d.h"
#include "Keys.h"

namespace phoenix{

//! Window Events Types
enum E_WINDOWEVENT_TYPE{
	WET_KEY, //!< Keyboard and mouse button events
	WET_CHAR, //!< Keyboard character event
	WET_MOUSE_POSITION, //!< Mouse position change
	WET_MOUSE_WHEEL, //!< Mouse wheel change
	WET_CLOSE, //!< Window close event
	WET_UPDATE, //!< Window update event
	WET_RESIZE //!< Window Resize Event.
};

struct WindowEvent{ 
	E_WINDOWEVENT_TYPE type;
	int int_data; //!< used for keys, etc.
	bool bool_data; //!< used for keystates. false for released, true for pressed
	Vector2d vector_data; //!< used for mouse position, window size, etc.
};

}//namespace phoenix

#endif //__PHWINDOWEVENT_H__