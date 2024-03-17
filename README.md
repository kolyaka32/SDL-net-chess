# The standard "Chess" game on c++ using SDL2

This repository contains sources for standart chess game, I made based on SDL2 library.

![Screenshot of game](/screenshots/game-main.png?raw=true)

## Installing of game
1. Download archieve from [releases](https://github.com/kolyaka32/SDL-net-chess/releases), unzip and run 'Chess.exe'!
2. Also you can build project by yourself, watch point 'Instalation for own use'.


## Usage
Classical game "chess", ported on computer. Rules are simple you need to
You goal - 

Game have 3 game variants: 
* Singleplayer (only if field width equal 3);
* Local two-person mode (for two people at one machine, walking in turns);
* Intrnet two person mode (for two people at two different machines, by LAN);
Also you can change start configuration and other usefull things from "settings5.ini" file.


## Supported languages
* English
* Russian (Русский)
* German (Deutsch)
* Bellarussian (Беларускі)


## Instalation for own use (windows)
1. Install C++ compiler (such as [MSYS2](https://www.msys2.org/#installation));
2. Install [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Install [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Download and extract external SDL libraries ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL net](https://github.com/libsdl-org/SDL_net/releases));
5. Download and extract archieve library - libzip (build by you own), required: 1. [zlib](https://www.zlib.net/), 2. bzip (came with GNU), 3. [libzip itself](https://libzip.org/download/), 4. Build libzip using cmake to folder, 5. Run 'make', 'make install' (as administrator);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).

Point 4 with all last builded libraries is located at [releases](https://github.com/kolyaka32/SDL-net-chess/releases) (Development-kit).


## Instalation for own use (linux-like)
1. Check availability of [make] and [cmake];
2. 
3. 
4. External SDL libraries ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL net](https://github.com/libsdl-org/SDL_net/releases));
5. External archieve library - libzip (build by you own), required: [libzip](https://libzip.org/download/);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).




## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
