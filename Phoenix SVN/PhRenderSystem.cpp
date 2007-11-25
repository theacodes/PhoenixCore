/*

Copyright (c) 2007, Jonathan Wayne Parrott.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "PhRenderSystem.h"
#include <iostream>

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct & Destruct
////////////////////////////////////////////////////////////////////////////////

PhRenderSystem::PhRenderSystem()
{

    screen = NULL; //No screen yet

    events = NULL; //No events yet

    textures = NULL; //No textures yet either

    fpstimer.startTimer(); //Start counting

    frame=0; //No frames rendered yet

    lighting = false;

}

PhRenderSystem::~PhRenderSystem()
{
    delete events; //delete event reciever

    delete textures; //insures all the textures are cleaned up

    SDL_FreeSurface(screen); //delete the screen

    SDL_Quit(); //quit SDL
}

////////////////////////////////////////////////////////////////////////////////
//Sets the caption of the window
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::setWindowCaption(std::string str)
{

    SDL_WM_SetCaption( str.c_str(), NULL );

}

////////////////////////////////////////////////////////////////////////////////
//run function, should be called once every loop, it makes things ready for
//a render.
////////////////////////////////////////////////////////////////////////////////

bool PhRenderSystem::run()
{

    //flip the screen
    SDL_GL_SwapBuffers();

    //clear it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //update the events
    events->updateEvents();

    //fps calculation
    frame++;

    return true;

}

////////////////////////////////////////////////////////////////////////////////
//Gets how fast the system is rendering
////////////////////////////////////////////////////////////////////////////////

float PhRenderSystem::getFPS()
{

    //Calculate the frames per second and create the string
    return (float) frame / ( fpstimer.getTicks() / 1000.f );

}

////////////////////////////////////////////////////////////////////////////////
//Get the number of ticks since this thing was created
////////////////////////////////////////////////////////////////////////////////

int PhRenderSystem::getTicks()
{

    return fpstimer.getTicks();

}

////////////////////////////////////////////////////////////////////////////////
//This initializes the system
////////////////////////////////////////////////////////////////////////////////

bool PhRenderSystem::initSystem( PhVector2d sc )
{

    //somevars up everything else
    screensize = sc;

    //init SDL
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        cerr << "FATAL: Failed to initialize SDL!";
        return false;
    }

    //OpenGL screen settings
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);		//Use at least 5 bits of Red
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);		//Use at least 5 bits of Green
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);		//Use at least 5 bits of Blue
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);		//Use at least 16 bits for the depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	//Enable double buffering

    //set up the render screen
    //first with hwrendering
    screen = SDL_SetVideoMode( int(screensize.getX()), int(screensize.getY()), 16, SDL_OPENGL | SDL_HWSURFACE);

    //if it fails, live with software
    if (screen == NULL)
    {
        cout << "WARNING: Phoenix is unable to draw using Hardware Acceleration, attempting software..." <<endl;
        screen = SDL_SetVideoMode( int(screensize.getX()), int(screensize.getY()), 16, SDL_OPENGL | SDL_SWSURFACE);
    }

    //If there was in error in setting up the render screen
    if ( screen == NULL )
    {
        cerr << "FATAL: Failed to initialize OpenGL!" << endl;
        return false;
    }

    //Configure OpenGL to work with a our screen in orthogonal mode
    glViewport(0,0,int(screensize.getX()), int(screensize.getY()));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, screensize.getX(), screensize.getY(), 0.0f, -1000.0f, 1000.0f); //Ortho
    //gluPerspective(45.0f,(GLfloat)screensize.getX()/(GLfloat)screensize.getY(),0.0f,-150.0f);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    //Clear the screen to black and turn a few OpenGL switches on/off.
    glClearColor(0.0f,0.0f,0.0f,0.5f); //Clear to black
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_CULL_FACE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); // Set The Blending Function For Translucency
    glEnable(GL_BLEND); //enable blending

    //set up the font stuff
    float temp = 16.0/256.0;

    for (int i=0; i<256; i++)
    {
        if (i<17)
        {
            glyphs[i].t.setX(i*temp);
            glyphs[i].t.setY(0);
        }
        if (i>16)
        {
            glyphs[i].t.setX(i*temp);//*(i - (int) ((i/16)*16) )) ;
            glyphs[i].t.setY(temp*(int)(i/16));
        }
    }

    //Set the window caption
    setWindowCaption("Phoenix v0.1");

    //set the events
    events = new PhEventHandler;

    //set the textures
    textures = new PhTextureManager;

    //everything was fine
    return true;

}

////////////////////////////////////////////////////////////////////////////////
//Get screen size
////////////////////////////////////////////////////////////////////////////////

PhVector2d PhRenderSystem::getScreenSize()
{
    return screensize;
}

////////////////////////////////////////////////////////////////////////////////
//Load texture function
////////////////////////////////////////////////////////////////////////////////

PhTexture* PhRenderSystem::loadTexture( std::string filename, bool linear )
{

    //Load the image
    SDL_Surface* loadedImage = IMG_Load( filename.c_str() );

    //This is the class that will hold our texture
    PhTexture* ctext = new PhTexture(textures);

    if (loadedImage)
    {

        //OpenGL Texture ID
        GLuint texture;

        //Genereate 1 texture
        glGenTextures(1,&texture);

        //Load the texture
        glBindTexture(GL_TEXTURE_2D, texture);

        //Generate the texture
        if (filename.find(".png")!=std::string::npos)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedImage->w, loadedImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedImage->pixels);
        }

        if (filename.find(".bmp")!=std::string::npos)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedImage->w, loadedImage->h, 0, GL_BGR, GL_UNSIGNED_BYTE, loadedImage->pixels);
        }

        //use linear filtering
        if (linear == true)
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

        //Set up the PhTexture class
        ctext->setTexture(texture);
        ctext->setWidth(loadedImage->w);
        ctext->setHeight(loadedImage->h);
        ctext->setName(filename);

        //Free the loaded image
        SDL_FreeSurface(loadedImage);


    }
    else
    {

        ctext->setTexture(0);
        ctext->setWidth(0);
        ctext->setHeight(0);
        ctext->setName("FAILEDTOLOAD");

    }

    //Return our texture
    return ctext;

    //add it to the texture list to be cleaned up
    textures->addTexture(ctext);


}

////////////////////////////////////////////////////////////////////////////////
//Draws an indexed trangle list
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawIndexedTriangleList(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, int tricount )
{

    //enable the states first
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY );
    glEnableClientState(GL_NORMAL_ARRAY );

    //now set up the pointers
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
    glNormalPointer(GL_FLOAT, 0, normals);
    glTexCoordPointer(2, GL_FLOAT, 0, tcoords);
    glVertexPointer(3, GL_FLOAT, 0,  vertices);

    //draw the elements
    glDrawElements(GL_TRIANGLES, 3*tricount, GL_UNSIGNED_INT, indexlist);

    //restore our states
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY );
    glDisableClientState(GL_NORMAL_ARRAY );

}


////////////////////////////////////////////////////////////////////////////////
//Draws a rectangle
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawRectangle( PhRect r, float depth, PhColor a, PhColor b, PhColor c, PhColor d )
{
    //load the idenity
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //Move the the top of the screen.
    float x = float(r.getWidth()/2.0f);
    float y = float(r.getHeight()/2.0f);

    glTranslatef(r.getX()+x,r.getY()+y,depth);

    //colors
    GLuint colors[] = {a.toGLColor(), b.toGLColor(), c.toGLColor(), d.toGLColor()};
    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
    //vertices
    GLfloat vertices[] =  {-x,-y,0.0f,
                           x,-y,0.0f,
                           x,y,0.0f,
                           -x,y,0.0f
                          };
    //tcoords, easy
    GLfloat tcoords[] = {0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};
    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );

    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
//Draws a polygon
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawPolygon (PhPolygon P, float depth, PhColor a)
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(P.getPosition().getX(), P.getPosition().getY(), depth);

    a.setActiveColor();
    glBegin(GL_TRIANGLE_FAN);

    glNormal3f(0.0f,0.0f,1.0f);

    for (int i = 0; i < P.getVertexCount(); i ++)
    {
        glVertex3f(P.getVertex(i).getX(), P.getVertex(i).getY(), 0.0f);
    }
    glVertex3f(P.getVertex(0).getX(), P.getVertex(0).getY(), 0.0f);

    glEnd();

    glPopMatrix();

}

////////////////////////////////////////////////////////////////////////////////
//Draws a vector
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawVector(PhVector2d origin,PhVector2d vect)
{
    //load the idenity
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_LINES);
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f(origin.getX(),origin.getY(),0.0f);
    glVertex3f((origin+vect).getX(),(origin+vect).getY(),0.0f);
    glEnd();
    glPopMatrix();
}

void PhRenderSystem::drawVector2(PhVector2d origin,PhVector2d vect)
{
    //load the idenity
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_LINES);
    glNormal3f(0.0f,0.0f,1.0f);
    glVertex3f(origin.getX(),origin.getY(),0.0f);
    glVertex3f((vect).getX(),(vect).getY(),0.0f);
    glEnd();
    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
//Renders a Texture
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawTexture(  PhTexture* source, PhVector2d pos, float depth, float rot, float scale, PhColor color, bool flip)
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //Move the the center of the image
    glTranslatef(pos.getX()+(source->getWidth()/2),pos.getY()+(source->getHeight()/2),depth);

    //flip?
    if (flip)
    {
        glRotatef(180.0f,0.0f,1.0f,0.0f);
    }

    //Rotate
    glRotatef(rot,0.0f,0.0f,1.0f);

    //scale
    glScalef(scale,scale,1.0f);

    glEnable(GL_TEXTURE_2D); //enable textures

    source->bindTexture();

    //colors
    GLuint colors[] = {color.toGLColor(), color.toGLColor(), color.toGLColor(), color.toGLColor()};
    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
    //vertices
    float x = float(source->getWidth()/2.0f);
    float y = float(source->getHeight()/2.0f);
    GLfloat vertices[] =  {-x,-y,0.0f,
                           x,-y,0.0f,
                           x,y,0.0f,
                           -x,y,0.0f
                          };
    //tcoords, easy
    GLfloat tcoords[] = {0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};
    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );

    glPopMatrix();

}

//this draws a texture with a clipping rectangle
void PhRenderSystem::drawTexturePart( PhTexture* source, PhVector2d pos, PhRect rect,  float depth, float rot, float scale, PhColor color, bool flip)
{
    //now for texture manipulations
    glMatrixMode(GL_TEXTURE);

    glPushMatrix();

    glTranslatef(  float(rect.getX()) / source->getWidth() ,  float(rect.getY()) / source->getHeight() ,0.0f);

    glScalef( (float(rect.getWidth())/source->getWidth()), (float(rect.getHeight())/source->getHeight()), 1.0f);

    //modelview manipulations
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //Move the the center of the image
    glTranslatef(pos.getX()+(rect.getWidth()/2),pos.getY()+(rect.getHeight()/2),depth);

    //flip?
    if (flip)
    {
        glRotatef(180.0f,0.0f,1.0f,0.0f);
    }

    //Rotate
    glRotatef(rot,0.0f,0.0f,1.0f);

    //scale
    glScalef(scale,scale,1.0f);

    glEnable(GL_TEXTURE_2D); //enable textures

    source->bindTexture();

    //colors
    GLuint colors[] = {color.toGLColor(), color.toGLColor(), color.toGLColor(), color.toGLColor()};
    //normals (each vector is (0.0f,0.0f,1.0f) )
    GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
    //vertices
    float x = float(rect.getWidth()/2.0f);
    float y = float(rect.getHeight()/2.0f);
    GLfloat vertices[] =  {-x,-y,0.0f,
                           x,-y,0.0f,
                           x,y,0.0f,
                           -x,y,0.0f
                          };
    //tcoords, easy
    GLfloat tcoords[] = {0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};
    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );

    glPopMatrix();

    //restore texture matrix
    glMatrixMode(GL_TEXTURE);

    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
//font stuff.
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::setFont( PhTexture* t )
{
    font = t;
}

PhTexture* PhRenderSystem::getFont()
{
    return font;
}

////////////////////////////////////////////////////////////////////////////////
//Draw text on the screen
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawText( std::string text, PhVector2d pos, PhColor color, float depth)
{


    //xoff lets us know where to draw the next character
    int xoff = 0;

    //this is a little value for conveince
    float temp = 16.0/256.0;

    for (int i=0; i<text.size(); i++)
    {

        //load our identity
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();

        //Enable texturing
        glEnable(GL_TEXTURE_2D);

        //disable lighting
        glDisable(GL_LIGHTING);

        //Load the texture
        font->bindTexture();

        //move to where we are
        glTranslatef(pos.getX()+xoff,pos.getY(),depth);

        //colors
        GLuint colors[] = {color.toGLColor(), color.toGLColor(), color.toGLColor(), color.toGLColor()};
        //normals (each vector is (0.0f,0.0f,1.0f) )
        GLfloat normals[] = {0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f};
        //vertices
        float x = 8.0f;
        float y = 8.0f;
        GLfloat vertices[] =  {-x,-y,0.0f,
                               x,-y,0.0f,
                               x,y,0.0f,
                               -x,y,0.0f
                              };
        //tcoords, little more difficult
        GLfloat tcoords[] = {glyphs[text[i]].t.getX(),glyphs[text[i]].t.getY(),
                             temp+glyphs[text[i]].t.getX(),glyphs[text[i]].t.getY(),
                             temp+glyphs[text[i]].t.getX(),temp+glyphs[text[i]].t.getY(),
                             glyphs[text[i]].t.getX(),temp+glyphs[text[i]].t.getY()
                            };
        //indexlist, pretty simple
        GLuint indexlist[] = {0,1,3,1,2,3};

        //tell the engine to draw it
        drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );

        //Disable texturing
        glDisable(GL_TEXTURE_2D);

        //make the engine restore the lighting state
        setLighting(getLighting());

        //add to our offset
        xoff+=10;

        glPopMatrix();
    }



}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the events handler
////////////////////////////////////////////////////////////////////////////////

PhEventHandler* PhRenderSystem::getEventHandler()
{
    return events;
}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the texture manager
////////////////////////////////////////////////////////////////////////////////

PhTextureManager* PhRenderSystem::getTextureManager()
{
    return textures;
}

////////////////////////////////////////////////////////////////////////////////
//sets and gets the lighting state
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::setLighting(bool a)
{
    if (a)
    {
        glEnable(GL_LIGHTING);
        lighting = true;
    }
    else
    {
        glDisable(GL_LIGHTING);
        lighting = false;
    }
}

bool PhRenderSystem::getLighting()
{
    return lighting;
}
