#include "WindowManager.h"

using namespace phoenix;

Vector2d WindowManager::screensize = Vector2d(0,0);
boost::function< void (Vector2d) > WindowManager::resizefunc( &WindowManager::noResizeCallback );