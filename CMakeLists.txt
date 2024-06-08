# Setting minimum required for versions
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 14)

project(Chess)  # Main game project

# Set source files
add_executable( ${CMAKE_PROJECT_NAME}
    # Base includes and defines
    src/include.hpp
    src/define.hpp
    src/workCodes.hpp
    src/dataTypes.hpp

    # All data for programm
    # Initialasing data from user (setting file)
    src/data/initFile.hpp
    src/data/initFile.cpp

    # Main data for render
    src/data/application.hpp
    src/data/application.cpp

    # Data loading system
    src/data/dataLoader.hpp
    src/data/fileLoader.cpp
    src/data/archieveLoader.cpp

    # Base program systems
    # Textures library
    src/data/graphics.hpp
    src/data/graphics.cpp

    # Game icone loading
    src/data/icone.hpp
    src/data/icone.cpp

    # Game animations
    src/data/animations.hpp
    src/data/animations.cpp

    # Game type font
    src/data/font.hpp
    src/data/font.cpp

    # Game idle system
    src/data/idleTimer.hpp
    src/data/idleTimer.cpp

    # All audio
    # Main audio libraries
    src/data/audio/audio.hpp
    src/data/audio/audio.cpp

    # Sounds library
    src/data/audio/sounds.hpp
    src/data/audio/sounds.cpp

    # Musics library
    src/data/audio/musics.hpp
    src/data/audio/musics.cpp

    # Base graphic user interface (GUI)
    src/GUI/baseGUI.hpp
    src/GUI/template.cpp
    src/GUI/animation.cpp
    src/GUI/bar.cpp
    src/GUI/textButton.cpp
    src/GUI/imageButton.cpp
    src/GUI/slider.cpp
    src/GUI/staticText.cpp
    src/GUI/typeBox.cpp
    src/GUI/roundedBackplate.cpp

    # Global interface
    src/data/texts.hpp
    src/data/texts.cpp

    # All game data
    src/data/data.hpp

    # Process cycles
    # Cycle template
    src/cycleTemplate.hpp
    src/cycleTemplate.cpp
    
    # Menu for selecting start option
    src/selectCycle.hpp
    src/selectCycle.cpp

    # Pause cycle for settings
    src/pauseCycle.hpp
    src/pauseCycle.cpp

    # Game part
    # Entities for game
    src/game/entity/figures.hpp
    # Entities realisations
    src/game/entity/figuresMoves.hpp
    src/game/entity/figuresMoves.cpp

    # Game board
    src/game/entity/board.hpp
    src/game/entity/board.cpp

    # Game surrounding
    src/game/entity/letters.hpp
    src/game/entity/letters.cpp

    # Base game interface (main game part)
    src/game/base.hpp
    src/game/base.cpp

    # Internet connection
    # Messages (for send and recieve)
    src/game/internet/message.hpp
    src/game/internet/message.cpp
    
    # Base internet functions
    src/game/internet/baseInternet.hpp
    src/game/internet/baseInternet.cpp

    # Internet cycles
    src/game/internet/internetCycle.hpp
    src/game/internet/internetCycle.cpp

    # Internet server part
    src/game/internet/internetServer.hpp
    src/game/internet/internetServer.cpp

    # Internet client part
    src/game/internet/internetClient.hpp
    src/game/internet/internetClient.cpp

    # Game variants
    # Singleplayer game cycle
    src/game/singlePlayer.hpp
    src/game/singlePlayer.cpp

    # Two-player game cycle
    src/game/twoPlayer.hpp
    src/game/twoPlayer.cpp

    # Server game cycle
    src/game/server.hpp
    src/game/server.cpp

    # Client game cycle
    src/game/client.hpp
    src/game/client.cpp

    # Main function
    src/main.cpp
    
    # Adding game icone
    src/set.rc
)

# Static linking standart C/C++ libraries
set(CMAKE_CXX_STANDARD_LIBRARIES "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(CMAKE_GENERATOR_PLATFORM -A "x64")

# Hidding console
#set(CMAKE_CXX_FLAGS "-mwindows -static")

# Setting other flags
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")

#set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -mwindows ${CMAKE_CSS_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Including external libraries
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2/")

# Finding place of external libraries
# Including SDL-family
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)

# Including libzip
find_package(libzip CONFIG REQUIRED)

# Including external included directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_NET_INCLUDE_DIRS})

# Including linked libraries
#target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
#target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_NET_LIBRARIES})


target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer SDL2::Net)
target_link_libraries(${CMAKE_PROJECT_NAME} ${libzip_LIBRARIES} libzip::zip)
