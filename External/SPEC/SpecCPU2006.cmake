include(External)
llvm_externals_find(TEST_SUITE_SPEC2006_ROOT "speccpu2006" "SPEC CPU2006")
if(TEST_SUITE_SPEC2006_ROOT)
  # SPEC supports three "run types": ref, train and test
  if(NOT TEST_SUITE_RUN_TYPE STREQUAL "train" AND
     NOT TEST_SUITE_RUN_TYPE STREQUAL "test" AND
     NOT TEST_SUITE_RUN_TYPE STREQUAL "ref")
    message(FATAL_ERROR
            "TEST_SUITE_RUN_TYPE must be 'train', 'test' or 'ref' for SPEC")
  endif()

  file(READ ${TEST_SUITE_SPEC2006_ROOT}/version.txt VERSION)
  if (VERSION VERSION_LESS 1.2)
    message(WARNING "
    Expected SPEC2006 version 1.2 or newer, found ${VERSION}
")
  endif()

  list(APPEND CPPFLAGS -DSPEC_CPU)

  if(TARGET_OS STREQUAL "Darwin")
    list(APPEND CPPFLAGS -DSPEC_CPU_MACOSX)
  elseif(TARGET_OS STREQUAL "Linux")
    list(APPEND CPPFLAGS -DSPEC_CPU_LINUX)
  endif()

  if(ARCH STREQUAL "x86")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      list(APPEND CPPFLAGS -DSPEC_CPU_X64)
    else()
      list(APPEND CPPFLAGS -DSPEC_CPU_IA32)
    endif()
  endif()

  include(TestBigEndian)
  test_big_endian(IS_BIGENDIAN)
  if(IS_BIGENDIAN)
    list(APPEND CPPFLAGS -DSPEC_CPU_BIGENDIAN -DSPEC_CPU_BIG_ENDIAN)
  else()
    list(APPEND CPPFLAGS -DSPEC_CPU_LITTLEENDIAN -DSPEC_CPU_LITTLE_ENDIAN)
  endif()

  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND CPPFLAGS -DSPEC_CPU_LP64)
  endif()

  if(TARGET_OS STREQUAL "Darwin")
    # Work around built in -Werror=implicit-function-declaration default on iOS
    list(APPEND CPPFLAGS -Wno-implicit-function-declaration)
  endif()

  macro(cpu2006_subdir BENCHMARK)
    set(BENCHMARK_DIR ${TEST_SUITE_SPEC2006_ROOT}/benchspec/CPU2006/${BENCHMARK})
    file(GLOB Source ${BENCHMARK_DIR}/src/*.c ${BENCHMARK_DIR}/src/*.cpp ${BENCHMARK_DIR}/src/*.cc)
    add_subdirectory(${BENCHMARK})
  endmacro()

  function(llvm_test_data_spec target)
    llvm_test_data(${target} SOURCE_DIR ${BENCHMARK_DIR} ${ARGN})
  endfunction()

  function(llvm_test_data_spec_default target)
    llvm_test_data_spec(${target} data)
  endfunction()

  # Create a new executable build target.
  function(dfisan_test_executable target)
    message("DFISan Target: ${target}")
    llvm_test_executable(${target} ${ARGN})

    set(target-bc "${target}.bc")
    set(target-ll "${target}.ll")
    set(target-obj "${target}.o")
    set(dfi-target "dfi-${target}")
    set(options "-mllvm" "--debug-only=def-use-log") # Output def-use to sqlite3
    set(options ${options} "-mllvm" "-stats" "-mllvm" "-stats-json" "-mllvm" "-info-output-file=${target}.json") # Output statistics to json file
    if (UNALIGNED_REGION_ONLY)
      set(options ${options} "-mllvm" "-unaligned-region-only")
    endif()
    message(STATUS "options: ${options}")
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND extract-bc ${target}
      COMMAND cp ${target} "original-${target}"

      ## Create executable directly
      COMMAND $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER} -fsanitize=dfi ${options} ${target-bc} -o ${target}
      COMMAND echo "Create ${dfi-target}"

      ## Create llvm-ir and executable
      # COMMAND $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER} -O0 -fsanitize=dfi -mllvm --debug-only=usedef-log ${target-bc} -S -emit-llvm -o ${target-ll}
      # COMMAND $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER} -O0 -fsanitize=dfi ${target-ll} -o ${dfi-target}

      # COMMAND $ENV{LLVM_COMPILER_PATH}/llc -filetype=obj ${target-ll} -o ${target-obj}
      # COMMAND $ENV{LLVM_COMPILER_PATH}/$ENV{LLVM_COMPILER} -O0 -fsanitize=dfi ${target-obj} -o ${dfi-target}
      # COMMAND cp ${dfi-target} ${target}
      # COMMAND mv ${target-ll}.sqlite3 ${target}.sqlite3
    )
  endfunction()
endif()
