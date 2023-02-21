option(USE_SMATUS "Compile with smatus" OFF)
set(SMATUS "/home/shizuku/Development/movec/bin/movec")

if (DFISAN)
  add_compile_options(-mllvm -protect-all)
endif()

add_subdirectory(field)
add_subdirectory(other_object)
add_subdirectory(support)

file(GLOB SOURCES
  *.c
)

foreach(SOURCE ${SOURCES})
  get_filename_component(TEST_NAME ${SOURCE} NAME_WE)

  if(USE_SMATUS)
    add_custom_target(${TEST_NAME}_target ALL DEPENDS ${TEST_NAME})
    add_custom_command(
      OUTPUT ${TEST_NAME} ${TEST_NAME}_tmp.c
      COMMAND ${SMATUS} --check-memsafe -c ${SOURCE} -o ${TEST_NAME}_tmp.c
      # COMMAND ${CMAKE_COMMAND} -E copy
      COMMAND cp
        ${CMAKE_CURRENT_SOURCE_DIR}/../movec/_RV_memsafe.c ${CMAKE_CURRENT_BINARY_DIR}/_RV_memsafe.c
      COMMAND cp
        ${CMAKE_CURRENT_SOURCE_DIR}/../movec/_RV_memsafe.h ${CMAKE_CURRENT_BINARY_DIR}/_RV_memsafe.h
      COMMAND clang ${TEST_NAME}_tmp.c -o ${TEST_NAME}
    )
  else()
    add_executable(${TEST_NAME} ${SOURCE})
  endif()

  add_test(
    NAME run_${TEST_NAME}
    COMMAND ${TEST_NAME}
    DEPENDS ${TEST_NAME} ${SOURCE}
  )
  set_tests_properties(run_${TEST_NAME}
    PROPERTIES
      WILL_FAIL TRUE
  )
endforeach()
