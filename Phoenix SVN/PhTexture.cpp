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

#include "PhTexture.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
// Construct and Destruct
////////////////////////////////////////////////////////////////////////////////

PhTexture::PhTexture(PhTextureManager* t)
{
    texture=0;
    width=0;
    height=0;
    name = std::string("");
    txtmgr = t;
    txtmgr->addTexture(this);
}

PhTexture::PhTexture(PhTextureManager* t, int a, int b)
{

    txtmgr = t;
    txtmgr->addTexture(this);

    //make some room for the texture's data
    data = (unsigned char*)malloc(a*b*4);

    //make all the pixels white and fully opaque
    for (int i = 0; i<(a*b*4); i++)
    {
        *(data+i) = 255;
    }

    //Generate 1 texture
    glGenTextures(1,&texture);

    //Load the texture
    glBindTexture(GL_TEXTURE_2D, texture);

    //write the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, a, b, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //set the parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //set the width and height
    width=a;
    height=b;

    //clear the data (not needed until the texture is locked agian)
    free(data);
    data = NULL;

    name = std::string("");

}

PhTexture::~PhTexture()
{
    if (glIsTexture(texture))
    {
        glDeleteTextures(1, &texture);
    }

    if (data!=NULL)
    {
        free(data);
    }

    txtmgr->removeTexture(this);

}

////////////////////////////////////////////////////////////////////////////////
// set and get the texture ID
////////////////////////////////////////////////////////////////////////////////

void PhTexture::setTexture(GLuint text)
{
    texture=text;
}

GLuint PhTexture::getTexture()
{
    return texture;
}

////////////////////////////////////////////////////////////////////////////////
// set and get the texture name
////////////////////////////////////////////////////////////////////////////////

void PhTexture::setName(std::string nm)
{
    name=nm;
}

std::string PhTexture::getName()
{
    return name;
}


////////////////////////////////////////////////////////////////////////////////
// get and set width and height
////////////////////////////////////////////////////////////////////////////////

int PhTexture::getWidth()
{
    return width;
}

int PhTexture::getHeight()
{
    return height;
}

void PhTexture::setWidth(int var)
{
    width = var;
}

void PhTexture::setHeight(int var)
{
    height = var;
}

////////////////////////////////////////////////////////////////////////////////
// write and read pixel functions
// follows naming conventions, get and set pixel as of v0.1b
////////////////////////////////////////////////////////////////////////////////

void PhTexture::setPixel(int x, int y, PhColor col)
{

    if (data!=NULL)
    {

        *(data+(((y*width)+x)*4)) = col.getRed();
        *(data+(((y*width)+x)*4)+1) = col.getGreen();
        *(data+(((y*width)+x)*4)+2) = col.getBlue();
        *(data+(((y*width)+x)*4)+3) = col.getAlpha();

    }

}

PhColor PhTexture::getPixel(int x, int y)
{

    if (data!=NULL)
    {

        PhColor col;
        col.setRed(*(data+(((y*width)+x)*4)));
        col.setGreen(*(data+(((y*width)+x)*4)+1));
        col.setBlue(*(data+(((y*width)+x)*4)+2));
        col.setAlpha(*(data+(((y*width)+x)*4)+3));
        return col;

    }
    else
    {

        return PhColor(255,255,255,255);

    }

}

////////////////////////////////////////////////////////////////////////////////
// lock and unlock texture
////////////////////////////////////////////////////////////////////////////////

void PhTexture::unlockTexture()
{

    if (data!=NULL)
    {

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        free(data);

        data = NULL;

    }
}

bool PhTexture::lockTexture()
{

    data = (unsigned char*)malloc(width*height*4);

    if (data!=NULL)
    {

        glGetTexImage( GL_TEXTURE_2D , 0 , GL_RGBA , GL_UNSIGNED_BYTE, data );
        return true;

    }
    else
    {
        return false;
    }

}

////////////////////////////////////////////////////////////////////////////////
// Bind texture
////////////////////////////////////////////////////////////////////////////////

bool PhTexture::bindTexture()
{
    if (glIsTexture(texture)) //make sure this is a texture
    {
        glBindTexture(GL_TEXTURE_2D, texture); //set the texture
        return true;
    }
    return false;
}
