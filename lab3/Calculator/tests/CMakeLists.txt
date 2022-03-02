add_executable(CalculatorTest
               Calculator.test.cpp)
target_link_libraries(CalculatorTest PUBLIC catch2)
add_test(NAME CalculatorTest COMMAND CalculatorTest)
