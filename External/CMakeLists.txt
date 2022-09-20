option(DFISAN "Compile with dfisan" OFF)

if(DFISAN)
  message(STATUS "Compile with dfisan")
endif()

add_subdirectory(SPEC)