add_executable(radix radix.cpp)
add_custom_command(TARGET radix
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:radix> ${CMAKE_CURRENT_SOURCE_DIR})
