~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			    PhoenixCore v0.2
			       April 2010
			        Jon Parrott

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thank you for your interest in PhoenixCore. At this
stage in development, Phoenix is just a rendering
framework. As such, it does not provide a lot
of the constructs required for developing 2d games
( such as classes for sprites ). While Phoenix does
not provide such high-level constructs, it does
provide a simple and flexible framework on which
to develop these constructs.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				    Building

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			    = Requirements =
			    
Phoenix requires the following libraries:
    
    * Cmake 2.8
    * Boost C++ Libraries ( 1.37 + )
	* Boost Threads
	* Boost Datetime
	* Boost Signals 2
    * GLFW ( 2.6 )

Boost and GLFW are usually available via the package
manager on many Linux distributions. On Windows
you can download GLFW from their website at
http://glfw.sourceforge.net/ and I highly suggest you
use the Boost Installer from Boost Pro Consulting.

		    = Microsoft Windows (MSVC) =
		
    1) Ensure that you've built Boost and GLFW.
    2) Using the command prompt, navigate to the 
	directory where you extracted PhoenixCore.
    3) Make a new directory named 'Build' and navigate
	to it.
    4) Issue the command 'cmake ..', you will also have
	to provide CMake with the generator desired
	( Usually -G"Visual Studio 9 2008") and the paths
	for GLFW and BOOST ( -DGLFW_PATH="..." and
	-DBOOST_ROOT="..." ).
    5) Once you've gotten CMake to succesfully generate
	project files, there should be a solution named 
	"PhoenixCore" in the Build directory.
    6) Building this solution should build the core
	library and all tests and examples.
    7) If you run into linking errors when building
	'Release' or 'Debug' but not both, check the
	link libraries; CMake doesn't always do a
	great job of detecting the correct versions.
	
				    = Linux =
				    
    1) Ensure that you've installed the dev packages for
	Boost and GLFW.
    2) Linux is usually a lot better about finding the GLFW
	and Boost libraries. You should be able to just make 
	a Build directory and issue "cmake .." ( atleast on
	ubuntu )
    3) Once CMake has made your makefiles, you should
	be able to execute "make" and it will build the library,
	tests, and examples.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				Getting Help

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    You can always try the google group for phoenixcore at
    -> http://groups.google.com/group/phoenixgl
    
    You are also welcome to email me at
    -> jjramone13@gmail.com
    
    And you can usually find me lurking around on FreeNode
    IRC with the handle Josie. I am usually in #irrlicht,
    #python, #cakephp, or #opengl.