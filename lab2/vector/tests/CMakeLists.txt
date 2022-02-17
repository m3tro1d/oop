add_executable(vectortest
               ../vector_utils.h
               ../vector_utils.cpp
               vectortest.cpp)
target_link_libraries(vectortest PUBLIC catch2)
add_test(NAME vectortest COMMAND vectortest)
