
#include "textures.hpp"


Textures::Textures(const DataLoader& _loader, unsigned _count, const char* _names[]) {

}

Textures::~Textures() {

}

void Textures::loadTexture() {

}

SDL_Texture* Textures::operator[] (IMG_names index) {
    return textures[index];
}
