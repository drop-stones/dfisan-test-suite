option(DFISAN "Compile with dfisan" OFF)
option(UNALIGNED_REGION_ONLY "All protection targets is replaced in unaligned region" OFF)
option(PROTECT_ALL "Protect all data" OFF)
option(NO_ERROR_REPORT "No error report" OFF)
option(SMATUS "Compile with smatus" OFF)

if(DFISAN)
  message(STATUS "Compile with dfisan")
  if (UNALIGNED_REGION_ONLY)
    message(STATUS "compile option: -mllvm -unaligned-region-only")
  endif()
  if (PROTECT_ALL)
    message(STATUS "compile option: -mllvm -protect-all -mllvm -no-check-unsafe-access")
  endif()
  if (NO_ERROR_REPORT)
    message(STATUS "compile option: -mllvm -no-error-report")
  endif()
elseif(SMATUS)
  message(STATUS "Compile with smatus")
endif()

add_subdirectory(SPEC)