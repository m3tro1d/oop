add_executable(replace replace.cpp)
add_custom_command(TARGET replace
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:replace> ${CMAKE_CURRENT_SOURCE_DIR})
