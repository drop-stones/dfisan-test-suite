
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/insertion_sort.c)
set(DFISAN $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER})
set(DATASHIELD "")

add_custom_target(insertion_sort_target ALL
  DEPENDS
    ${SOURCE}
    insertion_sort
    baseline_insertion_sort
    dfisan_insertion_sort
    asan_insertion_sort
    # datashield_insertion_sort
    run_insertion_sort.py
)

add_custom_command(
  OUTPUT insertion_sort
  COMMAND clang ${SOURCE} -o insertion_sort
)
add_custom_command(
  OUTPUT baseline_insertion_sort
  COMMAND ${DFISAN} -fsanitize=dfi ${SOURCE} -o baseline_insertion_sort
)
add_custom_command(
  OUTPUT dfisan_insertion_sort
  COMMAND ${DFISAN} -fsanitize=dfi -DSAFE_ALLOC ${SOURCE} -o dfisan_insertion_sort
)
add_custom_command(
  OUTPUT asan_insertion_sort
  COMMAND clang -fsanitize=address ${SOURCE} -o asan_insertion_sort
)
# add_custom_command(
#   OUTPUT datashield_insertion_sort
#   COMMAND ${DATASHIELD} ${SOURCE} -o datashield_insertion_sort
# )
add_custom_command(
  OUTPUT run_insertion_sort.py
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/run_insertion_sort.py ${CMAKE_CURRENT_BINARY_DIR}/run_insertion_sort.py
)
