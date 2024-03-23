cmake_minimum_required(VERSION 3.5)

project(snakeX LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(raylib)

add_executable(snakeX main.cpp
    cell.h cell.cpp
    grid.h grid.cpp)

target_link_libraries(snakeX raylib)

include(GNUInstallDirs)
install(TARGETS snakeX
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
