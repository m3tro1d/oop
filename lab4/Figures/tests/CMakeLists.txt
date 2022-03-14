add_executable(FiguresTest
               Figures.test.cpp)
target_link_libraries(FiguresTest PUBLIC catch2)
add_test(NAME FiguresTest COMMAND CarTest)
