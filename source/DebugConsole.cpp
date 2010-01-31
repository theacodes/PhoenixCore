#include "DebugConsole.h"

using namespace phoenix;

void DebugConsole::write( std::string _s )
{
    //stream and temporary storage.
    std::istringstream stream( _s );        
    char temp[256];

    // The first line in the string, even if it's empty, will be added to the current line.
    if( ! lines.empty() )
    {
        stream.getline( temp, 256 );
        lines.back() += std::string( temp );
    }

    // The remaining lines in the string will be addeded as completely new lines.
    for( int i = 0; !stream.eof(); ++i )
    {
        stream.getline( temp, 256 );
        lines.push_back( std::string( temp ) );
    }

    // Limit the number of lines.
    limitLines();
}


//draw function
void DebugConsole::draw( )
{

    if( EventReceiver::getKeyPressed( PHK_BACKTICK ) ) enabled = !enabled;

    if( enabled )
    {

        // Draw our overlay rectangle at depth- 0.01;
        BatchGeometryPtr geom = drawRectangle( Rectangle( Vector2d(0,0), WindowManager::getScreenSize() ), backcolor, backcolor, backcolor, backcolor);
        setDepth( getDepth() - 0.01f );
        apply( geom );
        setDepth( getDepth() + 0.01f );

        font->setColor( fontcolor );
        geom = font->drawText( "== PhoenixCore 0.1 Debug Console ==", Vector2d( 8,8 ) );
        apply( geom, EFF_ALL - EFF_TEXTURE );

        unsigned int count = 1;
        for( std::deque< std::string >::iterator i = lines.begin(); i != lines.end(); ++i, ++count )
        {
            geom = font->drawText( (*i), Vector2d( 8.0f, 8.0f+(16.0f* (float)(count) ) ) );
            apply( geom, EFF_ALL - EFF_TEXTURE );
        }
    }
}

void DebugConsole::groupEnd()
{
    renderer.getView().activate();
}