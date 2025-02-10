
#include "textures.hpp"


Textures::Textures(const DataLoader& loader) {

}

Textures::~Textures() {

}

void Textures::loadTexture() {

}

SDL_Texture* Textures::operator[] (IMG_names index) {
    return textures[index];
}
