/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>
#include "../data/window.hpp"
#include "../define.hpp"
#include "../languages.hpp"
#include "../data/time.hpp"


// Namespace of objects for GUI (Graphic User Interface)
namespace GUI {
    // Text alignment type
    enum ALIGNMENT_types{
        LEFT_text,
        MIDLE_text,
        RIGHT_text
    };


    // Graphic user interface template for other objects
    class GUItemplate {
     protected:
        SDL_Texture* texture;
        SDL_FRect rect;
     public:
        GUItemplate();
        virtual void blit(const Window& _target) const;
        bool in(float mouseX, float mouseY) const;
    };


    // Static text on screen
    class StaticText : public GUItemplate {
     public:
        StaticText(const Window& target, const std::string (&text)[LNG_count], float size, float X,
            float Y, SDL_Color color = BLACK, ALIGNMENT_types alignment = MIDLE_text);
        ~StaticText();
    };


    // Static text on screen
    class HighlightedStaticText : public GUItemplate {
     public:
        HighlightedStaticText(const Window& target, const std::string (&text)[LNG_count], float size, float X,
            float Y, int frame, SDL_Color color = BLACK, ALIGNMENT_types alignment = MIDLE_text);
        ~HighlightedStaticText();
    };


    // Dynamicly updated text on screen
    class DynamicText : public GUItemplate {
     private:
        const std::string (&text)[LNG_count];  // Text to create from
        const float posX, posY;          // Relative positions on screen
        const ALIGNMENT_types aligment;  // Aligment type to improve displasment
        const SDL_Color color;           // Base draw color
        const float height;              // Height of text to draw
        char currentText[50];            // Current text for print
     protected:
        void updateTexture(const Window& _target);
     public:
        DynamicText(const Window& _target, const std::string (&text)[LNG_count], float size, float X,
        float Y, SDL_Color color = BLACK, ALIGNMENT_types alignment = MIDLE_text);
        ~DynamicText();
        void updateLocation(const Window& _target);
        void updateLocationArgs(const Window& _target, ...);  // Change text, depend on another arguments
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
            ANI_names type;
            Uint32 frame;
            timer prevTick;
     public:
            GIFAnimation(Window& _target, SDL_Rect destination, ANI_names type);
            ~GIFAnimation();
            void update(Window& _target);
    };
    #endif


    // Class of field, where user can type text
    class TypeField : public GUItemplate {
     protected:
        // Class constants
        const static int bufferSize = 16;  // Size of text buffer
        const int posX;                    // Relevant x position on screen
        const ALIGNMENT_types aligment;    // Aligment type for correct placed position
        const SDL_Color textColor;         // Color of typing text
        const Window& target;              // Target, where draw to
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

        void updateTexture();              // Creat new texture and update it position
        void deleteSelected();             // Clearing selected part
        void writeClipboard();             // Write clipboard content after caret
        void copyToClipboard();            // Writing selected text to clipboard

     public:
        TypeField(const Window& _target, float height, float posX, float posY, const char *startText,
            ALIGNMENT_types newAligment = MIDLE_text, SDL_Color textColor = BLACK);
        ~TypeField();                        // Clearing font and texture
        const char* getString() const;       // Function of getting typed string
        void writeString(const char* str);   // Function of writing any string to buffer at caret position
        void press(SDL_Keycode code);        // Function of processing special keycodes
        void updateCaret();                  // Function of change caret symbol from '|' to ' ' and back
        void updateSelection(float mouseX);  // Function of updating selecting text
        void select(float mouseX);           // Function of setting caret for typing after
        void removeSelect();                 // Function of removing caret after typing
    };

    // Class of type field with frame for better writing
    class TypeBox : public TypeField {
     private:
        SDL_Texture* backTexture;  // Texture of backplate
        const SDL_FRect backRect;  // Rect of backplate
     public:
        TypeBox(const Window& _target, float textHeight, float posX, float posY, const char* startText = "");
        void blit() const;
        bool in(float mouseX, float mouseY) const;
    };

    // Class of backplate for
    class Backplate : public GUItemplate {
     public:
        Backplate(const Window& _target, float centerX, float centerY, float width, float height, float radius, float border,
            SDL_Color frontColor = GREY, SDL_Color backColor = BLACK);
        Backplate(const Window& _target, const SDL_FRect& rect, float radius, float border, SDL_Color frontColor = GREY,
            SDL_Color backColor = BLACK);
        ~Backplate();
    };

    // Class of buttons with text on it
    class TextButton : public HighlightedStaticText {
     private:
        const Backplate backplate;
     public:
        TextButton(const Window& _target, const std::string (&text)[LNG_count], float size, float X, float Y,
            SDL_Color color = WHITE, ALIGNMENT_types alignment = MIDLE_text);
        void blit(const Window& _target) const override;  // Drawing current button
    };

}  // namespace GUI
