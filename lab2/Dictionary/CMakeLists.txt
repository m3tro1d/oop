add_executable(Dictionary
               StringLib.h
               StringLib.cpp
               DictionaryLib.h
               DictionaryLib.cpp
               DictionaryFileLib.h
               DictionaryFileLib.cpp
               DictionaryConsoleLib.h
               DictionaryConsoleLib.cpp
               main.cpp)

add_subdirectory(tests)
