cmake_minimum_required(VERSION 2.8.1)
project(TinyThread++)

# create the lib
add_library(TinyThread++ STATIC "source/fast_mutex.h" "source/tinythread.h" "source/tinythread.cpp")
include_directories(source)

# build the test runner
#add_executable(tt_TestFractal "test/fractal.cpp")
#add_executable(tt_TestHello "test/hello.cpp")
#add_executable(tt_Test "test/test.cpp")

# TODO : detect if this project is added from another project, or if it is the main solution ( to enable tests )
#target_link_libraries(tt_TestFractal TinyThread++)
#target_link_libraries(tt_TestHello TinyThread++)
#target_link_libraries(tt_Test TinyThread++)

# turn on testing
#enable_testing()
#add_custom_target(tt_check COMMAND ${CMAKE_CTEST_COMMAND} -V)

# add the test runner as a test
#add_test(NAME tt_Test COMMAND Test)
#add_test(NAME tt_TestHello COMMAND TestHello)
#add_test(NAME tt_TestFractal COMMAND TestFractal)
#add_dependencies(tt_check Test)
#add_dependencies(tt_check Test)
#add_dependencies(tt_check Test)
