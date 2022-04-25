add_executable(StringStack
               CStringStack.h
               CStringStack.cpp
               CStringStackUnderflowError.h
               CStringStackUnderflowError.cpp
               main.cpp)

add_subdirectory(tests)
