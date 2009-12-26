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
add_executable( HelloWorld helloworld.cpp )
target_link_libraries( HelloWorld PhoenixCore ${LIBRARIES} )

# Box2d
if( BOX2D )
    add_executable( Box2d box2d.cpp )
    target_link_libraries( Box2d PhoenixCore ${LIBRARIES} ${BOX2D_LIBRARY} )
endif()