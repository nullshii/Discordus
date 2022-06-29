cmake_minimum_required(VERSION 3.8)

project(Discordus CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")

if(MINGW OR WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif(MINGW OR WIN32)

set(Res_File "")
if(MINGW OR WIN32)
 set(Res_File ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/resource.rc)
endif(MINGW OR WIN32)

file(GLOB_RECURSE ${PROJECT_NAME}Files ${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}Files} ${Res_File})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
