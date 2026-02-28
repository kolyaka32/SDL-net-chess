# Full installation on Debian-like systems for development

# Updating systems and libraries
sudo apt-get update

# Visual studio code
echo "code code/add-microsoft-repo boolean true" | sudo debconf-set-selections

# Installing c++ compiling system
sudo apt-get install -y gcc g++ make cmake
# Git for downloading libraries and game itself
sudo apt-get install -y git

# External depencies
# https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md#cmake-fails-to-build-without-x11-or-wayland-support

sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev \
libharfbuzz-dev

# Need testing:
# wavpack libxmp libfreetype-dev

# On ubuntu 22.04+
sudo apt-get install libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev

# Building external libraries
# SDL
git clone https://github.com/libsdl-org/SDL.git
cd SDL; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..
# SDL_image
git clone https://github.com/libsdl-org/SDL_image.git
cd SDL_image; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..
# SDL_mixer
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..
# SDL_ttf
git clone https://github.com/libsdl-org/SDL_ttf.git
cd SDL_ttf; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..
# SDL_net
git clone https://github.com/libsdl-org/SDL_net.git
cd SDL_net; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..
# libzip
git clone https://github.com/nih-at/libzip.git
cd libzip; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..

# Building game itself
git clone https://github.com/kolyaka32/tic-tak-toe-on-SDL-net.git
cd tic-tak-toe-on-SDL-net
cmake --build ./build --config Release --target all
