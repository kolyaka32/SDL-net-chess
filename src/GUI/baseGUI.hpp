/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include <array>
#include "../data/app.hpp"


// Namespace of objects for GUI (Graphic User Interface)
namespace GUI {
    // Text aligment type
    enum class Aligment : unsigned {
        Left,
        Midle,
        Right,
    };


    // Object, that will be drawn at screen
    class Template {
     protected:
        const Window& window;

     public:
        Template(const Window& window);
        virtual void blit() const;
    };


    // Object with texture, that will be drawn
    class TextureTemplate : public Template {
     protected:
        SDL_Texture* texture;
        SDL_FRect rect;

     public:
        TextureTemplate(const Window& window, SDL_Texture* texture = nullptr);
        TextureTemplate(const Window& window, SDL_FRect rect, SDL_Texture* texture = nullptr);
        TextureTemplate(TextureTemplate&& object) noexcept;
        void move(float X, float Y);
        void blit() const override;
        virtual bool in(const Mouse mouse) const;
    };


    // Class of rounded backplate for better understability
    class RoundedBackplate : public TextureTemplate {
     public:
        RoundedBackplate(const Window& window, float centerX, float centerY, float width, float height,
            float radius, float border, Color frontColor = GREY, Color backColor = BLACK);
        RoundedBackplate(const Window& window, const SDL_FRect& rect, float radius, float border,
            Color frontColor = GREY, Color backColor = BLACK);
        RoundedBackplate(RoundedBackplate&& object) noexcept;
        ~RoundedBackplate() noexcept;
    };


    // Class with rectangular backplate for typeBox
    class RectBackplate : public TextureTemplate {
     public:
        RectBackplate(const Window& window, float centerX, float centerY, float width, float height,
            float border, Color frontColor = GREY, Color backColor = BLACK);
        RectBackplate(const Window& window, const SDL_FRect& rect,
            float border, Color frontColor = GREY, Color backColor = BLACK);
        RectBackplate(const RectBackplate& copyObject) noexcept;
        RectBackplate(RectBackplate&& moveObject) noexcept;
        ~RectBackplate() noexcept;
    };


    // Textures
    #if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
    // Class of slider bar with point on it to control need parameter
    class Slider : public TextureTemplate {
     private:
        SDL_Texture *buttonTexture;  // Texture of line (upper part of slider)
        SDL_FRect buttonRect;        // Place for rendering upper part

     public:
        // Create slide with need line and button images
        Slider(const Window& window, float X, float Y, float width, float startValue,
            Textures lineImage = Textures::SliderLine, Textures buttonImage = Textures::SliderButton);
        Slider(Slider&& object) noexcept;
        float setValue(float mouseX);  // Setting new state from mouse position
        float scroll(float wheelY);    // Checking mouse wheel action
        void blit() const override;       // Drawing slider with need button position
    };


    // Class of buttons with image on it
    class ImageButton : public TextureTemplate {
     public:
        ImageButton(const Window& window, float X, float Y, float width, Textures name);
        ImageButton(ImageButton&& object) noexcept;
    };
    #endif


    // Animations
    #if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
    class Animation : public TextureTemplate {
     private:
        const Animations type;
        const IMG_Animation* animation;
        unsigned frame;
        timer prevTick;

     public:
        Animation(const Window& window, float X, float Y, float width, float height, Animations type);
        Animation(const Window& window, const SDL_FRect& destination, Animations type);
        Animation(Animation&& object) noexcept;
        ~Animation() noexcept;
        void update();
    };
    #endif


    // Text part
    #if (USE_SDL_FONT) && (PRELOAD_FONTS)
    // Static text on screen
    class StaticText : public TextureTemplate {
     public:
        template <typename ...Args>
        StaticText(const Window& window, float X, float Y, const LanguagedText&& texts, float height = Height::Main,
            Color color = WHITE, Aligment aligment = Aligment::Midle, const Args... args)
        : TextureTemplate(window) {
                // Checking for all chars
                char buffer[100];
                SDL_snprintf(buffer, sizeof(buffer), texts.getString().c_str(), args...);

                // Creating surface with text
                texture = window.createTexture(Fonts::Main, height, buffer, 0, color);

                // Updating rect height for correct button
                rect.w = texture->w;
                rect.h = texture->h;
                rect.x = SDL_roundf(window.getWidth() * X - (rect.w * (unsigned)aligment / 2));
                rect.y = SDL_roundf(window.getHeight() * Y - rect.h / 2);
            }
        StaticText(StaticText&& object) noexcept;
        ~StaticText() noexcept;
    };


    // Static text on screen
    class HighlightedStaticText : public TextureTemplate {
     public:
        HighlightedStaticText(const Window& window, float X, float Y, const LanguagedText&& texts, int frameThickness,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        HighlightedStaticText(HighlightedStaticText&& object) noexcept;
        ~HighlightedStaticText() noexcept;
    };


    // Dynamicly updated text on screen
    class DynamicText : public TextureTemplate {
     private:
        const LanguagedText texts;  // Text to create from
        const float posX;           // Relative positions on screen
        const Aligment aligment;    // Aligment type to improve displasment
        const Color color;          // Base draw color
        const float height;         // Height of text to draw

     public:
        DynamicText(const Window& window, float X, float Y, LanguagedText&& texts,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        DynamicText(DynamicText&& object) noexcept;
        ~DynamicText() noexcept;
        template <typename ...Args>
        void setValues(Args&& ...args) {
            // Checking for all chars
            char buffer[100];
            std::snprintf(buffer, sizeof(buffer), texts.getString().c_str(), args...);

            // Creating surface with text
            texture = window.createTexture(Fonts::Main, height, buffer, 0, color);

            // Moving draw rect to new place
            rect.w = texture->w;
            rect.h = texture->h;
            rect.x = window.getWidth() * posX - (rect.w * (unsigned)aligment / 2);
        }
    };


    // Class of field, where user can type text
    template <unsigned bufferSize = 16>
    class TypeField : public TextureTemplate {
     protected:
        // Class constants
        const int posX;               // Relevant x position on screen
        const Aligment aligment;      // Aligment type for correct placed position
        const Color textColor;        // Color of typing text (and inversed background)
        const Color backColor;        // Color of background plate (and inversed text)
        TTF_Font* font;               // Font for type text

        // Variables
        char buffer[bufferSize+1];    // String, that was typed
        size_t length = 0;            // Length of all text
        size_t caret = 0;             // Position of place, where user type
        timer needSwapCaret = 0;      // Time, when next need to change caret
        int selectLength = 0;         // Length of selected box

        bool showCaret = false;       // Flag, if need to show caret
        SDL_FRect caretRect;          // Place, where caret should be at screen
        SDL_FRect inversedRectDest;   // Rect of inversed selected text, where should be drawn
        SDL_FRect inversedRectSrc;    // Part of text, that should be reversed (relative)
        SDL_Texture* inverseTexture;  // Texture of inversed selected box
        bool pressed = false;         // Flag if currently mouse is pressed and selecting text
        bool selected = false;        // Flag if currently typing in this field

        void updateTexture();         // Creat new texture of updated text
        void updateSelected();        // Update reversed rect position (selected part)
        void deleteSelected();        // Clearing selected part
        void writeClipboard();        // Write clipboard content after caret
        void copyToClipboard();       // Writing selected text to clipboard

     public:
        TypeField(const Window& window, float posX, float posY, const char *startText = "",
            float height = Height::TypeBox, Aligment aligment = Aligment::Midle,
            Color textColor = BLACK, Color backColor = WHITE);
        TypeField(TypeField<bufferSize>&& object) noexcept;
        ~TypeField() noexcept;
        void writeString(const char* str);   // Write string to buffer at caret position
        void type(SDL_Keycode code);         // Processing special keycodes (like arrows, home, CTRL-C...)
        void update(float mouseX);           // Highlated area of typing
        bool click(const Mouse mouse);       // Set caret for typing at specified place
        void unclick();                      // Reset pressing
        const char* getString();             // Return typed string
        void setString(const char* string);  // Replace text with new string
        void blit() const override;          // Draw current text with selection at screen
    };


    // Object for typying in text with backplate for visability
    template <unsigned bufferSize = 16>
    class TypeBox : public TypeField<bufferSize> {
     private:
        GUI::RectBackplate backplate;

     public:
        TypeBox(const Window& window, float posX, float posY, const char *startText = "", float height = Height::TypeBox,
            Aligment aligment = Aligment::Midle, unsigned frameWidth = 2, Color textColor = BLACK);
        TypeBox(TypeBox&& object) noexcept;
        void blit() const override;  // Function for draw inputting text with backplate
        bool in(const Mouse mouse) const override;
    };


    // Class of buttons with text on it
    class TextButton : public HighlightedStaticText {
     private:
        GUI::RoundedBackplate backplate;

     public:
        TextButton(const Window& window, float X, float Y, const LanguagedText&& texts, float size = Height::Main,
            Color color = WHITE, Aligment aligment = Aligment::Midle);
        TextButton(TextButton&& object) noexcept;
        void blit() const override;
    };


    // Class of appearing for time and hidden by time text
    class InfoBox : public HighlightedStaticText {
     private:
        unsigned counter = 0;
        static const unsigned maxCounter = 100;

     public:
        InfoBox(const Window& window, float X, float Y, const LanguagedText&& texts,
            float height = Height::Main, Color color = WHITE, Aligment aligment = Aligment::Midle);
        InfoBox(InfoBox&& object) noexcept;
        void update();
        void reset();
    };


    // Class for box with message and actions with it
    class TwoOptionBox : public Template {
     private:
        // Flag of showing
        bool active = false;

        // Background plate for better visability
        GUI::RoundedBackplate background;
        // Main text - title
        GUI::HighlightedStaticText mainText;
        // Select variants
        GUI::TextButton button1, button2;

     public:
        TwoOptionBox(const Window& window, const LanguagedText&& title,
            const LanguagedText&& button1Text, const LanguagedText&& button2Text);
        TwoOptionBox(TwoOptionBox&& object) noexcept;
        int click(const Mouse mouse);  // Return 1, if active; 2 if 1 button pressed; 3 if 2 button pressed
        void activate();
        void reset();
        bool isActive() const;
        void blit() const override;
    };


    // Class for box with message and actions with it
    class OneOptionBox : public Template {
     private:
        // Flag of showing
        bool active = false;

        // Background plate for better visability
        GUI::RoundedBackplate background;
        // Main text - title
        GUI::HighlightedStaticText mainText;
        // Select variants
        GUI::TextButton button;

     public:
        OneOptionBox(const Window& window, const LanguagedText&& title,
            const LanguagedText&& buttonText);
        OneOptionBox(OneOptionBox&& object) noexcept;
        int click(const Mouse mouse);  // Return 1, if active; 2 if button pressed
        void activate();
        void reset();
        bool isActive() const;
        void blit() const override;
    };

    #endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)

    // Menu for scrolling items
    template <class Item, class SourceItem>
    class ScrollBox : public Template {
     protected:
        // Items, for draw
        int startField = 0;
        int endField = 0;
        const int maxItems;
        // Items in reverce order for easier appending
        std::vector<Item> items;
        // Adding text of absence of objects
        #if (USE_SDL_FONT) && (PRELOAD_FONTS)
        GUI::HighlightedStaticText emptySavesText;
        #endif
        // Slider for showing position
        SDL_FRect sliderRect;
        const SDL_FRect sliderBackRect;
        bool holding = false;
        float holdPosition;

        void moveUp();
        void moveDown();

     public:
        // Create menu for scrolling objects, placed at center with (posX, posY) and size.
        // Shows "maxShowedItems" items at a time
        ScrollBox(const Window& window, float posX, float posY, float width, float height, int maxShowedItems,
            const LanguagedText&& emptyItemsText);
        ScrollBox(const Window& window, float posX, float posY, float width, float height, int maxShowedItems,
            std::vector<SourceItem> items, const LanguagedText&& emptyItemsText);
        ScrollBox(ScrollBox&& object) noexcept;
        ~ScrollBox() noexcept;
        void addItem(const SourceItem& field);
        void clear();
        // Return index of selected+1 and 0, if don't
        int click(const Mouse mouse);
        void unclick();
        void update(const Mouse mouse);
        void scroll(const Mouse mouse, float wheelY);
        void blit() const override;
    };

}  // namespace GUI
