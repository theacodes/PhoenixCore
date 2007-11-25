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

#include "PhSceneManager.h"

using namespace phoenix;

////////////////////////////////////////////////////////////////////////////////
//Construct and destruct
////////////////////////////////////////////////////////////////////////////////

PhSceneManager::PhSceneManager(PhRenderSystem* s)
{
    system=s;
    nodecount=0;
    rnodecount=0;
    colhandle = NULL;
    defview = new PhView(system);
}

PhSceneManager::~PhSceneManager()
{
    //remove all the nodes........
    for(int i=0;i<nodecount;i++)
    {
        if(nodes[i]!=NULL)
        {
            delete nodes[i];
        }
    }
    nodes.clear();
    rendernodes.clear();
}

////////////////////////////////////////////////////////////////////////////////
//Returns a pointer to the rendersystem
////////////////////////////////////////////////////////////////////////////////

PhRenderSystem* PhSceneManager::getRenderSystem()
{
    return system;
}

////////////////////////////////////////////////////////////////////////////////
//This adds a scenenode to the list, only a scenenode should call this during
//construction
////////////////////////////////////////////////////////////////////////////////

void PhSceneManager::addNode(PhSceneNode* ptr)
{
    nodes.push_back(ptr);
    nodecount+=1;
}

////////////////////////////////////////////////////////////////////////////////
//Removes a scenenode from the list, only a scenenode should call this during
//destruction
////////////////////////////////////////////////////////////////////////////////

void PhSceneManager::removeNode(PhSceneNode* ptr)
{
    for(int i=0;i<nodecount;i++)
    {
        if(nodes[i]==ptr)
        {
            nodes.erase(nodes.begin()+i);
            nodecount-=1;
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//This registers a scenenode to have onRender() called. The node is depth
//sorted according to what itss getDepth() function returns
////////////////////////////////////////////////////////////////////////////////

void PhSceneManager::registerForRendering(PhSceneNode* ptr)
{
    rendernodes.push_back(ptr);
    rnodecount+=1;
}

////////////////////////////////////////////////////////////////////////////////
//This is the draw function, it sorts the nodes and draws everything.
//onPreRender and onPostRender will be called on all nodes, regardless of if
//they are registered for rendering or not. onRender will only be called on
//scenenodes registered for rendering.
////////////////////////////////////////////////////////////////////////////////

void PhSceneManager::drawAll()
{

    //first set the view to the default.
    defview->setGLView();

    //prerender
    for(int i=0;i<nodecount;i++)
    {
        if(nodes[i]!=NULL)
        {
            (nodes[i])->onPreRender();
        }
    }

    //sort the nodes
    std::sort(rendernodes.begin(),rendernodes.end(), &depthSort);

    //first set the view to the default.
    defview->setGLView();

    //test collisions
    if(colhandle != NULL){
        colhandle->testCollisions();
    }

    //render
    for(int i=0;i<rnodecount;i++)
    {
        if(rendernodes[i]!=NULL)
        {
            (rendernodes[i])->onRender();
        }
    }

    //postrender
    for(int i=0;i<nodecount;i++)
    {
        if(nodes[i]!=NULL)
        {
            (nodes[i])->onPostRender();
        }
    }

    //clear stuff
    rendernodes.clear();
    rnodecount=0;
}

////////////////////////////////////////////////////////////////////////////////
// Get and set collision handler, if it isn't null, then collisions are tested
// after PreRender() and before Render()
////////////////////////////////////////////////////////////////////////////////

PhPolygonCollisionHandler* PhSceneManager::getCollisionHandler() {
    return colhandle;
}

void PhSceneManager::setCollisionHandler(PhPolygonCollisionHandler* a){
    colhandle = a;
}

////////////////////////////////////////////////////////////////////////////////
// View management functions, should be self-explainitory
////////////////////////////////////////////////////////////////////////////////

PhView* PhSceneManager::getView()
{
    return defview;
}

void PhSceneManager::setView(PhView* a)
{
    defview = a;
}

void PhSceneManager::setView(int x, int y)
{
    defview->setX(x);
    defview->setY(y);
}
