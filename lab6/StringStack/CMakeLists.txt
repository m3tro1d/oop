add_library(StringStack STATIC
            CStringStack.h
            CStringStack.cpp
            CStringStackUnderflowError.h
            CStringStackUnderflowError.cpp)

add_subdirectory(tests)
