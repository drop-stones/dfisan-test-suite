file(GLOB SOURCES
  *.c
)

foreach(SOURCE ${SOURCES})
  get_filename_component(TEST_NAME ${SOURCE} NAME_WE)
  add_executable(${TEST_NAME} ${SOURCE})
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
