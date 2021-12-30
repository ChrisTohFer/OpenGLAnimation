add_library(GLFW STATIC IMPORTED GLOBAL)

set(lib_folder "${CMAKE_CURRENT_SOURCE_DIRECTORY}lib/")
cmake_path(ABSOLUTE_PATH lib_folder)

set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION "${lib_folder}release/glfw3.lib")
set_property(TARGET GLFW PROPERTY IMPORTED_LOCATION_DEBUG "${lib_folder}debug/glfw3.lib")

target_include_directories(GLFW
    INTERFACE "include"
    )