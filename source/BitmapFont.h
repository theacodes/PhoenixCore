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

    //! Create Factory
    /*!
        Makes a new Bitmap Font.
        \param _rm A resource manager to keep track of this object.
        \param _br A batch renderer for this font to draw to.
        \param _t The texture containing the glyphs.
    */
    static boost::shared_ptr< BitmapFont > create( ResourceManager& _rm, BatchRenderer& _br,boost::shared_ptr<Texture> _t )
    {
        boost::shared_ptr< BitmapFont > newfont( new BitmapFont( _rm, _br ) );
        _rm.addResource( newfont->grab<Resource>() );
        newfont->setTexture(_t);
        newfont->_name = _t->getName() + " font";
        newfont->scale = Vector2d(1.0f,1.0f);
        newfont->color = Color(255,255,255);
        newfont->spacing = 10.0f;
        return newfont;
    }

    virtual ~BitmapFont()
    {}

	virtual boost::shared_ptr<BatchGeometry> drawText( const std::string& s, const Vector2d& p = Vector2d(0,0) );

    //! Gets the spacing between words, default is 10.0f.
    inline float getSpacing() const { return spacing; }

    //! Set spacing.
    inline void setSpacing( float s ) { spacing = s; }


protected:

    //! Private Constructor
    /*!
        Sets the resource type to ERT_BITMAP_FONT
    */
    BitmapFont( ResourceManager& _r, BatchRenderer& _b )
        : Font( _r, 3), renderer( _b )
    {}

    //! Render system
    BatchRenderer& renderer;

    //! Spacing
    float spacing;

};

} //namespace phoenix
#endif // __PHBITMAPFONT_H__
