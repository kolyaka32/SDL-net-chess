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


## Установка для собственного использования (windows)
1. Установить компилятор для C++ (например [MSYS2](https://www.msys2.org/#installation));
2. Установить [Make](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download);
3. Установить [CMake](https://sourceforge.net/projects/cmake.mirror/);
4. Установить и распоковать внешние библиотеки: ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL net](https://github.com/libsdl-org/SDL_net/releases));
5. Установить и распоковать библиотеку для архивации - libzip (собирается самим пользователем), требует: 1. [zlib](https://www.zlib.net/), 2. bzip (идёт вместе с GNU), 3. [libzip itself](https://libzip.org/download/), 4. Build libzip using cmake to folder, 5. Run 'make', 'make install' (as administrator);
6. (Опционально) Визуальная оболочка для редактирования кода [Visual Studio Code](https://code.visualstudio.com/download) (для более простого использования) (Рекомендуется с плагинами на c++ и cmake).

Пункт 4 со всеми собранными библиотеками можеи быть найден в [релизы](https://github.com/kolyaka32/SDL-net-chess/releases) (Development-kit).


## Установка для собственного использования (linux-like)
1. Check availability of [make] and [cmake];
2. 
3. 
4. External SDL libraries ([SDL2](https://github.com/libsdl-org/SDL/releases), [SDL image](https://github.com/libsdl-org/SDL_image/releases), [SDL mixer](https://github.com/libsdl-org/SDL_mixer/releases), [SDL ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL net](https://github.com/libsdl-org/SDL_net/releases));
5. External archieve library - libzip (build by you own), required: [libzip](https://libzip.org/download/);
6. (Optional) Code editor [Visual Studio Code](https://code.visualstudio.com/download) (for better usage).




## Использованные внешние зависимости:
* https://github.com/libsdl-org/SDL
* https://github.com/libsdl-org/SDL_image
* https://github.com/libsdl-org/SDL_mixer
* https://github.com/libsdl-org/SDL_ttf
* https://github.com/libsdl-org/SDL_net
* https://github.com/nih-at/libzip
