include_directories(../include)

macro(CREATE_TEST NAME)
add_executable("${NAME}-test" "${NAME}.cxx")
target_link_libraries("${NAME}-test" gtest_main)
add_test(NAME "${NAME}-test" COMMAND "${NAME}-test")
endmacro()

set(LINK_FLAGS -lgcov -fprofile-arcs)
SET(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")

CREATE_TEST(imemstream)
CREATE_TEST(omemstream)
CREATE_TEST(binary_writer)
CREATE_TEST(binary_reader)
CREATE_TEST(file)
CREATE_TEST(args)
CREATE_TEST(event)
CREATE_TEST(fs)
CREATE_TEST(path)
CREATE_TEST(algorithm)