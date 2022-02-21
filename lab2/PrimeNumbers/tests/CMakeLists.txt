add_executable(PrimeNumbersGeneratorTest
               ../PrimeNumbersGenerator.h
               ../PrimeNumbersGenerator.cpp
               PrimeNumbersGeneratorTest.cpp)
target_link_libraries(PrimeNumbersGeneratorTest PUBLIC catch2)
add_test(NAME PrimeNumbersGeneratorTest COMMAND PrimeNumbersGeneratorTest)
