#pragma once

#include "GUI/baseGUI.hpp"

// Types of numerated static texts
enum TXT_types{
    // Selection menu 
    TXT_SELECT_ENTER,    // Game name
    TXT_SELECT_SINGLE,   // Singleplayer gamemode
    TXT_SELECT_TWO,      // Two player gamemode
    TXT_SELECT_SERVER,   // Host server
    TXT_SELECT_CLIENT,   // Connect to server

    // Pause texts
    TXT_PAUSE_PAUSE,     // Pause name
    TXT_PAUSE_MUSIC,     // Pause music slider text
    TXT_PAUSE_SOUND,     // Pause sound slider text

    // Game start texts
    TXT_START_SELECT,    // Text of selecting start shape

    // Stop menu
    TXT_STOP_WIN,        // Winning topic
    TXT_STOP_LOOSE,      // Loosing topic
    TXT_STOP_NOBODY,     // Topic of nobody win
    TXT_STOP_SKIP,       // Topping of skipping round
    TXT_STOP_WIN_1,      // First player win topic (for two players)
    TXT_STOP_WIN_2,      // Second player win topic (for two players)
    TXT_STOP_RESTART,    // Resatrt game button text
    TXT_STOP_MENU,       // Menu going button text

    // Internet texts
    TXT_INTERNET_TURN,   // Topic of turn of current player
    TXT_INTERNET_WAIT,   // Topic of waiting for turn

    // Server texts
    TXT_SERVER_WAIT,     // Server label of waiting to connect
    TXT_SERVER_PORT,     // Server label of current connect port

    // Client texts
    TXT_CLIENT_IP,       // IP enter label
    TXT_CLIENT_PORT,     // Port enter label
    TXT_CLIENT_CONNECT,  // Connect button text
    TXT_CLIENT_WAIT      // Start waiting label
};

// Summary text counter
#define TXT_count 25

// Types of language
enum LNG_types{
    LNG_ENGLISH,    // English language
    LNG_RUSSIAN,    // Russian language
    LNG_GERMAN,     // German language
    LNG_BELARUSIAN  // Belarusian language
};

#define LNG_count 4  // Final counter of all languages

// All static texts
class Texts
{
public:
    LNG_types language;
    GUI::staticText texts[TXT_count] = {
        // Selection menu
        {"Tic-tac-toe\nКрестики нолики\n", 
            24, 0.5, 0.1},
        {"Singleplayer\nОдиночная игра\n", 
            24, 0.5, 0.3},
        {"Two players\nДва игрока\n", 
            24, 0.5, 0.5},
        {"Create server\nСоздать сервер\n", 
            24, 0.5, 0.7},
        {"Connect\nПрисоединится\n", 
            24, 0.5, 0.9},
        
        // Game pause
        {"Pause\nПаузе\n",
            24, 0.5, 0.1},
        {"Music:\nМузыка:\n",
            24, 0.5, 0.6},
        {"Sounds:\nЗвуки:\n",
            24, 0.5, 0.8},

        // Game start
        {"Select type\nВыберите тип\n",
            31, 0.5, 0.2, BLACK},

        // Game stop
        {"You win!\nВы выйграли!\n",
            24, 0.5, 0.3},
        {"You loose...\nВы проиграли...\n", 
            24, 0.5, 0.3},
        {"Nobody win.\nНичья.\n", 
            24, 0.5, 0.3},
        {"Game stopped.\nИгра остановлена.\n",
            24, 0.5, 0.3},
        {"Cross win\nКрестик выйграл\n",
            24, 0.5, 0.3},
        {"Circle win\nКружок выйграл\n",
            24, 0.5, 0.1},
        {"Restart\nПерезапустить\n",
            24, 0.5, 0.7},
        {"Game menu\nИгровое меню\n",
            24, 0.5, 0.9},

        // Internet texts
        {"Your turn\nВаш ход\n",
            20, 0.5, 0.1, BLACK},
        {"Wait for turn\nОжидайте ход\n",
            20, 0.5, 0.1, BLACK},
        
        // Server texts
        {"Wait for connect\nОжидайте\n",
            24, 0.5, 0.1},
        {"Your port: %\nВаш порт: %\n",
            24, 0.5, 0.3},
        
        // Client texts
        {"Enter IP\nВведите IP\n",
            24, 0.5, 0.1},
        {"Enter port\nВведите порт\n",
            24, 0.5, 0.4},
        {"Connect\nПрисоединится\n",
            24, 0.5, 0.7},
        {"Wait start\nОжидайте начала\n",
            24, 0.5, 0.1, BLACK},
    };
public:
    Texts();
    ~Texts();
    void updateTranslation();
};
