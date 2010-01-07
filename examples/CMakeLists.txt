############################################
#
# PhoenixCore Examples CMake
#
############################################
cmake_minimum_required( VERSION 2.6 )

project( PhoenixCore )

############################################
# Examples
############################################

# Hello, World!
add_executable( HelloWorld 01\ helloworld.cpp )
target_link_libraries( HelloWorld PhoenixCore ${LIBRARIES} )

# Shapes
add_executable( Shapes 02\ shapes.cpp )
target_link_libraries( Shapes PhoenixCore ${LIBRARIES} )


# Box2d
if( BOX2D )
    add_executable( Box2d box2d.cpp )
    target_link_libraries( Box2d PhoenixCore ${LIBRARIES} ${BOX2D_LIBRARY} )
endif()