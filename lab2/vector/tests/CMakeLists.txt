add_executable(vectortest vectortest.cpp)
target_link_libraries(vectortest PRIVATE vectorlib catch2)
add_test(NAME vectortest COMMAND vectortest)
