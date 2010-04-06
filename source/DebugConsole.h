#ifndef __PH_DEBUG_CONSOLE_H__
#define __PH_DEBUG_CONSOLE_H__

#include <string>
#include "config.h"
#include "2dGraphicsFactory.h"
#include "Font.h"
#include "Color.h"
#include "View.h"

namespace phoenix
{

class RenderSystem;

//! Debug Console
/*!
    The debug console provides an easy and familiar way to debug graphical applications in phoenix. The RenderSystem has one of these
    by default, accessible from RenderSystem::getDebugConsole().
*/
class DebugConsole
    : public virtual GraphicsFactory2d
{
public:

    //! Constructor
    /*!
        Makes a new debug console. Requires a reference to a RenderSystem.
    */
    DebugConsole( BatchRenderer& _r, FontPtr _f )
        : GraphicsFactory2d( _r ), font(_f), enabled( false ), lines(), linelimit(0), backcolor(0,0,0,200), fontcolor(127,127,255)
    {
        setDepth( 999.0f );
        setGroup( -10 );
        setGroupBeginFunction( boost::function< void() >( &DebugConsole::groupBegin ) );
        setGroupEndFunction( boost::bind( &DebugConsole::groupEnd, this ) );
        updateLineLimit();
    }

    //! Does nothing.
    virtual ~DebugConsole() {}

    //! Get the font.
    FontPtr getFont() { return font; }

    //! Set the font.
    void setFont( FontPtr _f ) { font = _f; }

    //! Set the background color.
    void setBackgroundColor( const Color& _c = Color(0,0,0,200) ) { backcolor = _c; }

    //! Get the background color.
    const Color& getBackgroundColor() { return backcolor; }

    //! Set the color used to draw text.
    void setFontColor( const Color& _c = Color(127,127,255) ) { fontcolor = _c; }

    //! Get the text color.
    const Color& getFontColor() { return fontcolor; }

    //! Write a string to the console.
    /*!
        Newline characters '\n' are automatically split.
    */
    virtual void write( std::string _s );

    //! Templated write function.
    /*!
        Used by the stream operator to convert types into
        strings. Supports any type that stringstreams do.
    */
    template < typename T >
    void write( T _v )
    {
        std::ostringstream stream;
        stream << _v;
        write( stream.str() );
    }

    //! Clear the debug console.
    void clear()
    {
        lines.clear();
    }

    //! Prints the console's content to cout.
    void print()
    {
        for( std::deque< std::string >::iterator i = lines.begin(); i != lines.end(); ++i )
        {
            std::cout<<(*i)<<std::endl;
        }
    }

    //! Update the line limit based on the size of the window.
    void updateLineLimit()
    {
		try{
			linelimit = (unsigned int)(((WindowManager::Instance())->getWindowSize().getY())/16.0f) - 2;
		} catch ( WindowManager::BadInstance ){
			linelimit = 10;
		}
    }

    //! Removes old lines that are beyond the limit of displayable lines.
    void limitLines()
    {
        unsigned int size = lines.size();
        if( size > linelimit )
            lines.erase( lines.begin(), lines.begin()+( size-linelimit ) );
    }

    //! Stream operator.
    /*!
        Uses the templated write() function to stream types into the console.
    */
    template < typename T >
    DebugConsole& operator << ( T _s )
    {
        write<T>( _s );
        return *this;
    }

    //! Draw the console.
    /*!
        The RenderSystem automatically calls this during RenderSystem::run(). It runs through all
        the lines and draws them.
    */
    void draw( );
    

    //! Group begin function.
    /*!
        Clears the view state so that user transformations do not effect the console.
    */
    inline static void groupBegin()
    {
        View view;
		view.setSize();
        view.activate();
    }

    //! Group end funciton.
    /*!
        Restores the render system's transformations.
    */
    void groupEnd();

protected:

    FontPtr font;
    bool enabled;
    std::deque< std::string > lines;
    unsigned int linelimit;
    Color backcolor;
    Color fontcolor;
};

} //namespace phoenix;

#include "RenderSystem.h"

#endif // __PH_DEBUG_CONSOLE_H__