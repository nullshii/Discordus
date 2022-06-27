cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 23)

# Submodules | add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/discord-rpc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Simpleini)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# Include submodules | include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/discord-rpc/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/Simpleini/)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/imgui-filebrowser/)

# Link submodules | link_libraries(L_I_B_N_A_M_E)
link_libraries(discord-rpc)
link_libraries(SimpleIni)
link_libraries(glfw)
link_libraries(imgui)

# Add local libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DiscordRPCpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad)

# Include local libraries
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/DiscordRPCpp/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

# Link local libraries
link_libraries(DiscordRPCpp)
link_libraries(glad)

# Project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Discordus)