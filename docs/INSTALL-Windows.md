# Full installation on Fedora for development

1. Install C++ compiler (such as Mingw from [MSYS2](https://www.msys2.org/#installation));
2. Install [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Install [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Installing external SDL libraries has two options:
4.1. Download precompiled:
4.1.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.1.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.1.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.1.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
4.2. Compile by youreself (Recomended):
For correct installation (make install required launch command line **as a administator**)
Also for easier installation can use 'cmake-gui' with selected Mingw-makefile
```bash
# Installing SDL (main library)
git clone https://github.com/libsdl-org/SDL.git
cd SDL; mkdir build; cd build
cmake ..; make; sudo make install; cd ../..
# SDL_image
git clone https://github.com/libsdl-org/SDL_image.git
cd SDL_image; mkdir build; cd build
cmake ..; make; sudo make install; cd ../..
# SDL_mixer
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer; mkdir build; cd build
cmake ..; make; sudo make install; cd ../..
# SDL_ttf
git clone https://github.com/libsdl-org/SDL_ttf.git
cd SDL_ttf; mkdir build; cd build
cmake ..; make; sudo make install; cd ../..
# Libzip (for archieve loading)
git clone https://github.com/nih-at/libzip.git
cd libzip; mkdir build; cd build
cmake ..; make; sudo make install; cd ../..
```
5. Extra library - libzip (build by your own), required:
5.1. [zlib](https://www.zlib.net/):
git clone https://github.com/madler/zlib.git
cd zlib; mkdir build; cd build
cmake ..; make; sudo make install; cd ../..
5.2. bzip (came with GNU);
5.3. [libzip itself](https://libzip.org/download/)
```bash
git clone https://github.com/nih-at/libzip.git
cd ./libzip; mkdir build; cd build;
cmake ..; make .; make install
```
6. (Optional) IDE [Visual Studio Code](https://code.visualstudio.com/download) (for easier usage).
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
