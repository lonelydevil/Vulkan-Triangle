cmake_minimum_required(VERSION 3.15)

project(Vulkan\ Triangle)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(vulkan-triangle
	Sources/vk_triangle.c
	Sources/vk_instance.c
	Sources/vk_physical_device.c
	Sources/vk_device.c
	Sources/vk_queue.c
	Sources/vk_surface.c
	Sources/vk_image.c
	Sources/vk_frame.c
	Sources/vk_shader.c
	Sources/vk_pipeline.c
	Sources/vk_command.c
	Sources/vk_synchronization.c
	Sources/vk_present.c)

if(UNIX AND NOT APPLE)
	#[[
		Build for linux, basically you don't need to do anything,
		but if you ONLY BUILD glfw or vulkanSDK
		without install it into '/usr' directory, you should

			1. add extra 'target_include_directories' option
			2. modify the 'target_link_libraries' option

		based on your build directories
	]]
	target_link_libraries(vulkan-triangle
		/usr/lib/libvulkan.so
		/usr/lib/libglfw.so
		/usr/lib/libm.so)
elseif(WIN32)
	#[[
		Build for windows, mingw-w64 C compiler is recommended.
		Visual C++ doesn't fully support C99, use it with cautious.

		Before build, you should

			1. modify the 'target_include_directories' option
				if it's different from the path provided below.

			2. modify the 'target_link_libraries' option
				if it's different from the library file provided below.

		based on your install directories
	]]
	target_include_directories(vulkan-triangle PRIVATE
		C:/VulkanSDK/1.2.176.1/Include
		C:/glfw/include)

	target_link_libraries(vulkan-triangle
		C:/VulkanSDK/1.2.176.1/Lib/vulkan-1.lib
		C:/glfw/lib-mingw-w64/libglfw3dll.a)
		# if you're using Visual C++ 2019, add '#' to the line above
		# and delete '#' from the line below
		#C:/glfw/lib-vc2019/libglfw3dll.a)

	target_link_options(vulkan-triangle PRIVATE
		-mwindows)
endif()

add_custom_target(Shaders
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Shaders)
	# if you're using Visual C++ 2019, add '#' to the line above
	# and delete '#' from the line below
	#COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Debug/Shaders)

add_custom_target(triangle_vertex.spv
	COMMAND glslangValidator --quiet -V ${CMAKE_SOURCE_DIR}/Shaders/triangle.vert -o ${CMAKE_BINARY_DIR}/Shaders/triangle_vertex.spv)
	# if you're using Visual C++ 2019, add '#' to the line above
	# and delete '#' from the line below
	#COMMAND glslangValidator --quiet -V ${CMAKE_SOURCE_DIR}/Shaders/triangle.vert -o ${CMAKE_BINARY_DIR}/Debug/Shaders/triangle_vertex.spv)

add_custom_target(triangle_fragment.spv
	COMMAND glslangValidator --quiet -V ${CMAKE_SOURCE_DIR}/Shaders/triangle.frag -o ${CMAKE_BINARY_DIR}/Shaders/triangle_fragment.spv)
	# if you're using Visual C++ 2019, add '#' to the line above
	# and delete '#' from the line below
	#COMMAND glslangValidator --quiet -V ${CMAKE_SOURCE_DIR}/Shaders/triangle.frag -o ${CMAKE_BINARY_DIR}/Debug/Shaders/triangle_fragment.spv)

add_dependencies(vulkan-triangle
	Shaders
	triangle_vertex.spv
	triangle_fragment.spv)

if(WIN32)
	#[[
		Windows need glfw3.dll to run this program,
		modify the path to glfw3.dll to your own path
	]]
	add_custom_target(glfw3.dll
		COMMAND ${CMAKE_COMMAND} -E copy C:/glfw/lib-mingw-w64/glfw3.dll ${CMAKE_BINARY_DIR}/)
		# if you're using Visual C++ 2019, add '#' to the line above
		# and delete '#' from the line below
		#COMMAND ${CMAKE_COMMAND} -E copy C:/glfw/lib-vc2019/glfw3.dll ${CMAKE_BINARY_DIR}/Debug/)

	add_dependencies(vulkan-triangle
		glfw3.dll)
endif()
