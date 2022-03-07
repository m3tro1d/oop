add_executable(CarTest
               ../CCar.h
               ../CCar.cpp
               ../CCarControl.h
               ../CCarControl.cpp
               Car.test.cpp)
target_link_libraries(CarTest PUBLIC catch2)
add_test(NAME CarTest COMMAND CarTest)
