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

#ifndef PHOENIXSN
#define PHOENIXSN

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

        PhSceneNode(float d) : depth(d)
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

}

#endif
