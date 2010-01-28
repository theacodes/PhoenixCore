/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#ifndef __PHFONT_H__
#define __PHFONT_H__

#include "Resource.h"
#include "AbstractGeometryFactory.h"
#include "string.h"
#include "Color.h"

namespace phoenix
{

//! Font class.
/*!
    Abstract base class for font handling. Tou can overload this class to provide
    custom font drawing interfaces for phoenix.
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
    Font(ResourceManager& _r, int _t = 2)
        : Resource( _r, _t ), color(), scale( Vector2d( 1, 1 ) )
    {}

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

protected:

	//! Color
	Color color;

	//! Scale.
    Vector2d scale;

};

//! Friendly Font pointer
typedef boost::intrusive_ptr<Font> FontPtr;

}//namespace phoenix
#endif // __PHFONT_H__
