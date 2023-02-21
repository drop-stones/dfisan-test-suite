option(USE_SMATUS "Compile with smatus" OFF)
set(SMATUS "/home/shizuku/Development/movec/bin/movec")

if (DFISAN)
  add_compile_options(-mllvm -protect-all)
endif()

add_subdirectory(field)
add_subdirectory(other_object)
