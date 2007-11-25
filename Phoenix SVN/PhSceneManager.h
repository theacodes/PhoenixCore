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

#ifndef PHOENIXSM
#define PHOENIXSM

#include "PhRenderSystem.h"
#include "PhView.h"
#include "PhPolygonCollision.h"


namespace phoenix
{

    //! Scenenode Prototype.
    /*!
        This is the prototype for a scenenode, all scenenodes should be derived from
        this class.
    */
    class PhSceneNode
    {
    protected:

        //! Depth value.
        /*!
            This value is used by the scenemanger to depth sort all drawn nodes.
            if your object does not execute the onRender() call, then it does not
            matter to you.
            \sa getDepth(), setDepth(), phoenix::PhSceneManager
        */
        float depth;

    public:

        //! Constructor.
        /*!
            Does nothing as this is a base class meant to be derived from.
        */
        PhSceneNode()
        {}

        //! Virtual destructor.
        /*!
            Does nothing.
        */
        virtual ~PhSceneNode()
        {}

        //! Pre-render call.
        /*!
            All nodes in the list will have this function called by the scenemanger
            once per frame. Overloading this is required. If the scene node wants to be drawn
            it must call phoenix::PhSceneManger::registerForRendering().
        */
        virtual void onPreRender()
        {}

        //! Render call.
        /*!
            Any nodes that called phoenix::PhSceneManger::registerForRendering() will first be
            sorted according to their depth, then this function is called for each node in order.
            It is highly suggested that you put any drawing code in this function. Of course, it's
            possible to draw during any of the three node passes, but this pass is the only one that is
            exclusive (Nodes must register) and is the only one that is depth sorted.
        */
        virtual void onRender()
        {}

        //! Post-render call.
        /*!
            The third render pass takes place at the end of every frame, the scene manager calls this
            function for every node in the list, and any code that should happen after everything is drawn
            should go here.
        */
        virtual void onPostRender()
        {}

        //! Set depth function.
        /*!
            Sets the depth of this node.
            \param d The new depth.
            \sa depth
        */
        void setDepth(float d)
        {
            depth = d;
        }

        //! Get depth function.
        /*!
            Returns the current depth of this node.
            \return Current depth.
            \sa depth
        */
        float getDepth()
        {
            return depth;
        }

    };

    //! Scene Manger Class
    /*!
        This is the phoenix scene manager. This allows for a representation of all objects in the game
        through the use of nodes. All objects are nodes and all nodes are dervied from phoenix::PhSceneNode.
        This class organizes and manages all scene nodes.
    */
    class PhSceneManager
    {

    protected:

        //! Pointer to phoenix::PhRenderSystem.
        /*!
            Stores a pointer the render system used to draw all the nodes.
            \sa getRenderSystem()
        */
        PhRenderSystem* system;

        //! Vector containing all the nodes.
        /*!
            This is a vector that contains pointers to every node in the scene graph.
            \sa addNode(), removeNode()
        */
        std::vector<PhSceneNode*> nodes;

        //! List of nodes to be rendered.
        /*!
            This is a list of all nodes that call registerForRendering(), it is
            sorted and used to call phoenix::PhSceneNode::onRender() in order.
            \sa drawAll(), registerForRendering()
        */
        std::vector<PhSceneNode*> rendernodes;

        //! Pointer to the collision handler.
        /*!
            This holds a pointer to phoenix::PhPolygonCollisionHanlder. When this is
            not null, the scene manager takes care of checking for collisions and does it
            after the pre-render sweep and before the render sweep.
            \sa phoenix::PhCollisionHandler, drawAll(), setCollisionHandler(), getCollisionHandler()
        */
        PhPolygonCollisionHandler* colhandle;

        //! Number of nodes.
        /*!
            A simple count of all the nodes, probably not needed. (Could use std::vector::size())
        */
        int nodecount;

        //! Number of nodes to be rendered.
        /*!
            A simple count of all the nodes to be rendered, probably not needed. (Could use std::vector::size())
        */
        int rnodecount;

        //! The default view.
        /*!
            A simple count of all the nodes, probably not needed. (Could use std::vector::size())
            \sa getView(), setView()
        */
        PhView* defview;

    private:

        //! Overloaded sort.
        /*!
            Function that sorts the nodes according to depth.
        */
        static bool depthSort(PhSceneNode* a, PhSceneNode* b)
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

    public:

        //! Constructor.
        /*!
            Simply makes a new scenemanager that uses the defined rendersystem
            \param s A pointer to the rendersystem that every object will use.
            \sa phoenix::PhRenderSystem
        */
        PhSceneManager(PhRenderSystem* s);

        //! Destructor.
        /*!
            Deletes all nodes in the list.
        */
        ~PhSceneManager();

        //! Get render system call.
        /*!
            Returns a pointer to the render system used by this scenemanger.
            \sa phoenix::PhRenderSystem()
            \return A pointer to phoenix::PhRenderSystem().
        */
        PhRenderSystem* getRenderSystem();

        //! Adds a scene node to the list.
        /*!
            Pushes a scene node onto the list.
            \param ptr A pointer to phoenix::PhSceneNode.
        */
        void addNode(PhSceneNode* ptr);

        //! Removes a node from the list
        /*!
            Finds and removes the node given from the list. Does not actually delete the node.
            \param ptr A pointer to phoenix::PhSceneNode.
        */
        void removeNode(PhSceneNode* ptr);

        //! Register a node to be rendered.
        /*!
            Registers a scene node to the lists of nodes to be rendered. This list is depth sorted after the
            pre render pass and then only the nodes in this list have their phoenix::PhSceneNode::onRender()
            function called.
            \param ptr A pointer to phoenix::PhSceneNode.
            \sa phoenix::PhSceneNode::onRender(), drawAll()
        */
        void registerForRendering(PhSceneNode* ptr);

        //! Does one step for all the nodes.
        /*!
            This function's name is a bit misleading (change in future versions?). This call is the main point
            of the scene manager. It does the following:
            1) Calls onPreRender() for all the nodes
            2) If applicable, check for collisions
            3) Sorts all the nodes to be "drawn"
            4) Calls onRender() for the sorted nodes in order
            5) Calls onPostRender() for all nodes.
            \sa registerForRendering(), setCollisionHandler(), phoenix::PhSceneNode
        */
        void drawAll();

        //! Gets the collision handler.
        /*!
            This gets the currently collision handler that the scene manager is using to test collisions with.
            \return A pointer to phoenix::PhPolygonCollisionHandler
            \sa setCollisionHandler(), phoenix::PhPolygonCollisionHandler.
        */
        PhPolygonCollisionHandler* getCollisionHandler();

        //! Sets a collision handler.
        /*!
            This sets the collision manager that the scene manager will use to check for collisions.
            If this is set, then phoenix::PhPolygonCollisionHandler::testCollisions() is called after
            every prerender pass. If it is null then of course nothing happens.
            \param a A pointer to phoenix::PhPolygonCollisionHandler.
            \sa getCollisionHandler(), phoenix::PhPolygonCollisionHandler, drawAll(), colhandle
        */
        void setCollisionHandler(PhPolygonCollisionHandler* a);

        //! Gets the current view.
        /*!
            Simply returns a pointer to the current view used by the scene manager.
            \return a pointer to phoenix::PhView
            \sa setView(), phoenix::PhView
        */
        PhView* getView();

        //! Sets the current view
        /*!
            Sets the current view to the given view.
            \param a a pointer to the new view
            \sa getView(), phoenix::PhView
        */
        void setView(PhView* a);
        //! Sets the current view
        /*!
            Lazy version that simply changes the x and y of the current view.
            \param x The new X coordinate of the view.
            \param y The new Y coordinate of the view.
            \sa getView(), phoenix::PhView
        */
        void setView(int x, int y);

    };

}

#endif
