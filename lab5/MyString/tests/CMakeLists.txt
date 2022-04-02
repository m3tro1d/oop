add_executable(MyStringTest
               MyString.test.cpp)
target_link_libraries(MyStringTest PUBLIC MyString catch2)
add_test(NAME MyStringTest COMMAND CarTest)
