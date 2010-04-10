#ifndef __PH_DEBUG_CONSOLE_H__
#define __PH_DEBUG_CONSOLE_H__

#include <string>
#include "config.h"
#include "2dGraphicsFactory.h"
#include "WindowManager.h"
#include "Font.h"
#include "Color.h"
#include "View.h"

namespace phoenix
{

class RenderSystem;

//! Debug Console
/*!
    The debug console provides an easy and familiar way to debug graphical applications in phoenix. Any
	class that can be written to an ostream can be used in the write() function. This class is a Singleton
	and must be accessed through Instance().
*/
class DebugConsole
    : public virtual GraphicsFactory2d
{
public:

	//! Bad Instance Exception
	struct BadInstance{};

	//! Initialization Function.
	/*!
		Creates the singleton instance. This is separate from Instance() because
		this class requires parameters in order to be created. It also requires
		that a valid WindowManager has be initialized.
	*/
	inline static boost::shared_ptr<DebugConsole> Initialize(  BatchRenderer& _r, FontPtr _f ){
		instance = boost::shared_ptr<DebugConsole>( new DebugConsole(_r,_f) );
		return instance;
	}

	//! Instance.
	/*!
		Gets the singleton instance of this class. It must be initialized with Initialize()
		first, otherwise it will throw a BadInstance.
	*/
	inline static boost::shared_ptr<DebugConsole> Instance(){
		if( instance ){
			return instance;
		}else{
			throw BadInstance();
		}
	}

    //! Destructor
    virtual ~DebugConsole() {
		event_connection.disconnect();
	}

	//! Listens for Window Events ( To Open/Close the console ).
	void onWindowEvent( const WindowEvent& e );

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
    void dump()
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
        Runs through all the lines and draws them. Automatically called on the
		WET_UPDATE event.
    */
    void draw( );
    

    //! Group begin function.
    /*!
        Clears the view state so that user transformations do not effect the console.
    */
    inline static void groupBegin()
    {
        View view;
        view.activate();
    }

    //! Group end funciton.
    /*!
        Restores the render system's transformations.
    */
    void groupEnd();

protected:

	//! Constructor
    /*!
        Makes a new debug console. Requires a reference to a RenderSystem.
    */
    DebugConsole( BatchRenderer& _r, FontPtr _f )
        : GraphicsFactory2d( _r ), font(_f), enabled( false ), lines(), linelimit(0), backcolor(0,0,0,200), fontcolor(127,127,255)
    {
		event_connection = WindowManager::Instance()->listen( boost::bind( &DebugConsole::onWindowEvent, this, _1 ) );
        setDepth( 999.0f );
        setGroup( -10 );
        setGroupBeginFunction( boost::function< void() >( &DebugConsole::groupBegin ) );
        setGroupEndFunction( boost::bind( &DebugConsole::groupEnd, this ) );
        updateLineLimit();
    }

	//! Static Instance
	static boost::shared_ptr<DebugConsole> instance;

	//! Connection to Window Manager
	boost::signals2::connection event_connection;

	//! Font
    FontPtr font;

	//! Enabled or not.
    bool enabled;

	//! List of lines.
    std::deque< std::string > lines;

	//! The most lines that can be displayed on the screen.
    unsigned int linelimit;

	//! Background Color.
    Color backcolor;

	//! Foreground Color.
    Color fontcolor;
};

typedef boost::shared_ptr<DebugConsole> DebugConsolePtr;

} //namespace phoenix;

#include "RenderSystem.h"

#endif // __PH_DEBUG_CONSOLE_H__