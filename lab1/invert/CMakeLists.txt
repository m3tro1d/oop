add_executable(invert invert.cpp)
add_custom_command(TARGET invert
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:invert> ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET invert
                   POST_BUILD
                   COMMAND cmd /c "cd ${CMAKE_CURRENT_SOURCE_DIR} && test.cmd $<TARGET_FILE:invert>")
