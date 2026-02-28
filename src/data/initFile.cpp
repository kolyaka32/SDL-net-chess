/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "initFile.hpp"
#include "macroses.hpp"
#include "logger.hpp"


// Check if has initfile
#if (USE_SETTING_FILE)

InitFile::InitFile() {
    loadSettings();
    logAdditional("Settings loaded correcly");
}

InitFile::~InitFile() {
    saveSettings();
    logAdditional("Settings saved correctly");
}

const std::string InitFile::getText(const std::string _line) const {
    return _line.substr(_line.rfind('=') + 2);
}

const unsigned InitFile::getValue(const std::string _line) const {
    return std::stoi(_line.substr(_line.rfind('=') + 2));
}

#endif  // (USE_SETTING_FILE)
