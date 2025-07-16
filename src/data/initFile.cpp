/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "initFile.hpp"


InitFile::InitFile(Music& _music, Sounds& _sounds)
: music(_music), sounds(_sounds) {
    loadSettings();
}

InitFile::~InitFile() {
    saveSettings();
}

const std::string InitFile::getText(const std::string _line) const {
    return _line.substr(_line.rfind('=')+2);
}

const unsigned InitFile::getValue(const std::string _line) const {
    return std::stoi(_line.substr(_line.rfind('=')+2));
}
