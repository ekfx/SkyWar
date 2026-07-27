#ifndef TEXTURES_H
#define TEXTURES_H

#include <GLAD/glad.h>    
#include <GLFW/glfw3.h>
#include <string>

#include "Types.h"

class Texture {
private:
    GLuint TextureID;
    i32 ImageWidth, ImageHeight, nColorChannel; // Dados da Imagem
    u8 *ImageData;                               // Ponteiro para imagem
    // Como um byte armazena uma imagem?

    std::string InfoLog;

public:
    /////////////////////////////////////////////////////////////////////////////////
    // Constructor and Destructor
    Texture();
    ~Texture();

    /////////////////////////////////////////////////////////////////////////////////
    // OpenGL Texture
    void CreateBasicTexture(i32 texture_slot, i32 texture_type, i32 texture_interpolation_type, const char* path_image, bool flip_image, bool unbind);
    void CreateTexture(i32 texture_slot, i32 texture_type);
    void ConfigTexture(i32 texture_type, i32 texture_interpolation_type);
    void ReleaseTexture();

    /////////////////////////////////////////////////////////////////////////////////
    // Load Assets
    void LoadImage(const char* path_image, bool flip_image);
    void ProcessImage(bool unbind);

    /////////////////////////////////////////////////////////////////////////////////
    // Getters
    GLuint GetTextureID();
    void ReleaseData();
    bool isPixelBlack(i64 x, i64 y);
    i32 GetWidth();
    i32 GetHeight();
};

#endif //TEXTURES_H
