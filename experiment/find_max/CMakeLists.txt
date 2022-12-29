
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/find_max.c)
set(DFISAN $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER})
set(DATASHIELD "")
set(CFLAGS "-O0")

add_custom_target(find_max_target ALL
  DEPENDS
    ${SOURCE}
    find_max
    baseline_find_max
    dfisan_find_max
    dfisan_no_check_unsafe_access_find_max
    asan_find_max
    # datashield_find_max
    run_find_max.py
)

add_custom_command(
  OUTPUT find_max
  COMMAND clang ${SOURCE} ${CFLAGS} -o find_max
)
add_custom_command(
  OUTPUT baseline_find_max
  COMMAND ${DFISAN} -fsanitize=dfi ${SOURCE} ${CFLAGS} -o baseline_find_max
)
add_custom_command(
  OUTPUT dfisan_find_max
  COMMAND ${DFISAN} -fsanitize=dfi -DSAFE_ALLOC ${SOURCE} ${CFLAGS} -o dfisan_find_max
)
add_custom_command(
  OUTPUT dfisan_no_check_unsafe_access_find_max
  COMMAND ${DFISAN} -fsanitize=dfi -DSAFE_ALLOC -mllvm -no-check-unsafe-access ${SOURCE} ${CFLAGS} -o dfisan_no_check_unsafe_access_find_max
)
add_custom_command(
  OUTPUT asan_find_max
  COMMAND clang -fsanitize=address ${SOURCE} ${CFLAGS} -o asan_find_max
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
