add_executable(VectorProcessorTest
               ../VectorProcessor.h
               ../VectorProcessor.cpp
               VectorProcessorTest.cpp)
target_link_libraries(VectorProcessorTest PUBLIC catch2)
add_test(NAME VectorProcessorTest COMMAND VectorProcessorTest)
