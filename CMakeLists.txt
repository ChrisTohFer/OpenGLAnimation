cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Thirdparty libs
add_subdirectory("third_party/glfw")
add_subdirectory("third_party/glad")

project(OpenGLAnimation)
file(GLOB_RECURSE source_list source/*.*)
add_executable(OpenGLAnimation ${source_list})

target_link_libraries(OpenGLAnimation PUBLIC GLFW)
target_link_libraries(OpenGLAnimation PUBLIC GLAD)

foreach(source IN LISTS source_list)
#from source to relative path source_path
	cmake_path(RELATIVE_PATH source OUTPUT_VARIABLE source_path)
	cmake_path(REMOVE_FILENAME source_path)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()