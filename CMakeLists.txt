# Setting minimum required for cmake versions
cmake_minimum_required(VERSION 3.10.0)

# Setting minimal c++ version for work
set(CMAKE_CXX_STANDARD 14)

project(Chess)  # Main project

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Static linking standart C++ libraries
set(CMAKE_CXX_STANDARD_LIBRARIES "-static") # !!!!!! not working with libzip on linux
set(CMAKE_EXE_LINKER_FLAGS "-static")       # !!!!!! not working with libzip on linux
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")

# Hidding console
set(CMAKE_CXX_FLAGS "-mwindows -static")

# Including external libraries
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Finding place of external libraries
# Including SDL-family
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_net CONFIG REQUIRED)

# Including libzip
find_package(libzip CONFIG REQUIRED)

# Including external included directories
include_directories(${SDL2_INCLUDE_DIRS})

# Including linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_net::SDL2_net)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${libzip_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE libzip::zip)
