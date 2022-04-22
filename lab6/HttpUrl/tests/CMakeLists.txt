add_executable(HttpUrlTest
               ../CHttpUrl.h
               ../CHttpUrl.cpp
               ../CUrlParsingError.h
               ../CUrlParsingError.cpp
               HttpUrl.test.cpp)
target_link_libraries(HttpUrlTest PUBLIC catch2)
add_test(NAME HttpUrlTest COMMAND HttpUrlTest)
