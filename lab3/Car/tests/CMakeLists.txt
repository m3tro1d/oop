add_executable(CCarTest
               ../CCar.h
               ../CCar.cpp
               CCar.test.cpp)
target_link_libraries(CCarTest PUBLIC catch2)
add_test(NAME CCarTest COMMAND CCarTest)
