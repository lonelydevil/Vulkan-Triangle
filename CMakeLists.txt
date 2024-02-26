cmake_minimum_required(VERSION 3.15)

project(Vulkan\ Triangle)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(GLFW_BASE_PATH C:/src/GLFW)
set(VULKAN_BASE_PATH C:/VulkanSDK/1.2.182.0)

file(GLOB_RECURSE HEADERS_FILES
		${PROJECT_SOURCE_DIR}/headers/*.h
		${PROJECT_SOURCE_DIR}/headers/*.inl
)
file(GLOB_RECURSE SOURCES_FILES
		${PROJECT_SOURCE_DIR}/Sources/*.c
)

add_executable(vulkan-triangle ${SOURCES_FILES})

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
			${VULKAN_BASE_PATH}/Include
			${GLFW_BASE_PATH}/include)

	target_link_libraries(vulkan-triangle
		${VULKAN_BASE_PATH}/Lib/vulkan-1.lib
		${GLFW_BASE_PATH}/lib-mingw-w64/libglfw3dll.a)
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
		COMMAND ${CMAKE_COMMAND} -E copy ${GLFW_BASE_PATH}/lib-mingw-w64/glfw3.dll ${CMAKE_BINARY_DIR}/)
		# if you're using Visual C++ 2019, add '#' to the line above
		# and delete '#' from the line below
		#COMMAND ${CMAKE_COMMAND} -E copy C:/glfw/lib-vc2019/glfw3.dll ${CMAKE_BINARY_DIR}/Debug/)

	add_dependencies(vulkan-triangle
		glfw3.dll)
endif()
