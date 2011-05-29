/*

Copyright (c) 2010, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHFONT_H__
#define __PHFONT_H__

#include "config.h"
#include "Resource.h"
#include "AbstractGeometryFactory.h"
#include "BatchRenderer.h"
#include <string>
#include "Color.h"

namespace phoenix
{

class RenderSystem;

//! Font class.
/*!
    Abstract base class for font handling. It is possible (and suggested)
	to overload this class and provide your own custom interfaces for phoenix
	to draw text.
    The default font interface in phoenix is provided by BitmapFont.
*/
class Font :
    public Resource, public AbstractGeometryFactory
{

public:
    
    //! Constructor
    /*!
        \param _r ResourceManager pointer.
        \param _t Type, defaults to 2 ( ERT_FONT ) for abstract font.
    */
    Font(ResourceManager& _r, BatchRenderer& _b, int _t = 2)
        : Resource( _r, _t ), renderer(&_b), color(), scale( Vector2d( 1, 1 ) )
    {}


	//! RenderSystem based construction.
	Font(RenderSystem& _r, int _t = 2);

    //! Destructor
    virtual ~Font()
    {}

    //! Draw text.
    /*!
        The basic interface for drawing text. Must be overloaded by derived classes to provide their
        facility of drawing text. It is a geometry factory.
        \param _s The string to print to the screen.
        \param _p The position to draw it at.
    */
    virtual BatchGeometryPtr drawText( const std::string& _s, const Vector2d& _p = Vector2d(0,0) ) = 0;

	//! Gets the current color of the font.
	inline virtual const Color& getColor() { return color; }

    //! Set color.
	inline virtual void setColor( const Color& _c ) { color = _c; }

	//! Gets the scaling factor of the font.
    inline const Vector2d& getScale() const { return scale; }

    //! Set scale.
    inline void setScale( const Vector2d& _s = Vector2d(1,1)) { scale = _s; }

	//! Gets the current target batch renderer
	inline virtual BatchRenderer* getBatchRenderer() { return renderer; }

    //! Set the target batch renderer.
	inline virtual void setBatchRenderer( BatchRenderer* _r ) { renderer = _r; }

protected:

	//! Batcher.
    BatchRenderer* renderer;

	//! Color
	Color color;

	//! Scale.
    Vector2d scale;

};

//! Friendly Font pointer
typedef boost::intrusive_ptr<Font> FontPtr;

}//namespace phoenix

#include "RenderSystem.h"

#endif // __PHFONT_H__
