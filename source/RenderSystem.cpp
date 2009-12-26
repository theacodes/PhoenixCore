/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/

#include "RenderSystem.h"
#include "PrecompiledFont.h"
#include "BitmapFont.h"
#include <iostream>
#include <GL/glfw.h>
#include "soil/SOIL.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct & Destruct
////////////////////////////////////////////////////////////////////////////////

RenderSystem::RenderSystem( const Vector2d& _sz , bool _fs  )
: BatchRenderer(), AbstractGeometryFactory(), console( *this ), fpstimer(), framerate(0.0f), font(), resources(), exitTest( &RenderSystem::defaultExitTestFunction )
{

	// Create our window
	WindowManager::open( _sz, _fs );

    // viewport the same as the window size.
    //glViewport(0,0,int(_sz.getX()), int(_sz.getY())); 
    getView().setSize();

    // Orthogonal projection.
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glOrtho(0.0f, _sz.getX(), _sz.getY(), 0.0f, 1000.0f, -1000.0f);

    // load up identity for the modelview matrix.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up depth buffer
    #ifdef DISABLE_DEPTHBUFFER
        // No need for depth buffer.
        glDisable(GL_DEPTH_TEST);
    #else
        // Enable depth testing and set the function
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    #endif

    // Smoooth shading, Nicest Hinting.
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Enable blending and set our blending mode.
    glEnable(GL_BLEND);
    setBlendMode(); // Default is for 2d transluceny with RGBA textures.

    //! Default material is white.
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Clear the screen to black 
    clearScreen( Color(0,0,0) );

    // Material mode
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);

    //load our default font
	std::string ffn = saveBuiltinFont();
	font = BitmapFont::create( resources, *this ,loadTexture(ffn));
    remove(ffn.c_str());

    //!start the timer
    fpstimer.start();

	//store the new framerate
    framerate = 1.0f;

    //set the debug console's line limit
    console.updateLineLimit();

}


RenderSystem::~RenderSystem()
{
	WindowManager::close();
}

////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////

void RenderSystem::resizeCallback( Vector2d _sz )
{
    WindowManager::setScreenSize( _sz );
    getView().setSize( _sz );
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glOrtho(0.0f, _sz.getX(), _sz.getY(), 0.0f, 1000.0f, -1000.0f);
    console.updateLineLimit();
}

////////////////////////////////////////////////////////////////////////////////
//run function, should be called once every loop, it makes things ready for
//a render.
////////////////////////////////////////////////////////////////////////////////

bool RenderSystem::run()
{

    //Call our own draw function
    draw();

    //flip the screen (this also polls events).
	WindowManager::swapBuffers();

    //clear screen
    clearScreen();

    //store the new framerate
    framerate = 1.0f/ fpstimer.getTime();

    //Start our fps timer
    fpstimer.stop();
    fpstimer.start();

    //draw the debug console.
    console.draw();

    if( exitTest )
    {
        return exitTest();
    }
    return false; //No exit test means that the system can never exit, so we'll force it to

}


////////////////////////////////////////////////////////////////////////////////
//Load texture function
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<Texture> RenderSystem::loadTexture( const std::string& _fn, bool _l )
{

	//This is the class that will hold our texture
	boost::shared_ptr<Texture> ctext = Texture::create( resources );

	int width=0,height=0;

	GLuint newtextid = SOIL_load_OGL_texture
        (
                _fn.c_str(),
                SOIL_LOAD_RGBA,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_TEXTURE_REPEATS,
                &width, &height
        );

	if( newtextid != 0 )
	{

        //Load the texture
        glBindTexture(GL_TEXTURE_2D, newtextid);

        //use linear filtering
        if ( _l == true)
        {

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        }
        else
        {

            //Use nearest filter
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        }

        //Set up the Texture class
        ctext->setTextureId(newtextid);
        ctext->setWidth(width);
        ctext->setHeight(height);
        ctext->setName( _fn );

        //Return our texture
        return ctext;

    }
    else
    {

        boost::shared_ptr<Texture> ctext = Texture::create( resources );
        ctext->setTextureId(0);
        ctext->setWidth(0);
        ctext->setHeight(0);
        ctext->setName("FAILED TO LOAD");

        //Return our texture
        return ctext;

    }

    //should never happen
    return boost::shared_ptr<Texture>();
    assert(true);

}

////////////////////////////////////////////////////////////////////////////////
// Find texture functions.
////////////////////////////////////////////////////////////////////////////////

//! Find texture.
boost::shared_ptr<phoenix::Texture> RenderSystem::findTexture(const std::string& _i)
{
    boost::shared_ptr<phoenix::Resource> findtexture = resources.findResource(_i);
    if( findtexture )
    {
        return findtexture->grab<phoenix::Texture>();
    }
    else
    {
        return boost::shared_ptr<phoenix::Texture>();
    }

}

//! Find texture.
boost::shared_ptr<phoenix::Texture> RenderSystem::findTexture(const GLuint& _n)
{
	boost::recursive_mutex::scoped_lock( resources.getMutex() );
    for (unsigned int i=0;i<resources.getResourceCount();i++)
    {
        if( resources.getResource(i)->getType() == ERT_TEXTURE )
        {
            if ( resources.getResource(i)->grab<phoenix::Texture>()->getTextureId() == _n )
            {
                return resources.getResource(i)->grab<phoenix::Texture>();
            }
        }
    }
    return boost::shared_ptr<phoenix::Texture>();
}

////////////////////////////////////////////////////////////////////////////////
//Draws a line
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<BatchGeometry> RenderSystem::drawLine(const Vector2d& _v1, const Vector2d& _v2, const Color& _a, const Color& _b)
{
    // Just make some new geometry, set it to immediate, and add the line's vertices.
    boost::shared_ptr<BatchGeometry> linegeom = BatchGeometry::create( *this, GL_LINES, getTexture(), getGroup(), getDepth() );
	linegeom->setImmediate( true );
	linegeom->addVertex( Vertex( _v1, _a, TextureCoords(0,0) ) );
	linegeom->addVertex( Vertex( _v2, _b, TextureCoords(1,1) ) );

    return linegeom;

}

////////////////////////////////////////////////////////////////////////////////
//Draws a rectangle
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<BatchGeometry> RenderSystem::drawRectangle( const Rectangle& _r, const Color& _a, const Color& _b, const Color& _c, const Color& _d )
{
    // Use BatchGeometry's factory for it.
	boost::shared_ptr<BatchGeometry> rectgeom = BatchGeometry::create( *this, _r, getTexture(), getGroup(), getDepth() );
	rectgeom->setImmediate( true );

    // now just set the colors.
	(*rectgeom)[0].color = _a;
	(*rectgeom)[1].color = _b;
	(*rectgeom)[2].color = _c;
	(*rectgeom)[3].color = _d;

    return rectgeom;
}

////////////////////////////////////////////////////////////////////////////////
//Draws a polygon
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<BatchGeometry> RenderSystem::drawPolygon (const Polygon& _p, const Color& _c)
{
    // just use the BatchGeometry's factory
	boost::shared_ptr<BatchGeometry> polygeom = BatchGeometry::create( *this, _p, getTexture(), getGroup(), getDepth());
	polygeom->setImmediate( true );
	polygeom->colorize( _c );
    return polygeom;
}

////////////////////////////////////////////////////////////////////////////////
//Draws a polygon
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<BatchGeometry> RenderSystem::drawTexturedPolygon (const Polygon& _p, boost::shared_ptr<Texture> _t, const Color& _c, bool _e)
{

    // Use the regular draw poly function to save us effort.
    setTexture( _t );
    boost::shared_ptr<BatchGeometry> polygeom = drawPolygon( _p, _c );
    setTexture();

    // planes for coordinate generation
    Vector2d splane( 1.0f/_t->getWidth(), 0);
    Vector2d tplane( 0, 1.0f/_t->getHeight() );

    // Go through each vertex on the geometry and generate the Tcoords.
    for( unsigned int i = 0; i < polygeom->getVertexCount(); ++i )
    {
        // We'll need the current vertex's position to calculate the tcoords.
        Vector2d v = (*polygeom)[i].position;
        // if we're generating object space coordinates, subtract the polygon's position from it.
        if( ! _e )
            v -= _p.getPosition();

        // Now it's as simple as the inner product of the planes and the vector.
        (*polygeom)[i].tcoords = TextureCoords( splane * v, tplane * v );
    }

    return polygeom;

}


////////////////////////////////////////////////////////////////////////////////
//Renders a Texture
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<BatchGeometry> RenderSystem::drawTexture(  boost::shared_ptr<Texture> _t, const Vector2d& _p,  const RotationMatrix& _rot, const Vector2d& _scale, const Color& _color, unsigned int _flags )
{
    // Use BatchGeometry's factory for rectangles.
	boost::shared_ptr<BatchGeometry> geom = BatchGeometry::create( *this, Rectangle( -_t->getSize()/2.0f, _t->getSize()) , _t, getGroup(), getDepth() );
    geom->setImmediate( true );

    // scale, rotate it, and then translate it.
    geom->scale( _scale );
    geom->rotate( _rot );
    geom->translate( _p + _t->getSize()/2.0f );

    // colorize
    geom->colorize( _color );

    // Flip tcoords
    if( _flags & EGF_HFLIP )
    {
        (*geom)[0].tcoords.u = ( - (*geom)[0].tcoords.u ) + 1.0f; 
        (*geom)[1].tcoords.u = ( - (*geom)[1].tcoords.u ) + 1.0f; 
        (*geom)[2].tcoords.u = ( - (*geom)[2].tcoords.u ) + 1.0f; 
        (*geom)[3].tcoords.u = ( - (*geom)[3].tcoords.u ) + 1.0f; 
    }
    if( _flags & EGF_VFLIP )
    {
        (*geom)[0].tcoords.v = ( - (*geom)[0].tcoords.v ) + 1.0f; 
        (*geom)[1].tcoords.v = ( - (*geom)[1].tcoords.v ) + 1.0f; 
        (*geom)[2].tcoords.v = ( - (*geom)[2].tcoords.v ) + 1.0f; 
        (*geom)[3].tcoords.v = ( - (*geom)[3].tcoords.v ) + 1.0f; 
    }

    // return it
    return geom;
}

//this draws a texture with a clipping rectangle
boost::shared_ptr<BatchGeometry> RenderSystem::drawTexturePart( boost::shared_ptr<Texture> _t, const Vector2d& _p, const Rectangle& _rect, const RotationMatrix& _rot, const Vector2d& _scale, const Color& _color, unsigned int  _flags )
{
    // Use BatchGeometry's factory for rectangles.
    boost::shared_ptr<BatchGeometry> geom = BatchGeometry::create( *this, Rectangle( -_rect.getDimensions()/2, _rect.getDimensions() ) , _t, getGroup(), getDepth() );
    geom->setImmediate( true );

    // scale, rotate it, and then translate it.
    geom->scale( _scale );
    geom->rotate( _rot );
    geom->translate( _p + _rect.getDimensions()/2.0f );

    // colorize
    geom->colorize( _color );

    // Define tcoords.
    Vector2d originuv( _rect.getX()/_t->getWidth(), _rect.getY()/_t->getHeight() );
    Vector2d spanuv( _rect.getWidth()/_t->getWidth(), _rect.getHeight()/_t->getHeight() );

    (*geom)[3].tcoords = TextureCoords( (originuv+spanuv).getX(), originuv.getY() );
    (*geom)[2].tcoords = TextureCoords( (originuv+spanuv).getX(), (originuv+spanuv).getY() );
    (*geom)[1].tcoords = TextureCoords( originuv.getX(), (originuv+spanuv).getY()  );
    (*geom)[0].tcoords = TextureCoords( originuv.getX(), originuv.getY() );

    // Flip tcoords
    if( _flags & EGF_HFLIP )
    {
        (*geom)[0].tcoords.u = ( - (*geom)[0].tcoords.u ) + 1.0f; 
        (*geom)[1].tcoords.u = ( - (*geom)[1].tcoords.u ) + 1.0f; 
        (*geom)[2].tcoords.u = ( - (*geom)[2].tcoords.u ) + 1.0f; 
        (*geom)[3].tcoords.u = ( - (*geom)[3].tcoords.u ) + 1.0f; 
    }
    if( _flags & EGF_VFLIP )
    {
        (*geom)[0].tcoords.v = ( - (*geom)[0].tcoords.v ) + 1.0f; 
        (*geom)[1].tcoords.v = ( - (*geom)[1].tcoords.v ) + 1.0f; 
        (*geom)[2].tcoords.v = ( - (*geom)[2].tcoords.v ) + 1.0f; 
        (*geom)[3].tcoords.v = ( - (*geom)[3].tcoords.v ) + 1.0f; 
    }

    // return it
    return geom;
}

////////////////////////////////////////////////////////////////////////////////
//Draw text on the screen
////////////////////////////////////////////////////////////////////////////////

boost::shared_ptr<BatchGeometry> RenderSystem::drawText( const std::string& _s, const Vector2d& _p, const Color& _c)
{
	font->setColor( _c );
    font->setDepth( getDepth() );
    font->setGroup( getGroup() );
	return font->drawText( _s, _p );
}

