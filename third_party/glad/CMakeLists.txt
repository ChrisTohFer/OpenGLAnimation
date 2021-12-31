file(GLOB_RECURSE glad_source *.*)
add_library(GLAD STATIC ${glad_source})
set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(GLAD PUBLIC "include")