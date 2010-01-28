/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHBITMAPFONT_H__
#define __PHBITMAPFONT_H__

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

    //Befriend phresource
    friend class Resource;

public:

    //! Constructor
    /*!
        Makes a new Bitmap Font.
        \param _rm A resource manager to keep track of this object.
        \param _br A batch renderer for this font to draw to.
        \param _t The texture containing the glyphs.
        \note Sets the resource type to ERT_BITMAP_FONT
    */
    BitmapFont( ResourceManager& _r, BatchRenderer& _b, TexturePtr _t = TexturePtr() )
        : Font( _r, 3), renderer( _b ), spacing( 10.0f )
    {
        setTexture( _t );
        setName(_t->getName() + " font");
    }

    virtual ~BitmapFont()
    {}

	virtual boost::shared_ptr<BatchGeometry> drawText( const std::string& s, const Vector2d& p = Vector2d(0,0) );

    //! Gets the spacing between words, default is 10.0f.
    inline float getSpacing() const { return spacing; }

    //! Set spacing.
    inline void setSpacing( float s ) { spacing = s; }


protected:

    //! Render system
    BatchRenderer& renderer;

    //! Spacing
    float spacing;

};

//! Friendly BitmapFont pointer
typedef boost::intrusive_ptr<BitmapFont> BitmapFontPtr;

} //namespace phoenix
#endif // __PHBITMAPFONT_H__
