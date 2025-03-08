/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "initFile.hpp"
#include <fstream>
#include <string>

// Files to setup
#include "../languages.hpp"
#include "../game/board.hpp"


InitFile::InitFile(Music& _music, Sounds& _sounds)
: music(_music), sounds(_sounds) {
    loadSettings();
}

InitFile::~InitFile() {
    saveSettings();
}

const std::string InitFile::getText(const std::string _line) const {
    return _line.substr(MAX(_line.rfind(' '), _line.rfind('='))+1);
}

const unsigned InitFile::getValue(const std::string _line) const {
    return std::stoi(_line.substr(MAX(_line.rfind(' '), _line.rfind('='))+1));
}

void InitFile::loadSettings() {
    // Reading file
    std::ifstream inSettings(SETTING_FILE);
    std::string currentLine;  // Input string line

    // Reading file until it end
    while (std::getline(inSettings, currentLine)) {
        std::string parameter = currentLine.substr(0, MIN(currentLine.find(' '), currentLine.find('=')));

        // Switching between options
        if (parameter == "language") {
            std::string lang = getText(currentLine);
            if (lang == "english") {
                currentLanguage = LNG_ENGLISH;
            } else if (lang == "russian") {
                currentLanguage = LNG_RUSSIAN;
            } else if (lang == "german") {
                currentLanguage = LNG_GERMAN;
            } else if (lang == "belarusian") {
                currentLanguage = LNG_BELARUSIAN;
            }
        } else if (parameter == "music") {
            music.setVolume(getValue(currentLine));
        } else if (parameter == "sounds") {
            sounds.setVolume(getValue(currentLine));
        } else if (parameter == "start config") {
            strcpy_s(boardConfig, 85, getText(currentLine).c_str());
        }/* else if (parameter == "IP") {
            baseIP = getText(currentLine);
        } else if (parameter == "port") {
            basePort = getText(currentLine);
        }*/
    }

    inSettings.close();  // Closing reading file
}

void InitFile::saveSettings() {
    // Creating output file
    std::ofstream outSettings(SETTING_FILE);

    // Writing data with comments to file
    outSettings << "# Settings of chess game:\n";

    // Writing language
    outSettings << "language = ";
    switch (currentLanguage) {
    case LNG_ENGLISH:
        outSettings << "english\n";
        break;

    case LNG_RUSSIAN:
        outSettings << "russian\n";
        break;

    case LNG_GERMAN:
        outSettings << "german\n";
        break;

    case LNG_BELARUSIAN:
        outSettings << "belarusian\n";
        break;
    }

    // Writing music and sounds volumes
    outSettings << "music = " << music.getVolume() << "\n";
    outSettings << "sounds = " << music.getVolume() << "\n";

    // Writing starting config (order of figures)
    outSettings << "\nGame configuration:\n";
    outSettings << "start config = " << boardConfig << "\n";

    // Writing internet connection data
    /*outSettings << "\n# Internet base parameters:\n";
    outSettings << "IP = ", baseIP << "\n";
    outSettings << "port = ", basePort << "\n";*/
}
