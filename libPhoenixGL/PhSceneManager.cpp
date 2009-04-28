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
	: system(s), colhandle(NULL), lightenable(false)
{
    defview = new PhView(system);
    lmgr = new PhLightManager(this);
    lightenable = false;
}

PhSceneManager::~PhSceneManager()
{
    //remove all the nodes........
    for(unsigned int i=0;i<nodes.size();++i)
    {
        if(nodes[i]!=NULL)
        {
            delete nodes[i];
        }
    }
    //nodes.clear();
    //rendernodes.clear();

    delete lmgr;
    delete defview;
    //if( colhandle != NULL ) delete colhandle;
}

////////////////////////////////////////////////////////////////////////////////
// Sort function
////////////////////////////////////////////////////////////////////////////////

bool PhSceneManager::depthSort(PhSceneNode* a, PhSceneNode* b)
{
	if ( a->getDepth() < b->getDepth() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////
//Removes a scenenode from the list, only a scenenode should call this during
//destruction
////////////////////////////////////////////////////////////////////////////////

void PhSceneManager::removeNode(PhSceneNode* ptr)
{
    for(unsigned int i=0;i<nodes.size();++i)
    {
        if(nodes[i]==ptr)
        {
            nodes.erase(nodes.begin()+i);
            break;
        }
    }
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

    //Generate our light buffer
    if(lightenable) lmgr->generateBuffer();

    //prerender
    for(unsigned int i=0;i<nodes.size();++i)
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
    for(unsigned int i=0;i<rendernodes.size();++i)
    {
        if(rendernodes[i]!=NULL)
        {
            (rendernodes[i])->onRender();
        }
    }

    //draw our light buffer.
    if(lightenable) lmgr->renderBuffer();

    //postrender
    for(unsigned int i=0;i<nodes.size();++i)
    {
        if(nodes[i]!=NULL)
        {
            (nodes[i])->onPostRender();
        }
    }

    //clear stuff
    rendernodes.clear();
}
