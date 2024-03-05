# The standard "" game on c++ using SDL2

This repository contains sources for standart game  I made based on SDL2 library.

![Screenshot of game](/screenshots/game-main.png?raw=true)

## Installing as game
1. Simply download archieve from [releases](https://github.com/kolyaka32/tic-tac-toe-on-SDL-net/releases), unzip and run 'tic-tac-toe.exe'!
2. Also you can download game installer from [releases](https://github.com/kolyaka32/tic-tac-toe-on-SDL-net/releases).
3. Also you can build project by yourself, watch point 'Instalation for own use'.

## Usage
Classical game "tic-tac-toe", ported on computer. Rules are simple you need to set crosses or circles at field.
You goal - have pre-set number of your shape in one line/column/diagonal.
As server or first player you can choose, how place first.
Game have 3 mode: 
* Singleplayer (only if field width equal 3);
* Local two-person mode (for two people at one machine, walking in turns);
* Intrnet two person mode (for two people at two different machines, by LAN);
Also you can change numbers of width, win width and other usefull things from "settings.ini" file.

## Supported languages
* English
* Russian (Русский)
* 
* 

## Instalation for own use (windows)
Need external soft:
1. C++ compiler (such as [MSYS2](https://www.msys2.org/#installation));
2. [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. External SDL libraries ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL net](https://github.com/libsdl-org/SDL_net/releases));
5. External archieve library - libzip (build by you own), required: 1. [zlib](https://www.zlib.net/), 2. bzip (came with GNU), 3. [libzip](https://libzip.org/download/);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).

## Instalation for own use (unux-like)
Need external soft:
1. 
2. 
3. [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. External SDL libraries ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL net](https://github.com/libsdl-org/SDL_net/releases));
5. External archieve library - libzip (build by you own), required: [libzip](https://libzip.org/download/);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).


Point 3 with all last builded sources is located at [releases](https://github.com/kolyaka32/tic-tac-toe-on-SDL-net/releases) (Development-kit).

## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip