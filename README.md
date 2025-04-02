# The standard "Chess" game on c++ using SDL2
[![ru](https://img.shields.io/badge/lang-ru-green.svg)](https://github.com/kolyaka32/SDL-net-chess/blob/main/README-ru.md)

This repository contains sources for standart chess game, I made based on SDL2 library.
Mostly this repository is need for my own study, training and preparing for bigger projects.
Also this creating projects unifed "game engine".

![Screenshot of game](/screenshots/game-main-en.png?raw=true)

## Installing of game
1. Download archieve from [releases](https://github.com/kolyaka32/SDL-net-chess/releases), unzip and run 'Chess.exe'!
2. You can build project by yourself, watch point 'Instalation for own use'.


## Usage
Classical game "chess" for two players, now ported on computer.
Rules are simple: your goal to checkmate the opponent's king and save your own.
You can move all your figures at game field (8x8), each move and attack by his own way.
Also there some additions:
* Awalable castling for king and rook;
* Pawn at edge position conevrt to queen (can be more than one);

Game have 3 game variants: 
* Singleplayer (playing with bot (now not work));
* Local two-person mode (for two people at one machine);
* Internet two person mode (for two people at two different machines, by LAN);
Also you can change start configuration and other usefull things from "settings5.ini" file.


## Supported languages
* English
* Russian (Русский)
* German (Deutsch) (WIP)
* Bellarussian (Беларускі) (WIP)


![Screenshot of menu](/screenshots/game-menu-en.png?raw=true)


## Instalation for own use (windows)
1. Install C++ compiler (such as [MSYS2](https://www.msys2.org/#installation));
2. Install [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Install [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Download and extract external SDL libraries:
4.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
5. Extra library - libzip (build by your own), required:
5.1. [zlib](https://www.zlib.net/);
5.2. bzip (came with GNU);
5.3. [libzip itself](https://libzip.org/download/);
5.4. Build libzip using cmake to 'build/' folder;
5.5. Run 'make' and 'make install' at command line at builed folder (as administrator);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage) (Recomended to use with plugins on c++ and cmake).


## Instalation for own use (unux systems)
1. Check availability of compilers[g++], [make] and [cmake];
2. Check availability of [git];
3. Install all necesery external libraries:
4. External SDL libraries ([SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3-image](https://github.com/libsdl-org/SDL_image/releases), [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL3-net](https://github.com/libsdl-org/SDL_net/releases));
5. External archieve library - libzip (build by you own), required: [libzip](https://libzip.org/download/);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).


## Prepaired sources
Sources with all builded libraries can be located at [releases](https://github.com/kolyaka32/Astroshuter-on-SDL/releases) (Development-kit).


## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
