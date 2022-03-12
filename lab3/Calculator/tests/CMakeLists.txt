add_executable(CalculatorTest
               ../StringLib.h
               ../StringLib.cpp
               ../CCalculator.h
               ../CCalculator.cpp
               ../CCalculatorControl.h
               ../CCalculatorControl.cpp
               Calculator.test.cpp)
target_link_libraries(CalculatorTest PUBLIC catch2)
add_test(NAME CalculatorTest COMMAND CalculatorTest)
