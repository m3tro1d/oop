add_executable(FindMaxExTest
               ../FindMaxEx.hpp
               FindMaxEx.test.cpp)
target_link_libraries(FindMaxExTest PUBLIC catch2)
add_test(NAME FindMaxExTest COMMAND FindMaxExTest)
