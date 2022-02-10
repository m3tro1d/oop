add_executable(fill fill.cpp)
add_custom_command(TARGET fill
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:fill> ${CMAKE_CURRENT_SOURCE_DIR})
