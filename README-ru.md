# Игра "Шахматы" на c++, SDL2
[![en](https://img.shields.io/badge/lang-en-green.svg)](https://github.com/kolyaka32/SDL-net-chess/blob/main/README.md)

Этот репозиторий содержит исходные файлы для стандартной игры "шахматы", которую я сделал на основе библиотеке SDL2.
В основном данный репозиторий нужен мне для обучению, тренировки и подготовки для более крупных проектов.
Также он формирует общий для всех проектов прототип "игрового движка".

![Screenshot of game](/screenshots/game-main-ru.png?raw=true)

## Установка игры
1. Скачать архив из [релизы](https://github.com/kolyaka32/SDL-net-chess/releases), распокавать и запустить 'Chess.exe'!
2. Вы можете сами собрать проект, для этого смотрите пункт 'Установка для собственного использования'.


## Использование
Классическая игра "Шахматы" для двух игроков, теперь портированная на коспьютер (ещё и мной).
Правила игры просты: ваша задача поставить мат противнику и не дать ему сделать того же.
Вы можете передвигать фигуры по игровому полю (8х8), у каждая из которых ходит и атакует по своему.
Также есть некоторые дополнительные возмоности:
* Доступна рокировка, чтобы поменять местами короля и ладью.
* Пешка, достигшая конца поля превращается в королеву (их может быть больше одной на поле). 

Есть 3 варианта игры: 
* Однопользовательский (игра с ботом (пока не работает));
* Локальная игра с напарником (для двух людей, за одим устройством);
* Многопользовательский режим по сети (для двух людей, по локальной сети);
Также вы можете изменять стартовую конфигурацию и другие полезные настройки в файле "settings5.ini".


## Поддерживаемые языки
* Английский (English)
* Русский (Russian)
* Немецкий (Deutsch) (работа в процессе)
* Белларусский (Беларускі) (работа в процессе)


![Изображение меню](/screenshots/game-menu-ru.png?raw=true)


## Установка для собственного использования (windows)
1. Установить компилятор для C++ (например [MSYS2](https://www.msys2.org/#installation));
2. Установить [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Установить [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Скачать и разархивировать библиотеки SDL (готовые):
4.1. [SDL3](https://github.com/libsdl-org/SDL/releases);
4.2. [SDL3-image](https://github.com/libsdl-org/SDL_image/releases);
4.3. [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases);
4.4. [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases);
5. Дополнительная библиотека - libzip (компилируется самостоятельно), требуется:
5.1. [zlib](https://www.zlib.net/);
5.2. bzip (идёт вместе с GNU(с компилятор));
5.3. [сама libzip](https://libzip.org/download/);
5.4. Собрать libzip используя cmake в папку 'build/';
5.5. Запустить 'make' и 'make install' в командной строке в папке 'build' (с правами администратора);
6. (Опционально) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (Рекомендуется для более простого использования с плагинами для c++ и cmake).


## Установка для собственного использования (unux системы)
1. Проверить наличие компиляторов g++, make и cmake;
2. Проверить наличие git;
3. Установить (или собрать самому) следующие библиотеки:
4. Внешние SDL библиотеки ([SDL3](https://github.com/libsdl-org/SDL/releases), [SDL3-image](https://github.com/libsdl-org/SDL_image/releases), [SDL3-mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL3-ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL3-net](https://github.com/libsdl-org/SDL_net/releases));
5. Внешняя библиотека архивации (собирается самостоятельно): [libzip](https://libzip.org/download/);
6. (Опционально) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (Рекомендуется для более простого использования с плагинами для c++ и cmake).


## Готовые исходники
Исходные файлы со всеми собранными библиотеками могут быть найден в [релизы](https://github.com/kolyaka32/Astroshuter-on-SDL/releases) (Development-kit).


## Использованные внешние зависимости:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
