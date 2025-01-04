cmake_minimum_required(VERSION 3.10)
project(alamat)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

add_executable(alamat
    src/alamat.cpp
    src/archive.cpp
    src/prompt.cpp
    src/menu.cpp
    src/login.cpp
    src/entry.cpp
    src/user.cpp
    src/screen.cpp
)

# Define platform-specific macros
if(WIN32)
    target_compile_definitions(alamat PRIVATE WIN32)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(alamat PRIVATE __LINUX__)
endif()

target_link_options(alamat PRIVATE -static-libgcc -static-libstdc++)
