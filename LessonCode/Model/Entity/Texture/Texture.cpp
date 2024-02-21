#include "Texture.hpp"

using namespace models;

Texture::Texture() {
    this->img_width = 0;
    this->img_height = 0;
    this->colorChannels = 0;
    this->tex_bytes = NULL;
}

void Texture::initializeTexture() {
    stbi_set_flip_vertically_on_load(true);
    this->tex_bytes = stbi_load("Model/Ayaya.png", &this->img_width, &this->img_height, &this->colorChannels, 0);
}

void Texture::freeImgData() {
    stbi_image_free(tex_bytes);
}

unsigned char* Texture::getTexBytes() {
    return this->tex_bytes;
}

int Texture::getImgWidth() {
    return this->img_width;
}

int Texture::getImgHeight() {
    return this->img_height;
}
