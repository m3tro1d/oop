add_executable(fill fill.cpp)
add_custom_command(TARGET fill
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:fill> ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(TARGET fill
                   POST_BUILD
                   COMMAND cmd /c "cd ${CMAKE_CURRENT_SOURCE_DIR} && test.cmd $<TARGET_FILE:fill>")
