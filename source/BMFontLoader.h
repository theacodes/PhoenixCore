/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHBITMAPFONTLDR_H__
#define __PHBITMAPFONTLDR_H__

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <boost/tokenizer.hpp>
#include "config.h"
#include "BitmapFont.h"

namespace phoenix
{

//! BMFont Text format Loader
/*!
    This class provides means to load a font created by AngelCode's BMFont tool.
*/
class BMFontLoader
{

public:
	BMFontLoader( BitmapFontPtr _font )
		: font(_font)
	{};

	void load( const std::string& fnt_file );

private:
	BitmapFontPtr font;

};

} //namespace phoenix
#endif // __PHBITMAPFONTLDR_H__