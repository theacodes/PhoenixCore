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

#include "PhDrawNode.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct: Needs a pointer to the scenemanager. other arguments are image,
//x, y, and free on destroy.
////////////////////////////////////////////////////////////////////////////////

PhDrawSceneNode::PhDrawSceneNode(PhSceneManager* s, PhTexture* i, PhVector2d p, bool c)
	: PhSceneNode(0), pos(p), image(i), fod(c), smgr(s)
{
    system=smgr->getRenderSystem();
    //tell the scenemanager that we exist.
    smgr->addNode((PhSceneNode*)this);
}

////////////////////////////////////////////////////////////////////////////////
//Destruct
////////////////////////////////////////////////////////////////////////////////

PhDrawSceneNode::~PhDrawSceneNode()
{
    if(fod&&image!=NULL)
    {
        delete image;
    }
    smgr->removeNode(this);
}

////////////////////////////////////////////////////////////////////////////////
//Get and set functions for X and Y
////////////////////////////////////////////////////////////////////////////////

const PhVector2d& PhDrawSceneNode::getPosition () const
{
    return pos;
}

void PhDrawSceneNode::setPosition(const PhVector2d& a)
{
    pos=a;
}

////////////////////////////////////////////////////////////////////////////////
//Get and set image functions
////////////////////////////////////////////////////////////////////////////////

void PhDrawSceneNode::setTexture(PhTexture* img)
{
    if(img!=NULL)
    {
        image=img;
    }
}

PhTexture* PhDrawSceneNode::getTexture() const
{
    return image;
}

////////////////////////////////////////////////////////////////////////////////
//PreRender function, this is called before everything is render, and should
//only be called by the scenemanager
////////////////////////////////////////////////////////////////////////////////

void PhDrawSceneNode::onPreRender()
{
    smgr->registerForRendering(this);
}

////////////////////////////////////////////////////////////////////////////////
//Render call, this is called only if the node was registered. This should only
//be called by the scenemanager
////////////////////////////////////////////////////////////////////////////////

void PhDrawSceneNode::onRender()
{
    if(image!=NULL)
    {
        system->drawTexture(image,pos,depth);
    }
}

////////////////////////////////////////////////////////////////////////////////
//PostRender call, this is called after everything is rendered. This should
//only be called by the scenenmanager.
////////////////////////////////////////////////////////////////////////////////

void PhDrawSceneNode::onPostRender()
{
}
