/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../include.hpp"
#include "../define.hpp"
#include "../dataTypes.hpp"
#include "../data/languages.hpp"
#include "../data/graphics.hpp"
#include "../data/font.hpp"
#include "../data/animations.hpp"


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
      SDL_Texture *texture;
      SDL_Rect rect;
     public:
        GUItemplate();
        virtual void blit() const;
        virtual bool in(const int mouseX, const int mouseY) const;
        virtual void updateLocation();
    };


    // Static text on screen with drawing and updating functions
    class StaticText : public GUItemplate {
     private:
        const char *text;                     // Text to create from
        const float posX, posY;               // Relative positions on screen
        const ALIGNMENT_types aligment;       // Aligment type to improve displasment
        const SDL_Color color;                // Base draw color
        TTF_Font *font;                       // Font to create texture
        char *bufferText;                     // Current text to show
        friend class TextButton;              // Allowing textbutton to take data
     public:
        StaticText(const char* text, textHeight size, float X,
            float Y, SDL_Color color = BLACK, ALIGNMENT_types alignment = MIDLE_text);
        ~StaticText();
        void updateLocation() override;
        void updateLocationArgs(const unsigned count, ...);  // Create new texture
        void updateTexture();  // Updating texture
    };


    // Class of slider bar with point on it to control need parameter
    class Slider : public GUItemplate {
     private:
        SDL_Texture *textureButton;  // Texture of line (upper part of slider)
        SDL_Rect destButton;         // Place for rendering upper part
        const unsigned maxValue;     // Maximal value of state
        unsigned *link;              // Pointer to data to control
     public:
        // Create slide with need line and button images
        Slider(float X, float Y, unsigned *controlData, IMG_names lineImage = IMG_GUI_SLIDER_LINE,
            IMG_names buttonImage = IMG_GUI_SLIDER_BUTTON, unsigned max = 255);
        void setValue(int mouseX);                           // Setting new state from mouse position
        bool scroll(Sint32 wheelY, int mouseX, int mouseY);  // Checking mouse wheel action
        void blit() const override;                          // Drawing slider with need button position
    };


    // Class of buttons with image on it
    class ImageButton : public GUItemplate {
     public:
        ImageButton(float X, float Y, IMG_names textureIndex);   // Create new button
    };


    // GIF-animations
    #if ANI_count
    class GIFAnimation : public GUItemplate {
     private:
        ANI_names type;
        Uint32 frame;
        timer prevTick;
     public:
        GIFAnimation(SDL_Rect destination, ANI_names type);
        ~GIFAnimation();
        void update();
    };
    #endif


    // Bar to show some charachteristic (like health) with icone
    class Bar : public GUItemplate {
     private:
        SDL_Rect Front_rect;    // Front rect for primal color
        SDL_Rect IconeRect;     // Rect for icone, near bar, if need
        const SDL_Color color;  // Color of front part of bar
     public:
        // Create new bar with it position, primal color and icone near it
        Bar(const SDL_Rect dest, SDL_Color color, IMG_names icone = IMG_GUI_PAUSE_BUTTON);
        void blit(int width);   // Drawing bar with icone need width
    };


    // Class of box, where user can type text
    class TypeBox : public GUItemplate {
     private:
        // Class constants
        const static Uint8 bufferSize = 16;
        const ALIGNMENT_types aligment;  // Aligment type for correct placed position
        const SDL_Color color;      // Color of typing text

        // Variables
        char buffer[bufferSize+1];       // String, that was typed
        char clipboardText[bufferSize];  // Copying string for clipboard
        char swapCaret;             // Byte for swap with caret
        int caret = 0;              // Position of place, where user type
        int selectLength = 0;       // Length of selected box
        Uint8 length;               // Length of all text
        TTF_Font *font;             // Font for type text
        SDL_Rect textRect;          // Rectangle of background plate (for better visability)
        SDL_Keycode preCode;        // Code of key, that was previously pressed

        void updateTexture();       // Function for creat new texture and updat it position
        void writeClipboard();      // Function for writing clipboard content after caret
        void copyToClipboard();     // Function for writing selected text to clipboard
        void selectAll();           // Select all text
        void deleteSelected();      // Function for clearing selected part

     public:
        TypeBox(textHeight size, float posX, float posY, const char *startText = "",
            ALIGNMENT_types newAligment = MIDLE_text, SDL_Color newColor = BLACK);
        ~TypeBox();                         // Clearing font and texture
        void blit() const override;         // Function of drawing text with background plate
        const char* getString() const;      // Function of getting typed string
        void writeString(const char* str);  // Function of writing any string to buffer at caret position
        void press(SDL_Keycode code);       // Function of processing special keycodes
        void resetPress(SDL_Keycode code);  // Resetting pressing on any button
        void updateCaret();                 // Function of change caret symbol from '|' to ' ' and back
        void updateSelection(int mouseX);   // Function of updating selecting text
        void select(int mouseX);            // Function of setting caret for typing after
        void removeSelect();                // Function of removing caret after typing
    };

    // Class of backplate for
    class Backplate : public GUItemplate {
     private:
        const SDL_Color frontColor, backColor;  // Front and back colors of plate
        const Uint8 rad;  // Radius of rounding
        const Uint8 bor;  // Border (with back color)
     protected:
        void updatePlate(const SDL_Rect rect);  // Update sizes of plate
     public:
        Backplate(float centerX, float centerY, float width, float height, Uint8 radius, Uint8 border,
            const SDL_Color frontColor = GREY, SDL_Color backColor = BLACK);
        Backplate(Uint8 radius, Uint8 border,  SDL_Color frontColor = GREY,
            const SDL_Color backColor = BLACK);
        ~Backplate();
    };

    // Class of buttons with text on it
    class TextButton : public Backplate {
     private:
        const StaticText topText;
     public:
        TextButton(const char* text, textHeight size, float X, float Y,
            SDL_Color color = BLACK, ALIGNMENT_types alignment = MIDLE_text);
        void blit() const override;      // Drawing current button
        void updateLocation() override;  // Update object to match text sizes
    };

}  // namespace GUI
