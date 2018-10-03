include_directories(../include)

macro(CREATE_TEST NAME)
add_executable("${NAME}-test" "${NAME}.cxx")
target_link_libraries("${NAME}-test" gtest_main)
add_test(NAME "${NAME}-test" COMMAND "${NAME}-test")
endmacro()

CREATE_TEST(imemstream)
CREATE_TEST(omemstream)
#add_executable(imemstream-test imemstream.cxx)
#target_link_libraries(imemstream-test gtest_main)
#add_test(NAME imemstream_tests COMMAND imemstream-test)