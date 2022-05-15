add_executable(MyArrayTest
               ../CMyArray.hpp
               MyArray.test.cpp)
target_link_libraries(MyArrayTest PUBLIC catch2)
add_test(NAME MyArrayTest COMMAND MyArrayTest)
