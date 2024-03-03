#include "include.hpp"
#include "dataTypes.hpp"


#define FNT_count 1  // Number of fonts for better count

class Font
{
private:
    char* data;   // Pointer to data of font
    Uint64 size;  // Size of font
public:
    Font(/* args */);
    ~Font();

    // Function of creating font with need height
    TTF_Font *createFont(textHeight size);
};
