if (DFISAN)
  add_compile_options(-mllvm -protect-all)
endif()

add_subdirectory(indirect_call)
add_subdirectory(indirect_jump)
add_subdirectory(return_address)
