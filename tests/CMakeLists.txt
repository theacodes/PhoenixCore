############################################
#
# oenixCore Tests CMake
#
############################################
cmake_minimum_required( VERSION 2.6 )

project( PhoenixCore )

############################################
# Source files for each test.
############################################
set( CORETEST_SOURCES
	main.cpp
	Demo.h
	TextureTest.h
	PolygonTest.h
	ResourceTest.h
	ChangeTest.h
	ViewTest.h
	EventTest.h
	VectorTest.h
	EventTest.h
	FontTest.h
)

############################################
# Tests
############################################

#Demo Test
add_executable( PhoenixCoreDemo ${CORETEST_SOURCES} )
target_link_libraries( PhoenixCoreDemo PhoenixCore ${LIBRARIES} )
set_property(
	TARGET PhoenixCoreDemo
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_DEMO_
)

#Font Test
add_executable( FontTest ${CORETEST_SOURCES} )
target_link_libraries( FontTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET FontTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_FONT_
)

#Texture Test
add_executable( TextureTest ${CORETEST_SOURCES} )
target_link_libraries( TextureTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET TextureTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_TEXTURE_
)

#Event Test
add_executable( EventTest ${CORETEST_SOURCES} )
target_link_libraries( EventTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET EventTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_EVENT_
)

#Polygon Test
add_executable( PolygonTest ${CORETEST_SOURCES} )
target_link_libraries( PolygonTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET PolygonTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_POLYGON_
)

#Vector Test
add_executable( VectorTest ${CORETEST_SOURCES} )
target_link_libraries( VectorTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET VectorTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_VECTOR_
)

#Resource Test
add_executable( ResourceTest ${CORETEST_SOURCES} )
target_link_libraries( ResourceTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET ResourceTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_RESOURCE_ ENABLECONSOLE
)

#Change Test
add_executable( ChangeTest ${CORETEST_SOURCES} )
target_link_libraries( ChangeTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET ChangeTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_CHANGE_ ENABLECONSOLE
)

#View Test
add_executable( ViewTest ${CORETEST_SOURCES} )
target_link_libraries( ViewTest PhoenixCore ${LIBRARIES} )
set_property(
	TARGET ViewTest
	APPEND PROPERTY COMPILE_DEFINITIONS _TESTS_VIEW_
)

######################################
# Windows stuff
######################################
#WINDOWS (MSVC)
if(WIN32)
	if(MSVC)
	    set_target_properties( PhoenixCoreDemo FontTest TextureTest EventTest PolygonTest VectorTest ViewTest
	        PROPERTIES WIN32_EXECUTABLE true )
	endif()
endif()