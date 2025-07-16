# Игра "Шахматы" на c++, SDL3
[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/kolyaka32/SDL-net-chess/blob/main/README.md)  [![ru](https://img.shields.io/badge/lang-ru-green.svg)](https://github.com/kolyaka32/SDL-net-chess/blob/main/README-ru.md)

Этот репозиторий содержит стандартную игру "шахматы" с локальным и онлайн режимами.

![Изображение игры](/screenshots/game-main-ru.png?raw=true)


## Использование
Классическая игра "Шахматы" для двух игроков, теперь портированная на коспьютер (ещё и мной).
Правила игры просты: ваша задача поставить мат противнику и не дать ему сделать того же.
Вы можете передвигать фигуры по игровому полю (8х8), у каждая из которых ходит и атакует по своему.
Также есть некоторые дополнительные возмоности:
* Доступна рокировка, чтобы поменять местами короля и ладью.
* Пешка, достигшая конца поля превращается в королеву (их может быть больше одной на поле). 

Есть 3 варианта игры: 
* Однопользовательский (попробуйте сами :D);
* Локальная игра с напарником (для двух людей, за одим устройством);
* Многопользовательский режим по сети (для двух людей, по локальной сети);

Также вы можете изменять стартовую конфигурацию поля и другие полезные настройки в файле "settings-chess.ini".


## Поддерживаемые языки
* Английский (English)
* Русский (Russian)
* Немецкий (Deutsch) (работа в процессе)
* Белларусский (Беларускі) (работа в процессе)


![Изображение меню](/screenshots/game-menu-ru.png?raw=true)


## Запуск игры
Скачать архив из [релизы](https://github.com/kolyaka32/SDL-net-chess/releases),  зависимости от системы, распокавать и запустить 'Chess.exe'/'Chess'!


## Самостоятельная сборка (windows)
1. Установить компилятор для C++ (например [MSYS2](https://www.msys2.org/#installation));
2. Установить [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Установить [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Скачать и разархивировать библиотеки SDL (готовые):
4.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
4.5. [SDL3-net](https://github.com/libsdl-org/SDL_net/releases);
5. Дополнительная библиотека - libzip (компилируется самостоятельно), требуется:
5.1. [zlib](https://www.zlib.net/) (можно скачать [готовый](https://github.com/madler/zlib/releases) или собрать самостоятельно аналогично остальным библиотекам);
5.2. bzip (идёт вместе с GNU(с компилятор));
5.3. [libzip itself](https://libzip.org/download/), сборка (требуется запустить командную строку **от имени администратора**):
```bash
git clone https://github.com/nih-at/libzip.git
cd ./libzip; mkdir build; cd build;
cmake ../; make .; make install
```
6. (Дополнительно) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (Рекомендуется для более простого использования с плагинами для c++ и cmake).
6.1. (Рекомендуется) Установить следующие расширения: C/C++ Extension pack, CMake Language Supports, CMake Tools.
7. Сборка самого проекта
7.1. Без visual studio code (из командной строки):
```bash
cd ./Shaft-production-planner
mkdir build
cmake --build ./build --config Release --target all --
```
7.2. С visual studio code:
Открыть папку с проектом, выбрать компилятор из установленных, выбрать конфигурации сборки, и, наконец, скомпилировать проект.

### Подготовленные исходники для windows
Исходные файлы со всеми собранными библиотеками могут быть найден в [релизы](https://github.com/kolyaka32/SDL-net-chess/releases) (Development-kit-windows).


## Самостоятельная сборка (unux системы)
1. Проверить наличие обновлений
2. Проверить наличие компилятора, make и cmake;
3. Проверить наличие git;
4. Установить внешние библиотеки:
4.1 Обязательные внешние библиотеки: libasound2-dev wavpack libxmp libfreetype-dev;
4.2. Внешние SDL библиотеки ([SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3-image](https://github.com/libsdl-org/SDL_image/releases), [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL3-net](https://github.com/libsdl-org/SDL_net/releases));
4.3. Внешняя библиотека архивации (собирается самостоятельно): [libzip](https://libzip.org/download/);
5. (Дополнительно) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (Рекомендуется для более простого использования с плагинами для c++ и cmake).
5.1. (Рекомендуется) Установить следующие расширения: C/C++ Extension pack, CMake Language Supports, CMake Tools.
6. Сборка самого проекта

### Установка на Debian-подобных системах
```bash
sudo apt-get update
# Установка системы сборки для c++
sudo apt-get install -y g++ git make cmake
# Установка дополнительных библиотек для SDL_mixer
sudo apt-get install -y libasound2-dev wavpack libxmp
# Установка дополнительных библиотек для SDL_ttf
sudo apt-get install -y libfreetype-dev
# Установка дополнительных библиотек для libzip
sudo apt-get install -y libzip-dev

# Сборка внешних библиотек
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

# Сборка самого проекта
git clone https://github.com/kolyaka32/SDL-net-chess.git
cd SDL-net-chess; mkdir build
cmake --build ./build --config Release --target all
```
### Готовые исходники
Исходные файлы со всеми собранными библиотеками могут быть найден в [релизы](https://github.com/kolyaka32/Astroshuter-on-SDL/releases) (Development-kit-unix).


## Использованные внешние зависимости:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
