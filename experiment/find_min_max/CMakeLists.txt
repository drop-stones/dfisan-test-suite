
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/find_min_max.c)
set(DFISAN $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER})
set(DATASHIELD "")
set(SMATUS $ENV{LLVM_COMPILER_PATH}/../../../movec/bin/movec)
set(CFLAGS "-O0" "-lpthread")

add_custom_target(find_min_max_target ALL
  DEPENDS
    ${SOURCE}
    find_min_max
    baseline_find_min_max
    dfisan_find_min_max
    dfisan_no_check_unsafe_access_find_min_max
    tsan_find_min_max
    run_find_min_max.py
)

add_custom_command(
  OUTPUT find_min_max
  COMMAND clang ${SOURCE} ${CFLAGS} -o find_min_max
)
add_custom_command(
  OUTPUT baseline_find_min_max
  COMMAND ${DFISAN} -fsanitize=dfi ${SOURCE} ${CFLAGS} -o baseline_find_min_max
)
add_custom_command(
  OUTPUT dfisan_find_min_max
  COMMAND ${DFISAN} -fsanitize=dfi -DSAFE_ALLOC ${SOURCE} ${CFLAGS} -o dfisan_find_min_max
)
add_custom_command(
  OUTPUT dfisan_no_check_unsafe_access_find_min_max
  COMMAND ${DFISAN} -fsanitize=dfi -DSAFE_ALLOC -mllvm -no-check-unsafe-access ${SOURCE} ${CFLAGS} -o dfisan_no_check_unsafe_access_find_min_max
)
add_custom_command(
  OUTPUT tsan_find_min_max
  COMMAND clang -fsanitize=thread ${SOURCE} ${CFLAGS} -o tsan_find_min_max
)
add_custom_command(
  OUTPUT run_find_min_max.py
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/run_find_min_max.py ${CMAKE_CURRENT_BINARY_DIR}/run_find_min_max.py
)
