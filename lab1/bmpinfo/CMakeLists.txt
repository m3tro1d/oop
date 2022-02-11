add_executable(bmpinfo bmpinfo.cpp)
add_custom_command(TARGET bmpinfo
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:bmpinfo> ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET bmpinfo
                   POST_BUILD
                   COMMAND cmd /c "cd ${CMAKE_CURRENT_SOURCE_DIR} && test.cmd $<TARGET_FILE:bmpinfo>")
