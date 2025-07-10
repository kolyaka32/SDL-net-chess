/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Namespace of objects for GUI (Graphic User Interface)
namespace GUI {
    // Text aligment type
    enum class Aligment : unsigned {
        Left,
        Midle,
        Right,
    };


    // Graphic user interface template for other objects
    class GUItemplate {
     protected:
        SDL_Texture* texture;
        SDL_FRect rect;
     public:
        GUItemplate();
        virtual void blit(const Window& _target) const;
        bool in(const Mouse mouse) const;
    };


    // Static text on screen
    class StaticText : public GUItemplate {
     public:
        StaticText(const Window& target, float X, float Y, const LanguagedText texts,
            float size, Color color = BLACK, Aligment aligment = Aligment::Midle);
        ~StaticText();
    };


    // Static text on screen
    class HighlightedStaticText : public GUItemplate {
     public:
        HighlightedStaticText(const Window& target, float X, float Y, const LanguagedText texts, 
            int frameThickness, float size, Color color = BLACK, Aligment aligment = Aligment::Midle);
        ~HighlightedStaticText();
    };


    // Dynamicly updated text on screen
    class DynamicText : public GUItemplate {
     private:
        const LanguagedText texts;             // Text to create from
        const float posX;                      // Relative positions on screen
        const Aligment aligment;               // Aligment type to improve displasment
        const Color color;                     // Base draw color
        const float height;                    // Height of text to draw

     public:
        DynamicText(const Window& _target, float X, float Y, const LanguagedText texts,
            float size = 20, Color color = BLACK, Aligment aligment = Aligment::Midle);
        ~DynamicText();
        template <typename ...Args>
        void setValues(const Window& _target, Args&& ...args) {
            // Checking for all chars
            char buffer[100];
            std::sprintf(buffer, texts.getString().c_str(), std::forward<Args>(args)...);

            // Creating surface with text
            texture = _target.createTexture(FNT_MAIN, height, buffer, 0, color);

            // Moving draw rect to new place
            rect.w = texture->w;
            rect.h = texture->h;
            rect.x = WINDOW_WIDTH * posX - (rect.w * (unsigned)aligment / 2);
        }
    };


    // Class of slider bar with point on it to control need parameter
    class Slider : public GUItemplate {
     private:
        SDL_Texture *textureButton;  // Texture of line (upper part of slider)
        SDL_FRect buttonRect;        // Place for rendering upper part
        const unsigned maxValue;     // Maximal value of state
     public:
        // Create slide with need line and button images
        Slider(const Window& _target, float X, float Y, unsigned startValue, IMG_names lineImage = IMG_GUI_SLIDER_LINE,
            IMG_names buttonImage = IMG_GUI_SLIDER_BUTTON, unsigned max = 255);
        unsigned setValue(float mouseX);                  // Setting new state from mouse position
        unsigned scroll(float wheelY);                    // Checking mouse wheel action
        void blit(const Window& _target) const override;  // Drawing slider with need button position
    };


    // Class of buttons with image on it
    class ImageButton : public GUItemplate {
    public:
        ImageButton(const Window& _target, float X, float Y, IMG_names textureIndex);
    };


    // GIF-animations
    #if ANI_count
    class GIFAnimation : public GUItemplate {
     private:
        const Uint8 type;
        SDL_Texture* texture = nullptr;
        Uint64 prevTick;
        const SDL_FRect dest;

     public:
        GIFAnimation(Window& target, SDL_Rect destination, ANI_names type);
        ~GIFAnimation();
        void draw(const Window& target);
    };
    #endif


    // Class of field, where user can type text
    template <unsigned bufferSize = 16>
    class TypeField {
     protected:
        // Class constants
        const int posX;                    // Relevant x position on screen
        const Aligment aligment;           // Aligment type for correct placed position
        const Color textColor;             // Color of typing text
        const Window& target;              // Target, where draw to
        SDL_Texture* backTexture;          // Texture of backplate
        const SDL_FRect backRect;          // Rect of backplate
        TTF_Font* font;                    // Font for type text

        // Variables
        char buffer[bufferSize];           // String, that was typed
        size_t length = 0;                 // Length of all text
        size_t caret = 0;                  // Position of place, where user type
        int selectLength = 0;              // Length of selected box
        bool showCaret = false;            // Flag, if need to show caret
        timer needSwapCaret = 0;           // Time, when next need to change caret
        SDL_FRect caretRect;               // Place, where caret should be at screen
        char clipboardText[bufferSize];    // Copying string for clipboard use
        bool pressed = false;              //
        bool selected = false;             //
        SDL_Texture* textTexture;          // Texture of text
        SDL_FRect textRect;                // Rect of text

        void select(float _mouseX);        // Select last letter to create writing symbol
        void updateTexture();              // Creat new texture and update it position
        void deleteSelected();             // Clearing selected part
        void writeClipboard();             // Write clipboard content after caret
        void copyToClipboard();            // Writing selected text to clipboard

     public:
        TypeField(const Window& target, float posX, float posY, float height, const char *startText = "",
            Aligment aligment = Aligment::Midle, Color textColor = BLACK);
        ~TypeField();                        // Clearing font and texture
        void writeString(const char* str);   // Function of writing any string to buffer at caret position
        void type(SDL_Keycode code);         // Function of processing special keycodes
        void update(float mouseX);           // Function of change caret symbol from '|' to ' ' and back
        void press(const Mouse mouse);       // Function of setting caret for typing after
        void unpress();                      // Function of resetting pressing
        const char* getString();             // Function of getting typed string
        void setString(const char* string);  // Function for replace text with new string
        void blit() const;                   // Function for draw at screen
        bool in(const Mouse mouse) const;    // Function of checking pressing
    };

    // Class of backplate for
    class Backplate : public GUItemplate {
     public:
        Backplate(const Window& target, float centerX, float centerY, float width, float height, float radius, float border,
            Color frontColor = GREY, Color backColor = BLACK);
        Backplate(const Window& _target, const SDL_FRect& rect, float radius, float border, Color frontColor = GREY,
            Color backColor = BLACK);
        ~Backplate();
    };

    // Class of buttons with text on it
    class TextButton : public HighlightedStaticText {
     private:
        const Backplate backplate;

     public:
        TextButton(const Window& target, float X, float Y, const LanguagedText texts, float size,
            Color color = WHITE, Aligment aligment = Aligment::Midle);
        void blit(const Window& _target) const override;
    };

    // Class of appearing for time and hidden by time text
    class InfoBox : public StaticText {
     private:
        unsigned counter = 0;
        static const unsigned maxCounter = 100;

     public:
        InfoBox(const Window& target, float X, float Y, const LanguagedText texts,
            float size, Color color = WHITE, Aligment aligment = Aligment::Midle);
        void update();
        void reset();
    };

}  // namespace GUI
