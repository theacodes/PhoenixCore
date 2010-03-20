/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHOENIXKEYS__
#define __PHOENIXKEYS__

#include <GL/glfw.h>
#include "config.h"

namespace phoenix
{

    //! Mouse button definitions
    /*!
    	Defines mouse buttons for the event receiver.
    	\sa EventReceiver
    */
    enum MouseButton
    {
        PHK_MB_LEFT     =   GLFW_MOUSE_BUTTON_LEFT,
        PHK_MB_RIGHT	=   GLFW_MOUSE_BUTTON_RIGHT,
        PHK_MB_MIDDLE   =   GLFW_MOUSE_BUTTON_MIDDLE
    };

    //! Keyboard key definitions
    /*!
    	Defines keyboard keys for the event receiver.
    	\sa EventReceiver
    */
    enum Key
    {
        PHK_A					='A',
        PHK_B					='B',
        PHK_C					='C',
        PHK_D					='D',
        PHK_E					='E',
        PHK_F					='F',
        PHK_G					='G',
        PHK_H					='H',
        PHK_I					='I',
        PHK_J					='J',
        PHK_K					='K',
        PHK_L					='L',
        PHK_M					='M',
        PHK_N					='N',
        PHK_O					='O',
        PHK_P					='P',
        PHK_Q					='Q',
        PHK_R					='R',
        PHK_S					='S',
        PHK_T					='T',
        PHK_U					='U',
        PHK_V					='V',
        PHK_W					='W',
        PHK_X					='X',
        PHK_Y					='Y',
        PHK_Z					='Z',
        PHK_0					='0',
        PHK_1					='1',
        PHK_2					='2',
        PHK_3					='3',
        PHK_4					='4',
        PHK_5					='5',
        PHK_6					='6',
        PHK_7					='7',
        PHK_8					='8',
        PHK_9					='9',
        PHK_BACKTICK            ='`',
        PHK_RIGHTBRACKET        ='[',
        PHK_LEFTBRACKET         =']',
        PHK_SEMICOLON           =';',
        PHK_QUOTE               ='\'',
        PHK_BACKSLASH           ='\\',
        PHK_EQUAL               ='=',
        PHK_MINUS               ='-',
        PHK_SPACE				=GLFW_KEY_SPACE,
        PHK_ESC					=GLFW_KEY_ESC,
        PHK_F1					=GLFW_KEY_F1,
        PHK_F2					=GLFW_KEY_F2,
        PHK_F3					=GLFW_KEY_F3,
        PHK_F4					=GLFW_KEY_F4,
        PHK_F5					=GLFW_KEY_F5,
        PHK_F6					=GLFW_KEY_F6,
        PHK_F7					=GLFW_KEY_F7,
        PHK_F8					=GLFW_KEY_F8,
        PHK_F9					=GLFW_KEY_F9,
        PHK_F10					=GLFW_KEY_F10,
        PHK_F11					=GLFW_KEY_F11,
        PHK_F12					=GLFW_KEY_F12,
        PHK_F13					=GLFW_KEY_F13,
        PHK_F14					=GLFW_KEY_F14,
        PHK_F15					=GLFW_KEY_F15,
        PHK_F16					=GLFW_KEY_F16,
        PHK_F17					=GLFW_KEY_F17,
        PHK_F18					=GLFW_KEY_F18,
        PHK_F19					=GLFW_KEY_F19,
        PHK_F20					=GLFW_KEY_F20,
        PHK_F21					=GLFW_KEY_F21,
        PHK_F22					=GLFW_KEY_F22,
        PHK_F23					=GLFW_KEY_F23,
        PHK_F24					=GLFW_KEY_F24,
        PHK_F25					=GLFW_KEY_F25,
        PHK_UP					=GLFW_KEY_UP,
        PHK_DOWN				=GLFW_KEY_DOWN,
        PHK_LEFT				=GLFW_KEY_LEFT,
        PHK_RIGHT				=GLFW_KEY_RIGHT,
        PHK_LSHIFT				=GLFW_KEY_LSHIFT,
        PHK_RSHIFT				=GLFW_KEY_RSHIFT,
        PHK_LCTRL				=GLFW_KEY_LCTRL,
        PHK_RCTRL				=GLFW_KEY_RCTRL,
        PHK_LALT				=GLFW_KEY_LALT,
        PHK_RALT				=GLFW_KEY_RALT,
        PHK_TAB					=GLFW_KEY_TAB,
        PHK_ENTER				=GLFW_KEY_ENTER,
        PHK_BACKSPACE			=GLFW_KEY_BACKSPACE,
        PHK_INSERT				=GLFW_KEY_INSERT,
        PHK_DEL					=GLFW_KEY_DEL,
        PHK_PAGEUP				=GLFW_KEY_PAGEUP,
        PHK_PAGEDOWN			=GLFW_KEY_PAGEDOWN,
        PHK_HOME				=GLFW_KEY_HOME,
        PHK_END					=GLFW_KEY_END,
        PHK_KP_0				=GLFW_KEY_KP_0,
        PHK_KP_1				=GLFW_KEY_KP_1,
        PHK_KP_2				=GLFW_KEY_KP_2,
        PHK_KP_3				=GLFW_KEY_KP_3,
        PHK_KP_4				=GLFW_KEY_KP_4,
        PHK_KP_5				=GLFW_KEY_KP_5,
        PHK_KP_6				=GLFW_KEY_KP_6,
        PHK_KP_7				=GLFW_KEY_KP_7,
        PHK_KP_8				=GLFW_KEY_KP_8,
        PHK_KP_9				=GLFW_KEY_KP_9,
        PHK_KP_ADD				=GLFW_KEY_KP_ADD,
        PHK_KP_SUBTRACT			=GLFW_KEY_KP_SUBTRACT,
        PHK_KP_DIVIDE			=GLFW_KEY_KP_DIVIDE,
        PHK_KP_MULTIPLY			=GLFW_KEY_KP_MULTIPLY,
        PHK_KP_DECIMAL			=GLFW_KEY_KP_DECIMAL,
        PHK_KP_EQUAL			=GLFW_KEY_KP_EQUAL,
        PHK_KP_ENTER			=GLFW_KEY_KP_ENTER
    };

} //namespace phoenix

#endif //__PHOENIXKEYS__
