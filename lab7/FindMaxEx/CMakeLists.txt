add_executable(FindMaxEx
               FindMaxEx.hpp
               main.cpp)
add_custom_command(TARGET FindMaxEx
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:FindMaxEx> ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET FindMaxEx
                   POST_BUILD
                   COMMAND cmd /c "cd ${CMAKE_CURRENT_SOURCE_DIR} && test.cmd $<TARGET_FILE:FindMaxEx>")

add_subdirectory(tests)
