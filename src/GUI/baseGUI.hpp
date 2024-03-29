#pragma once

#include "../include.hpp"
#include "../define.hpp"
#include "../dataTypes.hpp"
#include "../data/graphics.hpp"
#include "../data/font.hpp"
#include "../data/animations.hpp"


// Namespace of objects for UI
namespace GUI{

    // Text alignment type
    enum ALIGNMENT_types{
        LEFT_text,
        MIDLE_text,
        RIGHT_text
    };


    // Graphic
    class GUItemplate
    {
    protected:
        SDL_Texture *texture;
        SDL_Rect rect;
    public:
        GUItemplate();
        void blit() const;
        bool in(const int mouseX, const int mouseY) const;
    };


    // Static text on screen with drawing and updating functions
    class StaticText : public virtual GUItemplate
    {
    private:
        const static Uint8 BUFFER_SIZE = 50;  // Length of buffers for text
        const char *text;                     // Text to show on screen
        const float posX, posY;               // Relative positions on screen
        const ALIGNMENT_types aligment;       // Aligment type to improve displasment
        const SDL_Color color;                // Base draw color
        TTF_Font *font;                       // Font to create texture
    public:
        StaticText(const char* text, textHeight size, float X, 
            float Y, SDL_Color color = BLACK, ALIGNMENT_types alignment = MIDLE_text);
        ~StaticText();
        void updateText(int number = 0);  // Create new texture with displasment '%' to enter number to display
    };


    // Class of slider bar with point on it to control need parameter
    template <typename linkType = Uint8>
    class Slider : public virtual GUItemplate
    {
    private:
        SDL_Texture *textureButton;  // Texture of line (upper part of slider)
        SDL_Rect destButton;         // Place for rendering upper part
        const linkType maxValue;     // Maximal value of state
        linkType &link;              // Pointer to data to control
    public:
        Slider(float X, float Y, linkType &controlData, IMG_names lineImage = IMG_GUI_SLIDER_LINE, 
            IMG_names buttonImage = IMG_GUI_SLIDER_BUTTON, linkType max = 255);  // Create slide with need line and button images
        ~Slider();
        void setValue(int mouseX);                              // Setting new state from mouse position
        bool scroll(Sint32 wheelY, int mouseX, int mouseY);     // Checking mouse wheel action
        void blit() const;                                      // Drawing slider with need button position
    };


    // Class of buttons with image on it
    class ImageButton : public virtual GUItemplate
    {
    public:
        ImageButton(float X, float Y, IMG_names textureIndex);   // Create new button
    };


    // Class of buttons with text on it
    class TextButton : public virtual GUItemplate
    {
    private:
        const StaticText &topText;  // Pointer to text on this button (shortcut)
    public:
        TextButton(float X, float Y, StaticText &top);   // Create new button
        void blit() const;                      // Drawing current button
    };


    // GIF-animations
    #if ANI_count
    class GIFAnimation : public virtual GUItemplate
    {
    private:
        ANI_names type;
        Uint32 frame;
        timer prevTick;
    public:
        GIFAnimation( SDL_Rect destination, ANI_names type );
        ~GIFAnimation();
        void blit();
    };
    #endif


    // Bar to show some charachteristic (like health) with icone
    class Bar : public virtual GUItemplate
    {
    private:
        SDL_Rect Front_rect;    // Front rect for primal color
        SDL_Rect IconeRect;     // Rect for icone, near bar, if need
        const SDL_Color color;  // Color of front part of bar
    public:
        // Create new bar with it position, primal color and icone near it
        Bar( const SDL_Rect dest, SDL_Color color, IMG_names icone = IMG_GUI_PAUSE_BUTTON);
        void blit( int width );  // Drawing bar with icone need width
    };


    // Class of box, where user can type text
    class typeBox : public virtual GUItemplate
    {
    private:
        // Global class constants
        const static Uint8 bufferSize = 16;

        // Constants from creating
        const ALIGNMENT_types aligment;  // Aligment type for correct placed position
        const SDL_Color color;     // Color of typing text

        // Variables
        Uint8 caret;               // Position of place, where user type
        Uint8 length;              // Length of all text
        TTF_Font *font;            // Font for type text
        SDL_Rect backRect;         // Rectangle of background plate (for better visability)

        void updateTexture();      // System function of creating new texture and updating his position

    public:
        char buffer[bufferSize + 1];  // Read only data, which write in this typebox

        typeBox(textHeight size, float posX, float posY, const char *startText = "", 
            ALIGNMENT_types newAligment = MIDLE_text, SDL_Color newColor = BLACK);
        ~typeBox();                                  // Clearing font and texture
        void blit() const;                           // Function of drawing text with background plate
        void writeString(char* str, bool freeData);  // Function of writing any string to buffer at caret position
        void press(SDL_Keycode code);                // Function of processing special keycodes
        void updateCaret();                          // Function of change caret symbol from '|' to ' ' and back
        void select();                               // Function of setting caret for typing after
        void removeSelect();                         // Function of removing caret after typing
    };
}