cmake_minimum_required(VERSION 3.8)

project(Discordus CXX)
file(GLOB_RECURSE ${PROJECT_NAME}Files ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}Files})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)