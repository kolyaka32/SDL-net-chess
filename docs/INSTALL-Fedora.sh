# Full installation on Fedora for development

# Updating systems and libraries
sudo dnf update
sudo dnf upgrade

# Visual studio code
sudo rpm --import https://packages.microsoft.com/keys/microsoft.asc &&
echo -e "[code]\nname=Visual Studio Code\nbaseurl=https://packages.microsoft.com/yumrepos/vscode\nenabled=1\nautorefresh=1\ntype=rpm-md\ngpgcheck=1\ngpgkey=https://packages.microsoft.com/keys/microsoft.asc" | sudo tee /etc/yum.repos.d/vscode.repo > /dev/null
sudo dnf install code

# Installing c++ compiling system
sudo dnf install -y gcc g++ make cmake
# Git for SDL and game itself
sudo dnf install -y git

# External depencies
# https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md#cmake-fails-to-build-without-x11-or-wayland-support

sudo dnf install -y alsa-lib-devel fribidi-devel pulseaudio-libs-devel pipewire-devel \
libX11-devel libXext-devel libXrandr-devel libXcursor-devel libXfixes-devel \
libXi-devel libXScrnSaver-devel libXtst-devel dbus-devel ibus-devel \
systemd-devel mesa-libGL-devel libxkbcommon-devel mesa-libGLES-devel \
mesa-libEGL-devel vulkan-devel wayland-devel wayland-protocols-devel \
libdrm-devel mesa-libgbm-devel libusb1-devel libdecor-devel \
pipewire-jack-audio-connection-kit-devel libthai-devel \
harfbuzz-devel

# Need for fedora 40+
sudo dnf install zlib-ng-compat-static

# Installing SDL (main library)
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

# Libzip (for archieve loading)
git clone https://github.com/nih-at/libzip.git
cd libzip; mkdir build; cd build
cmake ..; make; sudo make install
cd ../..

# Building game itself
git clone https://github.com/kolyaka32/tic-tak-toe-on-SDL-net.git
cd tic-tak-toe-on-SDL-net
cmake --build ./build --config Release --target all
