include(${CMAKE_SOURCE_DIR}/External/SPEC/SpecCPU2006.cmake)
if(TEST_SUITE_SPEC2006_ROOT)
  cpu2006_subdir(401.bzip2)
  cpu2006_subdir(445.gobmk)
  cpu2006_subdir(456.hmmer)
  cpu2006_subdir(462.libquantum)

  if(NOT SMATUS)
    cpu2006_subdir(429.mcf)     # out-of-memory
    cpu2006_subdir(458.sjeng)   # out-of-memory
    cpu2006_subdir(464.h264ref) # compile error: macro expansion
  endif()

  # Skip big projects
  # cpu2006_subdir(400.perlbench)
  # cpu2006_subdir(403.gcc)

  # Skip c++ projects
  # cpu2006_subdir(471.omnetpp)
  # cpu2006_subdir(473.astar)
  # cpu2006_subdir(483.xalancbmk)
endif()
