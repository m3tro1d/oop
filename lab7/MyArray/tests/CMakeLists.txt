add_executable(MyArrayTest
               MyArray.test.cpp)
target_link_libraries(MyArrayTest PUBLIC catch2)
add_test(NAME MyArrayTest COMMAND MyArrayTest)
