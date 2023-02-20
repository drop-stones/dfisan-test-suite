option(DFISAN "Compile with dfisan" OFF)

enable_testing()

add_subdirectory(memory)
add_subdirectory(datarace)
add_subdirectory(cbench)
