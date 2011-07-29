/*!
	PhoenixCore Config File.
*/
#ifndef __PHOENIXCORE_CONFIG_H__
#define __PHOENIXCORE_CONFIG_H__

// Version Name/Number/Release.
#define PHOENIXCORE_VERSION "PhoenixCore 0.3 Raven"
#define PHEONIXCORE_VERSION_NUMBER "0.3"
#define PHEONIXCORE_VERSION_NAME "Raven"

// OpenGL Include
#include "glew/GL/glew.h"
#include <GL/glfw.h>

//! Define this to use the default GLFW Window Manager, or set to 0 to not compile the GLFW window manager.
/*!
	\note If this is 0, the system will not have a window manager, your custom window manager must be Instance()'d before calling RenderSystem(); 
*/
#define PH_USE_GLFW 1

#endif //__PHOENIXCORE_CONFIG_H__