add_executable(StringStackTest
               ../CStringStack.h
               ../CStringStack.cpp
               ../CStringStackUnderflowError.h
               ../CStringStackUnderflowError.cpp
               StringStack.test.cpp)
target_link_libraries(StringStackTest PUBLIC StringStack catch2)
add_test(NAME StringStackTest COMMAND StringStackTest)
