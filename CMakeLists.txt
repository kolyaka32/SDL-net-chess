cmake_minimum_required(VERSION 3.10.0)

project(tic-tac-toe)  # Main game project

# Set source files
add_executable( ${CMAKE_PROJECT_NAME}
    # Base includes and defines
    src/include.hpp
    src/define.hpp
    src/dataTypes.hpp
    src/values.hpp

    # Function of initialasing all data
    src/init.hpp
    src/init.cpp

    # Functions of loading all in-game data
    src/dataLoader.hpp
    src/dataLoader.cpp

    # Base interface
    src/baseGUI.hpp
    src/baseGUI.cpp

    # Interface of game pausing
    src/pause.hpp
    src/pause.cpp

    # System of initialasing file loading and unloading
    src/initFile.hpp
    src/initFile.cpp

    # In game classes
    src/entity.hpp
    src/entity.cpp

    # Singleplayer game cycles
    src/gameSingle.hpp
    src/gameSingle.cpp

    # Server game cycle
    src/gameServer.hpp
    src/gameServer.cpp

    # Client game cycle
    src/gameClient.hpp
    src/gameClient.cpp

    # Main function
    src/main.cpp
    
    # Adding game icone
    src/set.rc
)

# Static linking standart C/C++ libraries
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -mwindows")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
#set(CMAKE_GENERATOR_PLATFORM -A "x64")

# Hidding console
set(DCMAKE_C_FLAGS "-mwindows")

# Setting other flags
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")

#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Including external libraries
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2_net::SDL2_net)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${libzip_LIBRARIES} libzip::zip)
