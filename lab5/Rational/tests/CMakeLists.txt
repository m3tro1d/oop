add_executable(RationalTest
               Rational.test.cpp)
target_link_libraries(RationalTest PUBLIC Rational catch2)
add_test(NAME RationalTest COMMAND CarTest)
