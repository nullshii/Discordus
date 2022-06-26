cmake_minimum_required(VERSION 3.8)

# Submodules | add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/discord-rpc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Simpleini)

# Include submodules | include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/L_I_B_N_A_M_E/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/discord-rpc/include)
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/Simpleini/)

# Link submodules | link_libraries(L_I_B_N_A_M_E)
link_libraries(discord-rpc)
link_libraries(SimpleIni)

# Add local libraries
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DiscordRPCpp)

# Include local libraries
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/DiscordRPCpp/include)

# Link local libraries
link_libraries(DiscordRPCpp)

# Project
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Discordus)