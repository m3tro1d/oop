add_executable(HttpUrl
               CHttpUrl.h
               CHttpUrl.cpp
               CUrlParsingError.h
               CUrlParsingError.cpp
               main.cpp)

add_subdirectory(tests)
