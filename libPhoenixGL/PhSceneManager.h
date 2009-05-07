/*

Copyright (c) 2007, Jonathan Wayne Parrott, Denzel Morris

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

    // forward declaration of PhLightManager
    class PhLightManager;

    // forward declartion of PhSceneNode
    class PhSceneNode;

    //! Scene Manager Class
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

        //! Pointer to the light manager.
        /*!
            The scenemanager handles per-pixel lighting for us, and it needs a pointer.
            \sa getLightManager(), setLightManager()
        */
        PhLightManager* lmgr;

        //! Lights enable
        /*!
            Enables or disables the lighting system. (default disabled).
            \sa enableLighting(), disableLighting()
        */
        bool lightenable;

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
        static bool depthSort(PhSceneNode* a, PhSceneNode* b);

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
        inline PhRenderSystem* getRenderSystem() const { return system; }

        //! Adds a scene node to the list.
        /*!
            Pushes a scene node onto the list.
            \param ptr A pointer to an instance of phoenix::PhSceneNode.
        */
        inline void addNode(PhSceneNode* ptr) { nodes.push_back(ptr); }

        //! Removes a node from the list
        /*!
            Finds and removes the node given from the list. Does not actually delete the node.
            \param ptr A pointer to an instance of phoenix::PhSceneNode.
        */
        void removeNode(PhSceneNode* ptr);

        //! Register a node to be rendered.
        /*!
            Registers a scene node to the lists of nodes to be rendered. This list is depth sorted after the
            pre render pass and then only the nodes in this list have their phoenix::PhSceneNode::onRender()
            function called.
            \param ptr A pointer to an instance of phoenix::PhSceneNode.
            \sa phoenix::PhSceneNode::onRender(), drawAll()
        */
        inline void registerForRendering(PhSceneNode* ptr) { rendernodes.push_back(ptr); }

        //! Does one step for all the nodes.
        /*!
            This function's name is a bit misleading (change in future versions?). This call is the main point
            of the scene manager. It does the following:<br>
            1) Sets the view.<br>
            2) Generates the light buffer (if enabled).<br>
            3) Calls onPreRender() for all the nodes<br>
            4) If applicable, check for collisions<br>
            5) Sorts all the nodes to be "drawn"<br>
            6) Calls onRender() for the sorted nodes in order<br>
            7) Draws the light buffer over the scene.<br>
            8) Calls onPostRender() for all nodes.<br>
            \sa registerForRendering(), setCollisionHandler(), phoenix::PhSceneNode
        */
        void drawAll();

        //! Gets the collision handler.
        /*!
            This gets the currently collision handler that the scene manager is using to test collisions with.
            \return A pointer to phoenix::PhPolygonCollisionHandler
            \sa setCollisionHandler(), phoenix::PhPolygonCollisionHandler.
        */
        inline PhPolygonCollisionHandler* getCollisionHandler() const { return colhandle; }

        //! Sets a collision handler.
        /*!
            This sets the collision manager that the scene manager will use to check for collisions.
            If this is set, then phoenix::PhPolygonCollisionHandler::testCollisions() is called after
            every prerender pass. If it is null then of course nothing happens.
            \param a A pointer to an instance of phoenix::PhPolygonCollisionHandler.
            \sa getCollisionHandler(), phoenix::PhPolygonCollisionHandler, drawAll(), colhandle
        */
        inline void setCollisionHandler(PhPolygonCollisionHandler* a) { colhandle = a; }

        //! Get light manager.
        /*!
            \sa PhLightManager, setLightManager(), enableLighting()
            \return A pointer to the current light manager.
        */
        inline PhLightManager* getLightManager() const { return lmgr; }

        //! Set light manager.
        /*!
            Changes the currently active light manager.
            \sa PhLightManager, getLightManager(), setLightingEnabled()
        */
        inline void setLightManager(PhLightManager* l) { lmgr = l; }

        //! Get lighting state
        /*!
			\returns True if lights are enabled, otherwise false.
			\sa setLightingEnabled()
        */
        inline bool& getLightingEnabled() { return lightenable; }

        //! Set lighting state
		/*!
			\param s True if you want to enable lights, otherwise false.
		*/
		inline void setLightingEnabled(const bool& s) { lightenable = s; }

        //! Gets the current view.
        /*!
            Simply returns a pointer to the current view used by the scene manager.
            \return a pointer to phoenix::PhView containing the current view.
            \sa setView(), phoenix::PhView
        */
        inline PhView* getView() const { return defview; }

        //! Sets the current view
        /*!
            Sets the current view to the given view.
            \param a a pointer to the new view
            \sa getView(), phoenix::PhView
        */
        inline void setView(PhView* a) { defview = a; }

        //! Sets the current view
        /*!
            Lazy version that simply changes the x and y of the current view.
            \param pos The new position of the view
            \sa getView(), phoenix::PhView
        */
        inline void setView( const PhVector2d& pos ) { defview->setPosition( pos ); }

    };

}

#include "PhSceneNode.h"
#include "PhLightManager.h"

#endif
