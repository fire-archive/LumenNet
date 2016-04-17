cmake_minimum_required(VERSION 2.6)
project("Chat Telehash Example")
include_directories(${RAKNETHEADERFILES} ./) 
add_executable(ChatTelehashServer "Chat Example Server.cpp" readme.txt)
add_executable(ChatTelehashClient "Chat Example Client.cpp" readme.txt)

target_link_libraries(ChatTelehashServer ${RAKNET_COMMON_LIBS})
VSUBFOLDER(ChatTelehashServer "Samples")

target_link_libraries(ChatTelehashClient ${RAKNET_COMMON_LIBS})
VSUBFOLDER(ChatTelehashClient "Samples")






