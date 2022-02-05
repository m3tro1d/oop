add_library(vectorlib STATIC vector.cpp vector.h)
target_include_directories(vectorlib PUBLIC .)

add_executable(vector main.cpp)
target_link_libraries(vector PRIVATE vectorlib)

add_subdirectory(tests)
