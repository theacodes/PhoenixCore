/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/
#ifdef MSVC
#ifndef ENABLECONSOLE
#include <windows.h>
#endif
#endif
#include <iostream>
#include <cstdio>

#ifdef _TESTS_TEXTURE_
	#include "TextureTest.h"
#endif
#ifdef _TESTS_EVENT_
	#include "EventTest.h"
#endif
#ifdef _TESTS_POLYGON_
	#include "PolygonTest.h"
#endif
#ifdef _TESTS_VECTOR_
	#include "VectorTest.h"
#endif
#ifdef _TESTS_RESOURCE_
	#include "ResourceTest.h"
#endif
#ifdef _TESTS_VIEW_
	#include "ViewTest.h"
#endif
#ifdef _TESTS_FONT_
	#include "FontTest.h"
#endif
#ifdef _TESTS_DEMO_
	#include "Demo.h"
#endif

#include "AbstractGarbageCollector.h"
#include <boost/function.hpp>

int main()
{

#ifdef _TESTS_TEXTURE_
		TextureTest test;
#endif
#ifdef _TESTS_EVENT_
		EventTest test;
#endif
#ifdef _TESTS_POLYGON_
		PolygonTest test;
#endif
#ifdef _TESTS_VECTOR_
		VectorTest test;
#endif
#ifdef _TESTS_RESOURCE_
		ResourceTest test;
#endif
#ifdef _TESTS_VIEW_
		ViewTest test;
#endif
#ifdef _TESTS_FONT_
		FontTest test;
#endif
#ifdef _TESTS_DEMO_
		Demo test;
#endif

		test.run();

        return 0;
}


//! MSVC WinMain
#ifdef MSVC
#ifndef ENABLECONSOLE
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR Args, int WinMode) {
    return main();
}
#endif
#endif