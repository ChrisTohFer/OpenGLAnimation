add_library(assimp SHARED IMPORTED GLOBAL)

set(lib_folder "${CMAKE_CURRENT_SOURCE_DIRECTORY}lib/")
cmake_path(ABSOLUTE_PATH lib_folder)

set_property(TARGET assimp PROPERTY IMPORTED_IMPLIB "${lib_folder}release/assimp-vc142-mt.lib")
set_property(TARGET assimp PROPERTY IMPORTED_IMPLIB_DEBUG "${lib_folder}debug/assimp-vc142-mtd.lib")
set_property(TARGET assimp PROPERTY IMPORTED_LOCATION "${lib_folder}release/assimp-vc142-mt.dll")
set_property(TARGET assimp PROPERTY IMPORTED_LOCATION_DEBUG "${lib_folder}debug/assimp-vc142-mtd.dll")

target_include_directories(assimp
    INTERFACE "include"
    )