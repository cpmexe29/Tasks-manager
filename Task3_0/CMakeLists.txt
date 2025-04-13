cmake_minimum_required(VERSION 3.16)

project(Task3_0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Task3_0 main.cpp)

include(GNUInstallDirs)
install(TARGETS Task3_0
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
