cmake_minimum_required(VERSION 3.20)

project(OpenGLAnimation)
file(GLOB_RECURSE source_list source/*.cpp source/*.h)
add_executable(OpenGLAnimation ${source_list})

foreach(source IN LISTS source_list)
#from source to relative path source_path
	cmake_path(RELATIVE_PATH source OUTPUT_VARIABLE source_path)
	cmake_path(REMOVE_FILENAME source_path)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()