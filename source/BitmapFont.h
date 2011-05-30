/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHBITMAPFONT_H__
#define __PHBITMAPFONT_H__

#include <boost/unordered_map.hpp>
#include "config.h"
#include "Font.h"
#include "BatchRenderer.h"
#include "BatchGeometry.h"

namespace phoenix
{

//! Bitmap Font
/*!
    This class provides a simple interface to draw fonts based on textures containing a glyph for all 256
    characters. A built-in texture is supplied for the default font used by RenderSystem.
*/
class BitmapFont
    : public Font
{
public:

	//! Structure to hold information about each character
	struct Character{
		int x;
		int y;
		int width;
		int height;
		int xoffset;
		int yoffset;
		int xadvance;
	};

	//! Constructor
	/*!
		Makes a new Bitmap font and loads everything from a FNT file.
	*/
	BitmapFont( RenderSystem& _r, std::string _fnt = "");

    //! Advanced Constructor
    /*!
        Makes a new (empty) Bitmap Font.
		You must manually load in pages, etc.
        \param _rm A resource manager to keep track of this object.
        \param _br A batch renderer for this font to draw to.
        \note Sets the resource type to ERT_BITMAP_FONT
    */
    BitmapFont( ResourceManager& _r, BatchRenderer& _b )
        : Font( _r, _b, 3), characters(256), spacing( 10.0f )
    {
        setName("Unnamed font");
		std::fill( characters.begin(), characters.end(), BitmapFont::Character() );
    }

    virtual ~BitmapFont()
    {}

	//! Loads a BMFont text format .fnt file.
	/*
		Requires a rendersystem to load textures
	*/
	virtual void load( RenderSystem& _r, std::string _fnt = "" );

	//! Draws the given string at the given location.
	virtual BatchGeometryPtr drawText( const std::string& s, const Vector2d& p = Vector2d(0,0) );

    //! Gets the spacing between words.
    inline float getSpacing() const { return spacing; }

    //! Set spacing, default is 10.0f.
	inline void setSpacing( float s = 10.0f) { spacing = s; }

	//! Sets the character properties (Loader Interface).
	inline void setCharacterProperties( int _ix, const BitmapFont::Character& _c ){ characters[_ix] = _c; }

	//! Sets a kerning pair (Loader Interface).
	inline void setKerning( int _f, int _s, int _v ) { kernings[ KerningKey(_f,_s) ] = _v; }

	//! Fetches the kerning value for a pair
	inline int getKerning( int _f, int _s ) { return kernings[ KerningKey(_f,_s) ]; }

protected:

	//! Character List
	std::vector< BitmapFont::Character > characters; 

	//! Kerning pairs
	typedef std::pair<int,int> KerningKey;
	typedef boost::unordered_map< KerningKey, int > KerningMap;
	KerningMap kernings;

    //! Spacing between characters when drawn.
    float spacing;

};

//! Friendly BitmapFont pointer
typedef boost::intrusive_ptr<BitmapFont> BitmapFontPtr;

} //namespace phoenix
#endif // __PHBITMAPFONT_H__
