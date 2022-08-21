cmake_minimum_required(VERSION 3.8)

add_subdirectory(libs/wxWidgets)

project(Discordus CXX)
file(GLOB_RECURSE ${PROJECT_NAME}Files ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)

if (WIN32)
        add_executable(${PROJECT_NAME} WIN32 ${${PROJECT_NAME}Files})
else(WIN32)
        add_executable(${PROJECT_NAME} ${${PROJECT_NAME}Files})
endif(WIN32)


target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base)

if (!WIN32)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        add_custom_target(copy-compile-commands ALL
                ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ${CMAKE_CURRENT_LIST_DIR}
                )
endif(!WIN32)
