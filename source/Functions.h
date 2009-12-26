/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHOENIXFUNCS__
#define __PHOENIXFUNCS__

#include <cstdlib> //For rand()

namespace phoenix
{

    //! Random function.
	/*!
		\param low The lowest possible value.
		\param high The highest possible value.
		\return A pseudo random value between low and high.
	*/
	///random function
	int random(int low,int high)
	{
		return ( rand() % (high - low + 1) + low);
	}

} //namespace phoenix

#endif //__PHOENIXFUNCS__
