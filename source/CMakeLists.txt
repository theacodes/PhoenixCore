cmake_minimum_required (VERSION 2.6)
project ( PhoenixCore)


# Build oenix Core
add_library( PhoenixCore STATIC
	config.h
	2dGraphicsFactory.h
	2dGraphicsFactory.cpp
	AbstractGarbageCollector.h
	AbstractGeometryFactory.h
	BatchGeometry.h
	BatchRenderer.cpp
	BatchRenderer.h
	BitmapFont.cpp
	BitmapFont.h
	Color.h
	DebugConsole.cpp
	DebugConsole.h
	Droppable.h
	EventReceiver.cpp
	EventReceiver.h
	Font.h
	Functions.h
	GroupState.h
	TrackingInvariant.h
	Keys.h
	Phoenix.h
	Polygon.cpp
	Polygon.h
	Rectangle.cpp
	Rectangle.h
	RenderSystem.cpp
	RenderSystem.h
	RenderTexture.h
	Resource.h
	ResourceManager.cpp
	ResourceManager.h
	RotationMatrix.h
	Texture.h
	Texture.cpp
	Timer.h
	Vector2d.h
	Vertex.h
	View.h
	WindowEvent.h
	WindowManager.h
	WindowManager.cpp
	GLFWWindowManager.h
	GLFWWindowManager.cpp
	PrecompiledFont.h
	soil/image_DXT.h
	soil/image_DXT.c
	soil/image_helper.h
	soil/image_helper.c
	soil/SOIL.h
	soil/SOIL.c
	soil/stbi_DDS_aug.h
	soil/stbi_DDS_aug_c.h
	soil/stb_image_aug.h
	soil/stb_image_aug.c
	)
	
	