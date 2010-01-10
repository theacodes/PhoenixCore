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
add_executable( 01HelloWorld 01\ helloworld.cpp )
target_link_libraries( 01HelloWorld PhoenixCore ${LIBRARIES} )

# Shapes
add_executable( 02Shapes 02\ shapes.cpp )
target_link_libraries(  02Shapes PhoenixCore ${LIBRARIES} )

# Textures
add_executable( 03Textures 03\ textures.cpp )
target_link_libraries( 03Textures PhoenixCore ${LIBRARIES} )

# Box2d
if( BOX2D )
    add_executable( Box2d box2d.cpp )
    target_link_libraries( Box2d PhoenixCore ${LIBRARIES} ${BOX2D_LIBRARY} )
endif()