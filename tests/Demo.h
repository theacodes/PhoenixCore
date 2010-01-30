/*

Copyright (c) 2009, Jonathan Wayne Parrott

Please see the license.txt file included with this source
distribution for more information.

*/


#include "Phoenix.h"

using namespace phoenix;
using namespace boost;
using namespace std;

/*!~~~~~~~~~~~~~~~~~~~~
First, We'll need some sort of particle class,
and Resource is a good way to do it.
~~~~~~~~~~~~~~~~~~~~~~*/

class DemoParticle:
        public Resource
{
public:

    static bool blendmode;
    float radius, speed, life;
    Vector2d position, direction;
    Color color;
    float rot;
    BatchGeometryPtr geometry;
    RenderSystem& rsystem;

public:

    ~DemoParticle()
    {
    }

    DemoParticle( RenderSystem& s, TexturePtr t, Vector2d p )
            : Resource( s.getResourceManager() , 10), radius(1.f), position(p), speed(0.f), color(), rot(0), life(1), geometry(), rsystem(s)
    {
        direction = (p - Vector2d(320,240)).getDirection() * RotationMatrix(DegreesToRadians(random(-40,40)));
        speed = random(100,5000)/1000.0f;
        color = Color( random( 127, 255 ), random( 127, 255 ), random( 127, 255 ) );
        life = random(10000,100000);
        radius = random(750,1250)/1000.0f;
        rot = random(0,360);

        // Make some geometry.
        geometry = new BatchGeometry( s, GL_QUADS, t, 5, (EventReceiver::getKey( PHK_S ) ? random(1,150) : 0) );
        geometry->setGroupBeginFunction( boost::bind( &DemoParticle::startBlend, intrusive_ptr<DemoParticle>(this) ) );
        geometry->setGroupEndFunction( boost::bind( &DemoParticle::endBlend, intrusive_ptr<DemoParticle>(this) ) );
    }

    //! Start blend function
    virtual void startBlend()
    {
        // Set our blend mode.
        if ( blendmode )
            rsystem.setBlendMode( GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
        else
            rsystem.setBlendMode( GL_SRC_ALPHA, GL_ONE );
    }

    //! End blend function
    virtual void endBlend()
    {
        // restore the blend mode
        rsystem.setBlendMode();
    }

    virtual void drop()
    {
        if ( ! dropped() )
        {
            geometry->drop();
            Resource::drop();
        }
    }

    void draw( float dtime )
    {

        //! Velocity basted on position from the center.
        Vector2d velocity = direction * speed * (radius / 1.2f);
        position += velocity *(dtime*50);

        // Movement with Keys
        if ( EventReceiver::getKey( PHK_RIGHT ) ) position += (Vector2d( -1.0f, 0.0f ) * (radius*5.0f / 1.2f)) * dtime * 1000.0f;
        if ( EventReceiver::getKey( PHK_LEFT ) ) position += (Vector2d( 1.0f, 0.0f ) * (radius*5.0f / 1.2f)) * dtime* 1000.0f;
        if ( EventReceiver::getKey( PHK_UP ) ) position += (Vector2d( 0.0f, 1.0f ) * (radius*5.0f / 1.2f)) * dtime * 1000.0f;
        if ( EventReceiver::getKey( PHK_DOWN ) ) position += (Vector2d( 0.0f, -1.0f ) * (radius*5.0f / 1.2f)) * dtime * 1000.0f;

        // Update our geometry
        geometry->fromRectangle( phoenix::Rectangle( -16, -16, 32, 32 ) );
        geometry->colorize( color );
        geometry->scale( Vector2d( radius, radius ) );
        geometry->rotate( DegreesToRadians(rot) );
        geometry->translate( position );

        // lose some life, rotate a little, and scale down.
        color.setAlpha( (life*255) /100000 );
        life -= int(dtime*100);
        rot -= dtime*500.0f;
        radius -= 0.05 * (dtime*15.0f) ;

        // drop if too small/dead.
        if ( radius < 0.05 ) drop();
        if ( life <= 0 ) drop();
        if ( color.getAlpha() == 0 ) drop();

    }

};

bool DemoParticle::blendmode = true;

/*!~~~~~~~~~~~~~~~~~~~~~~
Main demo class.
~~~~~~~~~~~~~~~~~~~~~~*/

class Demo
{
public:

    Demo() : system(), timer()
    {
        // Enable resizing
        system.enableResize();

        //start timer
        timer.start();
    }

    virtual ~Demo()
    {
    }

    //! Draw some particles
    void drawParticles( )
    {

        // If 'P' was pressed, pause the system by stopping the timer.
        if( EventReceiver::getKey( PHK_P ) ) timer.stop();

        //! Iterate through the particles

        //lock resource mutex.
        system.getResourceManager().lock();

        // delta time
        float deltatime = timer.getTime();

        BOOST_FOREACH( ResourcePtr& r, system.getResourceManager().getList() )
        {
            if ( ! r->dropped() )
            {
                if ( r->getType() == 10 )
                {
                    r->grab<DemoParticle>()->draw( deltatime );
                }
            }
        }

        timer.reset();

        system.getResourceManager().unlock();

    }

    /*!
        This actually runs the demo.
    */
    int run()
    {

        // Textures for particles.
        glowtexture = system.loadTexture("feather.png");
        glowtexture2 = system.loadTexture("glow.png");

        // List of bright colors for subtractive blending
        vector<Color> brightcolors;
        brightcolors.push_back( Color(255,255,255) );
        brightcolors.push_back( Color(127,255,255) );
        brightcolors.push_back( Color(255,255,127) );
        brightcolors.push_back( Color(255,127,255) );
        brightcolors.push_back( Color(127,127,255) );
        brightcolors.push_back( Color(127,255,127) );
        brightcolors.push_back( Color(255,127,127) );

        // List of dark colors for additive blending
        vector<Color> darkcolors;
        darkcolors.push_back( Color(0,0,0) );
        darkcolors.push_back( Color(127,0,0) );
        darkcolors.push_back( Color(0,0,127) );
        darkcolors.push_back( Color(0,127,0) );
        darkcolors.push_back( Color(127,127,0) );
        darkcolors.push_back( Color(127,0,127) );
        darkcolors.push_back( Color(0,127,127) );

        // current color list
        vector<Color>* currentcolors = &brightcolors;

        // Our current and destination color index.
        unsigned int currentcolor = 0;
        unsigned int destcolor = random( 0, (*currentcolors).size()-1 );

        // Our current color percentage ( for inerpolation ).
        float colorpercent = 0.0f;

        // A timer for color changing.
        Timer colortimer;
        colortimer.start();

        // A tracking invariant for keeping up with the mouse position
        TrackingInvariant< Vector2d > mouseposition = EventReceiver::getMousePosition();

        //! Now just draw some stuff.
        while ( system.run() )
        {

            //! Colors.

            // clear the screen to our color interpolated with our destination color.
            system.clearScreen( (*currentcolors)[ currentcolor ].interpolate( (*currentcolors)[ destcolor ], colorpercent ) );

            // add to our interpolation percentage.
            colorpercent += colortimer.getTime() * 5.0f;

            // If we're all the way at the destination color,
            // make our current color the destination color
            // and pick a new color.
            if ( colorpercent > 100.0f )
            {
                colorpercent = 0.0f;
                currentcolor = destcolor;
                destcolor = random( 0, (*currentcolors).size()-1 );
            }

            //! Particles

            // Change particle's blendmode and colors if 'B' was pressed
            if ( EventReceiver::getKeyPressed( PHK_B ) )
            {
                DemoParticle::blendmode = !DemoParticle::blendmode; //swap it.

                // now pick a new color.
                if ( currentcolors == &brightcolors ) currentcolors = &darkcolors;
                else if ( currentcolors == &darkcolors ) currentcolors = &brightcolors;
                currentcolor = random( 0, (*currentcolors).size()-1 );
                destcolor = random( 0, (*currentcolors).size()-1 );

            }

            //! Particle creation functions.

            //update our mouse tracker
            mouseposition.reset();
            mouseposition = EventReceiver::getMousePosition();
            Vector2d dmouseposition = mouseposition.getPrevious() - mouseposition.get();
            system.getDebugConsole()<<"\nMouse Delta: "<<dmouseposition.getX()<<", "<<dmouseposition.getY();

            // we wanna generate 1 per 0.05ms, or 5000 per second.
            float ts = colortimer.getTime()/0.0005f;
            system.getDebugConsole()<<"\nParticles to Generate: "<<ceil(ts);

            //reset the timer.
            colortimer.reset();

            if ( EventReceiver::getMouseButton( PHK_MB_LEFT ))
            {
                for ( int i = 0; i < (int)ceil(ts) ; ++i)
                {
                    new DemoParticle( system ,glowtexture2, mouseposition.get() + dmouseposition*( float(i)/ts ) );
                }
            }


            if ( EventReceiver::getKey( PHK_SPACE ) )
            {
                for ( int i = 0; i< (int)ceil(ts); ++i)
                {
                    new DemoParticle( system, TexturePtr(), mouseposition.get() + dmouseposition*(  float(i)/ts  ) );
                }
            }

            if ( EventReceiver::getMouseButton( PHK_MB_RIGHT ) )
            {
                for ( int i = 0; i< (int)ceil(ts); ++i)
                {
                    new DemoParticle( system, glowtexture, mouseposition.get() + dmouseposition*(  float(i)/ts  ) );
                }
            }

            //! Draw them all
            drawParticles();

            //!s draw some info.
            system.drawText( "Use left & right mouse buttons to spawn particles.", Vector2d( 0,0 ), Color(255,127,127) );
            system.drawText( "Use arrow keys to move the field around.", Vector2d( 0,16 ), Color(255,147,147) );
            system.drawText( "Use 'B' to change blending modes, use 'P' to pause.", Vector2d( 0,32 ), Color(255,157,157) );
            system.drawText( "Press '~' for information.", Vector2d( 0, WindowManager::getScreenSize().getY()-16.0f ), Color(127,127,255,127) );


            // print some stats
            system.getDebugConsole()<<"\nSprites: "<<system.getResourceManager().count()
                <<"\nGeometry: "<<system.count()
                <<"\nFrames Per Seconds: "<<system.getFPS()
                <<"\nScreen Size: "<<WindowManager::getScreenSize().getX()<<", "<<WindowManager::getScreenSize().getY()
                <<"\nBlend Mode: "<< (DemoParticle::blendmode ? "Smoke" : "Additive")
                ;

        }

        return 0;

    }// Run

protected:

    Timer timer;
    TexturePtr glowtexture;
    TexturePtr glowtexture2;
    RenderSystem system;
private:
};
