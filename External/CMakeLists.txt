option(DFISAN "Compile with dfisan" OFF)
option(UNALIGNED_REGION_ONLY "All protection targets is replaced in unaligned region" OFF)

if(DFISAN)
  message(STATUS "Compile with dfisan")
  if (UNALIGNED_REGION_ONLY)
    message(STATUS "compile option: -mllvm -unaligned-region-only")
  endif()
endif()

add_subdirectory(SPEC)