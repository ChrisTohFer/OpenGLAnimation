cmake_minimum_required(VERSION 3.20)

project(OpenGLAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Thirdparty libs
add_subdirectory("third_party/glfw")
add_subdirectory("third_party/glad")

#Executable
file(GLOB_RECURSE source_list source/*.*)
add_executable(OpenGLAnimation ${source_list})

#Linker
target_link_libraries(OpenGLAnimation PUBLIC GLFW)
target_link_libraries(OpenGLAnimation PUBLIC GLAD)

#Add visual studio filters based on folders
foreach(source IN LISTS source_list)
	cmake_path(RELATIVE_PATH source OUTPUT_VARIABLE source_path)
	cmake_path(REMOVE_FILENAME source_path)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()