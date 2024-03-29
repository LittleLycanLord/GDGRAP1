#pragma once

#include "../../stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;

namespace models {
class Texture {
private:
    int img_width;
    int img_height;
    int colorChannels;
    unsigned char* tex_bytes;

public:
    Texture();

public:
    void initializeTexture();
    void freeImgData();

public:
    unsigned char* getTexBytes();
    int getColorChannels();
    int getImgWidth();
    int getImgHeight();
};
}  // namespace models