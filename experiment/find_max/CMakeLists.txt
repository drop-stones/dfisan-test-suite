
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/find_max.c)
set(DFISAN $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER})
set(DATASHIELD "")

add_custom_target(find_max_target ALL
  DEPENDS
    ${SOURCE}
    find_max
    baseline_find_max
    dfisan_find_max
    asan_find_max
    # datashield_find_max
    run_find_max.py
)

add_custom_command(
  OUTPUT find_max
  COMMAND clang ${SOURCE} -o find_max
)
add_custom_command(
  OUTPUT baseline_find_max
  COMMAND ${DFISAN} -fsanitize=dfi ${SOURCE} -o baseline_find_max
)
add_custom_command(
  OUTPUT dfisan_find_max
  COMMAND ${DFISAN} -fsanitize=dfi -DSAFE_ALLOC ${SOURCE} -o dfisan_find_max
)
add_custom_command(
  OUTPUT asan_find_max
  COMMAND clang -fsanitize=address ${SOURCE} -o asan_find_max
)
# add_custom_command(
#   OUTPUT datashield_find_max
#   COMMAND ${DATASHIELD} ${SOURCE} -o datashield_find_max
# )
add_custom_command(
  OUTPUT run_find_max.py
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/run_find_max.py ${CMAKE_CURRENT_BINARY_DIR}/run_find_max.py
)
