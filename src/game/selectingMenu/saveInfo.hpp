/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../fieldSave.hpp"
#include "../../GUI/interface.hpp"


// Information of one concrete save (date and picture for load)
class SaveInfo : public GUI::TextureTemplate {
 private:
    // Backplate
    GUI::RoundedBackplate backplate;
    // Save parameters
    //GUI::HighlightedStaticText saveNameText;
    GUI::HighlightedStaticText lastModifiedText;

 public:
    explicit SaveInfo(const Window& window, int position, const FieldSave& field);
    SaveInfo(SaveInfo&& info) noexcept;
    ~SaveInfo() noexcept;
    void moveUp();
    void moveDown();
    void blit() const override;
    bool in(Mouse mouse) const override;
};
