/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "graphics.hpp"
#include "dataLoader.hpp"


// Class of window icone
class Icone : virtual GraphicsLibrary, public virtual DataLoader {
 private:
    void loadIcone(const std::string name);  // Loading and set icone with need name

 public:
    Icone();  // Create and set icone
};
