cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(libs/wxWidgets)

project(Discordus CXX)
file(GLOB_RECURSE ${PROJECT_NAME}Files ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}Files})

target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base)

add_custom_target(copy-compile-commands ALL
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
        )
