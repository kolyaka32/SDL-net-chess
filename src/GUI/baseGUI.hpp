#pragma once

#include "../include.hpp"
#include "../define.hpp"
#include "../graphics.hpp"
#include "../font.hpp"
#include "../animations.hpp"


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
        void blit();
        bool in(const int mouseX, const int mouseY);
    };


    // Static text on screen with drawing functions
    class staticText : public virtual GUItemplate
    {
    private:
        const static Uint8 BUFFER_SIZE = 50;  // Length of buffers for text
        const char *text;                // Text to show on screen
        float posX, posY;          // Relative positions on screen
        ALIGNMENT_types aligment;  // Aligment type to improve displasment
        SDL_Color color;           // Base draw color
        TTF_Font *font;            // Font to create texture
    public:
        staticText(const char* newText, textHeight newSize, float newX, 
            float newY, SDL_Color newColor = WHITE, ALIGNMENT_types newAlignment = MIDLE_text);
        ~staticText();
        void updateText(int number = 0);  // Create new texture with displasment '%' to entered number
    };


    // Class of slider bar with point on it to control some parameter
    class Slider : public virtual GUItemplate
    {
    private:
        SDL_Texture *textureButton;  // Texture of line (upper part of slider)
        SDL_Rect destButton;         // Place for rendering upper part
        Uint16 maxValue;             // Maximal value of state
    public:
        Uint16 state;                // Current state of slider

        Slider(float Y, Uint16 max = 255, IMG_names lineImage = IMG_GUI_SLIDER_LINE, 
            IMG_names buttonImage = IMG_GUI_SLIDER_BUTTON);  // Create slide with need line and button images
        void setValue(int mouseX);                              // Setting new mouse position
        bool scroll(Sint32 wheelY, int mouseX, int mouseY);     // Checking mouse wheel action
        void blit();                                            // Drawing slider with need button position
    };


    // Class of buttons with image on it
    class ImageButton : public virtual GUItemplate
    {
    private:
        //
    public:
        ImageButton(float X, float Y, IMG_names textureIndex);   // Create new button
    };


    // Class of buttons with text on it
    class TextButton : public virtual GUItemplate
    {
    private:
        staticText &topText;     // Pointer to text on this button (shortcut)
    public:
        TextButton(float X, float Y, staticText &top);   // Create new button
        void blit();                      // Drawing current button
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
        //SDL_Rect Back_rect;         // Background rect for second color
        SDL_Rect Front_rect;        // Front rect for primal color
        SDL_Rect IconeRect;         // Rect for icone, near bar
        SDL_Color color;
    public:
        // Create new bar with it position, primal color and icone near it
        Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone);  
        void blit( int width );  // Drawing bar with icone need width
    };


    // Class of box, where user can type text
    class typeBox : public virtual GUItemplate
    {
    private:
        // Global class constants
        const static Uint8 bufferSize = 16;

        // Constants from creating
        ALIGNMENT_types aligment;  // Aligment type for correct placed position
        SDL_Color color;           // Color of typing text

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
        void blit();                                 // Function of drawing text with background plate
        void writeString(char* str, bool freeData);  // Function of writing any string to buffer at caret position
        void press(SDL_Keycode code);                // Function of processing special keycodes
        void updateCaret();                          // Function of change caret symbol from '|' to ' ' and back
        void select();                               // Function of setting caret for typing after
        void removeSelect();                         // Function of removing caret after typing
    };
}