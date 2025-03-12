cmake_minimum_required(VERSION 3.16)

project(QueueClients LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QueueClients main.cpp)

include(GNUInstallDirs)
install(TARGETS QueueClients
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
