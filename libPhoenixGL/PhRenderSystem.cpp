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
#include "PrecompiledFont.h"
#include "glpng.h"
#include <iostream>
#include <GL/glfw.h>

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct & Destruct
////////////////////////////////////////////////////////////////////////////////

PhRenderSystem::PhRenderSystem()
        : events(NULL), textures(NULL), fpstimer(), frame(0), vertexlighting(false)
{
}

PhRenderSystem::~PhRenderSystem()
{

    delete events; //delete event reciever

    delete textures; //insures all the textures are cleaned up

    delete logs; //cleans up all the logs

	delete vlsys; //delete all of our lights

    glfwCloseWindow();

    glfwTerminate();

}

////////////////////////////////////////////////////////////////////////////////
//Sets the caption of the window
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::setWindowCaption(const std::string& str)
{
	glfwSetWindowTitle(str.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//run function, should be called once every loop, it makes things ready for
//a render.
////////////////////////////////////////////////////////////////////////////////

bool PhRenderSystem::run()
{

    //update events
    events->updateEvents();

    glfwPollEvents();

    //flip the screen
    glfwSwapBuffers();

    //clear it
    glClearColor(0.f,0.f,0.f,1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //fps calculation
    frame+=1;

    //lights
    if(vertexlighting == true)
    {
        vlsys->setLights();
    }

    return true;

}

////////////////////////////////////////////////////////////////////////////////
//Gets how fast the system is rendering
////////////////////////////////////////////////////////////////////////////////

const float PhRenderSystem::getFPS() const
{

    //Calculate the frames per second and create the string
    return ( float(frame) / float(fpstimer.getTicks()) );

}

////////////////////////////////////////////////////////////////////////////////
//Get the number of ticks since this thing was created
////////////////////////////////////////////////////////////////////////////////

const double PhRenderSystem::getTicks() const
{

    return fpstimer.getTicks();

}

////////////////////////////////////////////////////////////////////////////////
//This initializes the system
////////////////////////////////////////////////////////////////////////////////

bool PhRenderSystem::initSystem( const PhVector2d& sc , const bool& fs )
{

    //somevars up everything else
    screensize = sc;

    //No GLFW functions may be called before this
    glfwInit();

    if(fs)
    {
        glfwOpenWindow(int(screensize.getX()), int(screensize.getY()), 0,0,0,0, 8, 0, GLFW_FULLSCREEN);
    }
    else
    {
        glfwOpenWindow(int(screensize.getX()), int(screensize.getY()), 8,8,8,8, 8, 0, GLFW_WINDOW);
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
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); // Set The Blending Function For Translucency
    glEnable(GL_BLEND); //enable blending

    //Materials
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Material mode
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);

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
    setWindowCaption("PhoenixGL v0.2");

    //set the events
    events = new PhEventHandler;

    //set the logs
    logs = new PhLogManager;

    //set GLFW callbacks
    glfwSetKeyCallback( &PhEventHandler::KeyboardCallback );
    glfwSetMouseButtonCallback( &PhEventHandler::MouseButtonCallback );
    glfwSetMousePosCallback( &PhEventHandler::MousePosCallback );
    glfwSetWindowCloseCallback( &PhEventHandler::WindowCloseCallback );
    glfwSetMouseWheelCallback( &PhEventHandler::MouseWheelPosCallback );

    glfwDisable(GLFW_KEY_REPEAT);

    //set the textures
    textures = new PhTextureManager;

    //load our default font
    string ffn = saveBuiltinFont();
    font = loadTexture(ffn);
    remove(ffn.c_str());

    //Start our fps timer
    fpstimer.startTimer();

    //Make a vertex light system
    vlsys = new PhVertexLightSystem();

    //everything was fine
    return true;

}

////////////////////////////////////////////////////////////////////////////////
//Get screen size
////////////////////////////////////////////////////////////////////////////////

const PhVector2d PhRenderSystem::getScreenSize() const
{
    return screensize;
}

////////////////////////////////////////////////////////////////////////////////
//Load texture function
////////////////////////////////////////////////////////////////////////////////

PhTexture* PhRenderSystem::loadTexture( const std::string& filename, const bool& linear )
{

    try
    {

        //This is the class that will hold our texture
        PhTexture* ctext = new PhTexture(textures);

        int width=0,height=0;

        //OpenGL Texture ID
        GLuint texture;

        //Genereate 1 texture
        glGenTextures(1,&texture);

        //Load the texture
        glBindTexture(GL_TEXTURE_2D, texture);

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

        //Generate the texture
        if (filename.find(".png")!=std::string::npos)
        {

            pngInfo pinfo;

            if(pngLoad(filename.c_str(), PNG_NOMIPMAP, PNG_ALPHA, &pinfo)){
                width = pinfo.Width;
                height = pinfo.Height;
            }
            else
            {
                throw(-1);
            }


        }

        if (filename.find(".bmp")!=std::string::npos)
        {
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedImage->w, loadedImage->h, 0, GL_BGR, GL_UNSIGNED_BYTE, loadedImage->pixels);
        }

        //Set up the PhTexture class
        ctext->setTexture(texture);
        ctext->setWidth(width);
        ctext->setHeight(height);
        ctext->setName(filename);

        //Return our texture
        return ctext;

        //add it to the texture list to be cleaned up
        textures->addTexture(ctext);

    }

    catch(int e)
    {

        PhTexture* ctext = new PhTexture(textures);
        ctext->setTexture(0);
        ctext->setWidth(0);
        ctext->setHeight(0);
        ctext->setName("FAILEDTOLOAD");

        //Return our texture
        return ctext;

        //add it to the texture list to be cleaned up
        textures->addTexture(ctext);

    }

    //should never happen
    return NULL;

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
//Draws an indexed triangle fan
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawIndexedTriangleFan(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, int vertcount )
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
    glDrawElements(GL_TRIANGLE_FAN, vertcount, GL_UNSIGNED_INT, indexlist);

    //restore our states
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY );
    glDisableClientState(GL_NORMAL_ARRAY );

}

////////////////////////////////////////////////////////////////////////////////
//Draws an indexed line.
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawIndexedLine(GLfloat* vertices, GLfloat* normals, GLfloat* tcoords, GLuint* colors, GLuint* indexlist, int vertcount )
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
    glDrawElements(GL_LINE_STRIP, vertcount, GL_UNSIGNED_INT, indexlist);

    //restore our states
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY );
    glDisableClientState(GL_NORMAL_ARRAY );

}

////////////////////////////////////////////////////////////////////////////////
//Draws a line
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawLine(PhVector2d v1, PhVector2d v2, float depth, PhColor a, PhColor b)
{

    //load the idenity
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //move to our depth
    glTranslatef(0.0f,0.0f,depth);

    //fill some arrays
    GLfloat verts[] = { v1.getX(), v1.getY(), 0.0f, v2.getX(), v2.getY(), 0.0f };
    GLfloat normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat tcoords[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    GLuint colors[] = { a.toGLColor(), b.toGLColor() };
    GLuint indexlist[] = { 0, 1 };

    //draw the elements
    glDisable(GL_TEXTURE_2D);
    drawIndexedLine(verts,normals,tcoords,colors,indexlist,2);
    glEnable(GL_TEXTURE_2D);

    //restore matrix
    glPopMatrix();

}

////////////////////////////////////////////////////////////////////////////////
//Draws a line
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawRay(PhVector2d origin, PhVector2d ray, float depth, PhColor a, PhColor b)
{

    //load the idenity
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //move to our depth
    glTranslatef(0.0f,0.0f,depth);

    //fill some arrays
    GLfloat verts[] = { origin.getX(), origin.getY(), 0.0f, origin.getX()+ray.getX(), origin.getY()+ray.getY(), 0.0f };
    GLfloat normals[] = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat tcoords[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    GLuint colors[] = { a.toGLColor(), b.toGLColor() };
    GLuint indexlist[] = { 0, 1 };

    //draw the elements
    glDisable(GL_TEXTURE_2D);
    drawIndexedLine(verts,normals,tcoords,colors,indexlist,2);
    glEnable(GL_TEXTURE_2D);

    //restore matrix
    glPopMatrix();

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
    GLfloat tcoords[] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    glDisable(GL_TEXTURE_2D);
    drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );
    glEnable(GL_TEXTURE_2D);

    glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////
//Draws a polygon
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawPolygon (PhPolygon P, float depth, PhColor a)
{

    //load the idenity
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);

    //move where we need to be
    glTranslatef(P.getPosition().getX(), P.getPosition().getY(), depth);

    //Cuts down the number of getVertexCount()s from 6 to 1 + the number of loops
    int vertexCount = P.getVertexCount();

    //make some space for the arrays
    GLuint* colors = new GLuint[vertexCount];
    GLuint* indexlist = new GLuint[vertexCount];
    GLfloat* normals = new GLfloat[vertexCount*3];
    GLfloat* vertices = new GLfloat[vertexCount*3];
    GLfloat* tcoords = new GLfloat[vertexCount*2];

    //fill them
    for (int i = 0; i < vertexCount; i ++)
    {
        //Cuts down the number of multiples from 6 to 1 per loop
        int triple_i = i*3;

        colors[i] = a.toGLColor();

        normals[triple_i] = 0.0f;
        normals[triple_i+1] = 0.0f;
        normals[triple_i+2] = 1.0f;

        vertices[triple_i] = P.getVertex(i).getX();
        vertices[triple_i+1] = P.getVertex(i).getY();
        vertices[triple_i+2] = 0.0f;

        indexlist[i] = i;

    }

    //now just tell the engine to draw it
    drawIndexedTriangleFan(vertices,normals,tcoords,colors,indexlist,vertexCount);

    glPopMatrix();

    delete[] colors;
    delete[] normals;
    delete[] indexlist;
    delete[] vertices;

    // enable texturing
    glEnable(GL_TEXTURE_2D);

}

////////////////////////////////////////////////////////////////////////////////
//Draws a polygon
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawTexturedPolygon (PhPolygon P, PhTexture* texture, float depth, PhColor a)
{

    //load the idenity
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    // Ensable texturing
    glEnable(GL_TEXTURE_2D);

    //bind the texture
    texture->bindTexture();

    glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	float s_plane[] = { 1.0f/texture->getWidth(), 0.0, 0.0, 0.0};
	float t_plane[] = { 0.0, 1.0f/texture->getHeight(), 0.0, 0.0};

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, s_plane);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, t_plane);

    //move where we need to be
    glTranslatef(P.getPosition().getX(), P.getPosition().getY(), depth);

    //Cuts down the number of getVertexCount()s from 6 to 1 + the number of loops
    int vertexCount = P.getVertexCount();

    //make some space for the arrays
    GLuint* colors = new GLuint[vertexCount];
    GLuint* indexlist = new GLuint[vertexCount];
    GLfloat* normals = new GLfloat[vertexCount*3];
    GLfloat* vertices = new GLfloat[vertexCount*3];
    GLfloat* tcoords = new GLfloat[vertexCount*2];

    //fill them
    for (int i = 0; i < vertexCount; i ++)
    {
        //Cuts down the number of multiples from 6 to 1 per loop
        int triple_i = i*3;

        colors[i] = a.toGLColor();

        normals[triple_i] = 0.0f;
        normals[triple_i+1] = 0.0f;
        normals[triple_i+2] = 1.0f;

        vertices[triple_i] = P.getVertex(i).getX();
        vertices[triple_i+1] = P.getVertex(i).getY();
        vertices[triple_i+2] = 0.0f;

        indexlist[i] = i;

    }

    //now just tell the engine to draw it
    drawIndexedTriangleFan(vertices,normals,tcoords,colors,indexlist,vertexCount);

    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

    delete[] colors;
    delete[] normals;
    delete[] indexlist;
    delete[] vertices;

}


////////////////////////////////////////////////////////////////////////////////
//Renders a Texture
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::drawTexture(  PhTexture* source, PhVector2d pos, float depth, float rot, PhVector2d scale, PhColor color, bool hflip, bool vflip)
{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //Move the the center of the image
    glTranslatef(pos.getX()+(source->getWidth()/2),pos.getY()+(source->getHeight()/2),depth);

    //Rotate
    glRotatef(rot,0.0f,0.0f,1.0f);

    //scale
    glScalef(scale.getX(),scale.getY(),1.0f);

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
    if( hflip )
    {
        tcoords[0] = 1.0f;
        tcoords[2] = 0.0f;
        tcoords[4] = 0.0f;
        tcoords[6] = 1.0f;
    }

    if( vflip )
    {
        tcoords[1] = 1.0f;
        tcoords[3] = 1.0f;
        tcoords[5] = 0.0f;
        tcoords[7] = 0.0f;
    }

    //indexlist, pretty simple
    GLuint indexlist[] = {0,1,3,1,2,3};

    //now just tell the engine to draw it
    drawIndexedTriangleList(vertices,normals,tcoords,colors,indexlist, 2 );

    glPopMatrix();

    glDisable(GL_TEXTURE_2D); //enable textures

}

//this draws a texture with a clipping rectangle
void PhRenderSystem::drawTexturePart( PhTexture* source, PhVector2d pos, PhRect rect,  float depth, float rot, PhVector2d scale, PhColor color, bool hflip, bool vflip)
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

    //Rotate
    glRotatef(rot,0.0f,0.0f,1.0f);

    //scale
    glScalef(scale.getX(),scale.getY(),1.0f);

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
    //tcoords
    GLfloat tcoords[] = {0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f};
    if( hflip )
    {
        tcoords[0] = 1.0f;
        tcoords[2] = 0.0f;
        tcoords[4] = 0.0f;
        tcoords[6] = 1.0f;
    }

    if( vflip )
    {
        tcoords[1] = 1.0f;
        tcoords[3] = 1.0f;
        tcoords[5] = 0.0f;
        tcoords[7] = 0.0f;
    }
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

PhTexture* PhRenderSystem::getFont() const
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
    float temp = 0.0625f;

    for (unsigned int i=0; i<text.size(); i++)
    {

        //load our identity
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();

        //Enable texturing
        glEnable(GL_TEXTURE_2D);

        //disable vertexlighting
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

        //make the engine restore the vertexlighting state
        setVertexLighting(getVertexLighting());

        //add to our offset
        xoff+=10;

        glPopMatrix();
    }



}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the events handler
////////////////////////////////////////////////////////////////////////////////

PhEventHandler* PhRenderSystem::getEventHandler() const
{
    return events;
}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the texture manager
////////////////////////////////////////////////////////////////////////////////

PhTextureManager* PhRenderSystem::getTextureManager() const
{
    return textures;
}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the log manager
////////////////////////////////////////////////////////////////////////////////

PhLogManager* PhRenderSystem::getLogManager() const
{
	return logs;
}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the light system.
////////////////////////////////////////////////////////////////////////////////

PhVertexLightSystem* PhRenderSystem::getVertexLightSystem() const
{
	return vlsys;
}

////////////////////////////////////////////////////////////////////////////////
//sets blending mode
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::setBlendMode(GLenum src, GLenum dst){
    glBlendFunc(src,dst);
}

void PhRenderSystem::setDefaultBlendMode(){
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

////////////////////////////////////////////////////////////////////////////////
//sets and gets the vertexlighting state
////////////////////////////////////////////////////////////////////////////////

void PhRenderSystem::setVertexLighting(const bool& a)
{
    if (a)
    {
        glEnable(GL_LIGHTING);
        vertexlighting = true;
    }
    else
    {
        glDisable(GL_LIGHTING);
        vertexlighting = false;
    }
}

const bool& PhRenderSystem::getVertexLighting() const
{
    return vertexlighting;
}
