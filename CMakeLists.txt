cmake_minimum_required(VERSION 3.0.0)
project(tar4 VERSION 0.1.0)

include(CTest)
enable_testing()
add_executable(server Server.cpp CLI.cpp Command.cpp Command.h Command1.cpp Command2.cpp Command3.cpp
Command4.cpp Command5 Distance.cpp Input.cpp Knn.cpp SocketIO.cpp)
add_executable(client Client.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
