/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"
#include "../GUI/interface.hpp"


// Class of menu with game settings
class SettingsMenu : public GUI::GUItemplate {
 private:
	static bool active;       // Flag of showing current menu
	timer nextSound = 0;      // Time to play next sound
	Uint8 holdingSlider = 0;  // Index of holded slider

	// Button for enter and quit settings menu
	const GUI::ImageButton settingButton;
	// Background plate
	const GUI::Backplate background;
	// Title
	GUI::HighlightedStaticText titleText;
	// Flags for select language
	const GUI::ImageButton flags[(unsigned)Language::Count];
	// Sliders and it texts
	GUI::HighlightedStaticText musicText;
	GUI::Slider musicSlider;
	GUI::HighlightedStaticText soundText;
	GUI::Slider soundSlider;
	// Quit button
	GUI::TextButton exitButton;

 public:
	SettingsMenu(const App& app);
	void blit(const Window& target) const override;
	bool click(const Mouse mouse);
	void unClick();
	void scroll(App& app, const Mouse mouse, float wheelY);
	void update(App& app);
	void activate();
};
