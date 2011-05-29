/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHBITMAPFONT_H__
#define __PHBITMAPFONT_H__

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
        Makes a new Bitmap Font.
        \param _rm A resource manager to keep track of this object.
        \param _br A batch renderer for this font to draw to.
        \param _t The texture containing the glyphs.
        \note Sets the resource type to ERT_BITMAP_FONT
    */
    BitmapFont( ResourceManager& _r, BatchRenderer& _b, TexturePtr _t = TexturePtr() )
        : Font( _r, 3), renderer( _b ), characters(256), spacing( 10.0f )
    {
        setTexture( _t );
        setName(_t->getName() + " font");
		std::fill( characters.begin(), characters.end(), BitmapFont::Character() );
    }

    virtual ~BitmapFont()
    {}

	//! Draws the given string at the given location.
	virtual BatchGeometryPtr drawText( const std::string& s, const Vector2d& p = Vector2d(0,0) );

    //! Gets the spacing between words.
    inline float getSpacing() const { return spacing; }

    //! Set spacing, default is 10.0f.
    inline void setSpacing( float s = 10.0f) { spacing = s; }


	//! Sets the character properties (Loader Interface).
	inline void setCharacterProperties( int ix, const BitmapFont::Character& c ){ characters[ix] = c; }

protected:

	//! Character List
	std::vector< BitmapFont::Character > characters; 

    //! Batcher.
    BatchRenderer& renderer;

    //! Spacing between characters when drawn.
    float spacing;

};

//! Friendly BitmapFont pointer
typedef boost::intrusive_ptr<BitmapFont> BitmapFontPtr;

} //namespace phoenix
#endif // __PHBITMAPFONT_H__
