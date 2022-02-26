add_executable(ExpandTemplateLibTest
               ../ExpandTemplateLib.h
               ../ExpandTemplateLib.cpp
               ExpandTemplateLib.test.cpp)
target_link_libraries(ExpandTemplateLibTest PUBLIC catch2)
add_test(NAME ExpandTemplateLibTest COMMAND ExpandTemplateLibTest)
