# The standard "Chess" game on c++ using SDL3
[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/kolyaka32/SDL-net-chess/blob/main/README.md)  [![ru](https://img.shields.io/badge/lang-ru-green.svg)](https://github.com/kolyaka32/SDL-net-chess/blob/main/README-ru.md)

This codebase implement standart chess game with cooperative and online mods.

![Screenshot of game](/screenshots/game-main-en.png?raw=true)


## Usage
Classical game "chess" for two players, ported on computer.
Rules are simple: your goal to checkmate the opponent's king and save your own.
You can move all your figures at game field (8x8), each move and attack by his own way.
Also there some additions:
* Awalable castling for king and rook;
* Pawn at edge position convert to queen (can be more than one);

Game have 3 game variants: 
* Singleplayer (you need to try it by yourself :D);
* Local two-person mode (for two people at one machine);
* Internet competitive mode (for two people at two different machines, by LAN, UDP);

Also you can change start field configuration and other usefull things from "settings-chess.ini" file.


## Supported languages
* English
* Russian (Русский)
* German (Deutsch) (WIP)
* Bellarussian (Беларускі) (WIP)


![Screenshot of menu](/screenshots/game-menu-en.png?raw=true)


## Launching of the game
Download archieve from [releases](https://github.com/kolyaka32/SDL-net-chess/releases), depend on platform, unzip and run 'Chess.exe'/'Chess'!


## Building by yourself (windows)
1. Install C++ compiler (such as [MSYS2](https://www.msys2.org/#installation));
2. Install [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Install [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Download and extract external SDL libraries:
4.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
4.5. [SDL3-net](https://github.com/libsdl-org/SDL_net/releases);
5. Extra library - libzip (build by your own), required:
5.1. [zlib](https://www.zlib.net/);
5.2. bzip (came with GNU);
5.3. [libzip itself](https://libzip.org/download/), build (required launch command line **as a administator**):
```bash
git clone https://github.com/nih-at/libzip.git
cd ./libzip; mkdir build; cd build;
cmake ../; make .; make install
```
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage) (Recomended to use with plugins on c++ and cmake).
6.1. (Recomended) Install extensions: C/C++ Extension pack, CMake Language Supports, CMake Tools.
7. Compile project itself
7.1. Without visual studio code:
```bash
cd ./Shaft-production-planner
mkdir build
cmake --build ./build --config Release --target all --
```
7.2. With visual studio code:
Open folder with project, select complier kit, select build configuration, and build.

### Prepaired sources for windows
Sources with all builded libraries can be located at [releases](https://github.com/kolyaka32/SDL-net-chess/releases) (Development-kit-windows).


## Building by yourself (unux systems)
1. Check updates
2. Check availability of compiler, make and cmake;
3. Check availability of git;
4. Install all necesery external libraries:
4.1 Necesary external libraries: libasound2-dev wavpack libxmp libfreetype-dev;
4.2. External SDL libraries ([SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3-image](https://github.com/libsdl-org/SDL_image/releases), [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL3-net](https://github.com/libsdl-org/SDL_net/releases));
4.3. External archieve library (build by you own), required: [libzip](https://libzip.org/download/);
5. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for easier usage).
5.1. (Recomended) Install extensions: C/C++ Extension pack, CMake Language Supports, CMake Tools.
6. Compile project itself

### Installing on Debian-like systems
```bash
sudo apt-get update
# Installing c++ compiling system
sudo apt-get install -y g++ git make cmake
# Installing libraries for SDL_mixer
sudo apt-get install -y libasound2-dev wavpack libxmp
# Installing libraries for SDL_ttf
sudo apt-get install -y libfreetype-dev
# Installing libraries for libzip
sudo apt-get install -y libzip-dev

# Building external libraries
# SDL
git clone https://github.com/libsdl-org/SDL.git
cd SDL; mkdir build; cd build
cmake ..
make; sudo make install
cd ../../
# SDL_image
git clone https://github.com/libsdl-org/SDL_image.git
cd SDL_image; mkdir build; cd build
cmake ..
make; sudo make install
cd ../../
# SDL_mixer
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer; mkdir build; cd build
cmake ..
make; sudo make install
cd ../../
# SDL_ttf
git clone https://github.com/libsdl-org/SDL_ttf.git
cd SDL_ttf; mkdir build; cd build
cmake ..
make; sudo make install
cd ../../
# SDL_net
git clone https://github.com/libsdl-org/SDL_net.git
cd SDL_net; mkdir build; cd build
cmake ..
make; sudo make install
cd ../../
# libzip
git clone https://github.com/nih-at/libzip.git
cd libzip; mkdir build; cd build
cmake ..
make; sudo make install
cd ../../

# Building app itself
git clone https://github.com/kolyaka32/SDL-net-chess.git
cd SDL-net-chess; mkdir build
cmake --build ./build --config Release --target all
```
### Prepaired sources for unix
Sources with all builded libraries can be located at [releases](https://github.com/kolyaka32/SDL-net-chess/releases) (Development-kit-unix).


## Used external libraries:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
