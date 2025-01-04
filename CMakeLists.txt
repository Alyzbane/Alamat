cmake_minimum_required(VERSION 3.10)
project(alamat)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(alamat
    alamat.cpp
    archive.cpp
    prompt.cpp
    menu.cpp
    login.cpp
    entry.cpp
    user.cpp
    screen.cpp
)

# Define platform-specific macros
if(WIN32)
    target_compile_definitions(alamat PRIVATE WIN32)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(alamat PRIVATE __LINUX__)
endif()

# Link static libraries
target_link_options(alamat PRIVATE -static-libgcc -static-libstdc++)