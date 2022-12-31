
file(GLOB SOURCES
  *.c
)

foreach(SOURCE ${SOURCES})
  get_filename_component(TEST_NAME ${SOURCE} NAME_WE)
  add_executable(${TEST_NAME} ${SOURCE})
  if(DFISAN)
    target_compile_definitions(${TEST_NAME} PRIVATE SAFE_ALLOC DFISAN)
  endif()
  add_test(
    NAME run_${TEST_NAME}
    COMMAND ${TEST_NAME}
    DEPENDS ${TEST_NAME} ${SOURCE}
  )
endforeach()
