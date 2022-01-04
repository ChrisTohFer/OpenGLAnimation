cmake_minimum_required(VERSION 3.20)

project(OpenGLAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Thirdparty libs
add_subdirectory("third_party/glfw")
add_subdirectory("third_party/glad")
add_subdirectory("third_party/assimp")

#Executable
file(GLOB_RECURSE source_list source/*.*)
add_executable(OpenGLAnimation ${source_list})
target_include_directories(OpenGLAnimation PUBLIC "third_party/glm")

#Linker
target_link_libraries(OpenGLAnimation PUBLIC GLFW)
target_link_libraries(OpenGLAnimation PUBLIC GLAD)
target_link_libraries(OpenGLAnimation PUBLIC assimp)

add_custom_command(TARGET OpenGLAnimation POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:OpenGLAnimation> $<TARGET_FILE_DIR:OpenGLAnimation>
  COMMAND_EXPAND_LISTS
  )

#Add visual studio filters based on folders
foreach(source IN LISTS source_list)
	cmake_path(RELATIVE_PATH source OUTPUT_VARIABLE source_path)
	cmake_path(REMOVE_FILENAME source_path)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()