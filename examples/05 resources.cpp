/*! Resource example.
    In this example we will explore phoenix's resources. It
    will show how to define custom resources and manipulate
    them.
*/

#include "Phoenix.h"

using namespace phoenix;
using namespace boost;

/*!
    The first thing we'll do is define our resource. We'll
    simply make a class and derive from Resource. 
*/
class ExampleResource
    : public Resource
{
public:

    /*!
        We'll befriend Resource so we can use it's create()
        function, as you'll see.
    */
    friend class Resource;

    /*!
        Because of the way phoenix works internally, all resources
        are constructed using the create() function- there are no
        public constructors. This function should create a new
        resource, encase it in a shared_ptr, initialize it's members,
        and return the pointer.
    */
    static shared_ptr<ExampleResource> create( ResourceManager& r )
    {
        /*!
            We'll skip the construction stuff by using Resource's templated
            create() function. This function works for all derived classes
            as long as their constructor only takes one argument ( The resource
            manager ). For more complex ones, we can just use new ExampleResource
            ( ... ). 
        */
        shared_ptr<ExampleResource> newresource = Resource::create<ExampleResource>( r );

        /*!
            Here we'll set up some stuff about our resource. We'll give it a
            random color and position.
        */
        newresource->color = Color( random(127,255), random(127,255), random(127,255) );
        newresource->position = Vector2d( random(0,620), random(0,440) );

        /*!
            Finally, we'll return the new resource.
        */
        return newresource;
    }

    /*!
        Now for an interesting function. This is our draw funcion which we
        will call for every resource.
    */
    void draw( RenderSystem& system )
    {
        /*!
            Just like in the Hello World example, we'll draw some text.
            This time we'll draw it with our position and color.
        */
        system.drawText( "Resource" , position, color );

        /*!
            What if we'd like for these resources to go away? Well,
            in order to get rid of a resource, we drop it. Here we
            check if the user has pressed the spacebar, and if our
            random function landed on 1. If so, we'll drop this
            resource.
        */
        if( EventReceiver::getKeyPressed( PHK_SPACE ) && random(0,10) == 1 )
            drop();
    }

    /*!
        Also note that it is possible (and sometimes desired) to
        overload the drop() function. You can use drop as a moment
        to clear up or drop() and other resources. However, you
        should usually wait until the Garbage Collector calls the
        destructor before actually deleting any internal data.
    */

private:

    /*!
        Here you see we have a private constructor. This forces
        you to use the create() function to instance a resource.
    */
    ExampleResource( ResourceManager& r )
        : Resource( r )
    {
    }

    /*!
        These are just our color and position members.
    */
    Vector2d position;
    Color color;

};

int main()
{

    RenderSystem system;

    /*!
        We need a resource manager to keep track of all of
        our resources. We could use the system's internal
        resource manager, but we'd have to check for types
        in that case, because it also stores all the textures
        and fonts.
    */
    ResourceManager examples;

    /*!
        Now let's fill the resource manager with 10 resources.
        We'll call the create function like we did earlier.
    */
    for( int i = 0; i < 10; ++i )
    {
        ExampleResource::create( examples );
    }

    while( system.run() )
    {

        /*!
            Now we'll iterate through each resource and call draw().
            Because garbage collection occurs in another thread, we
            must lock the resource manager before doing so.
        */
        examples.lock();

        /*!
            Now the iteration. The loop looks more complicated than it actually is. 
            It's just standard list iteration. sometimes it's more asthetically 
            pleasing to use this:
                BOOST_FOREACH( shared_ptr<Resource>& r, examples.getResourceList() )
            but for this example I wanted to show iterating without foreach.
        */
        for( std::list< shared_ptr<Resource> >::iterator i = examples.getResourceList().begin(); i != examples.getResourceList().end(); ++i )
        {
            /*!
                First, we make sure the resource hasn't been dropped. Usually it is
                still safe to use dropped resources, but it is undesirable to do so.
            */
            if( ! (*i)->dropped() )
            {
                /*!
                    Now we'll use Resource's templated grab<>() function to automatically
                    cast to an ExampleResource and then we'll call our draw function.
                */
                (*i)->grab<ExampleResource>()->draw( system );
            }
        }

        /*!
            Finally, we can unlock our resource manager and let the garbage collector
            work.
        */
        examples.unlock();

    }

    return 0;

}
