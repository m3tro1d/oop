add_executable(crypt crypt.cpp)
add_custom_command(TARGET crypt
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:crypt> ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET crypt
                   POST_BUILD
                   COMMAND cmd /c "cd ${CMAKE_CURRENT_SOURCE_DIR} && test.cmd $<TARGET_FILE:crypt>")
