
// Types of data
typedef Uint8 coord;       // Type of data for field coordinates
typedef Uint8 cell;        // Type of cell content
typedef Uint16 count;      // Type of data for any counters

typedef Uint64 timer;      // Type of data for time (SDL_GetTicks64())
typedef Uint8 textHeight;  // Type of heights of any letters

// Structs
// Global application data with render and window
struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

// Structer of storing object
struct Data{
    char* data;   // Data of need object
    Uint64 size;  // Size of need object
};

// Types of language
enum LNG_types{
    LNG_ENGLISH,  // English language
    LNG_RUSSIAN   // Russian language
};

#define LNG_count 2  // Final counter of all languages