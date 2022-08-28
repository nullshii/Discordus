cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/discord-rpc)

project(Discordus CXX)
file(GLOB_RECURSE ${PROJECT_NAME}Files ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)

if (WIN32)
        add_executable(${PROJECT_NAME} WIN32 ${${PROJECT_NAME}Files})
else(WIN32)
        add_executable(${PROJECT_NAME} ${${PROJECT_NAME}Files})
endif(WIN32)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/discord-rpc/include)

target_link_libraries(${PROJECT_NAME} discord-rpc)
target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base)