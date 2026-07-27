#include <iostream>
#include "Textures.h"
#include "stbi_load.h"     

/////////////////////////////////////////////////////////////////////////////////
// Constructor and Destructor
Texture::Texture() {

};
Texture::~Texture() {
};

/////////////////////////////////////////////////////////////////////////////////
// OpenGL Texture
void Texture::CreateBasicTexture(i32 texture_slot, i32 texture_type, i32 texture_interpolation_type, const char* path_image, bool flip_image, bool unbind) {
    CreateTexture(texture_slot, texture_type);
    ConfigTexture(texture_type, texture_interpolation_type);
    LoadImage(path_image, flip_image);
    ProcessImage(unbind);
};

void Texture::CreateTexture(i32 texture_slot, i32 texture_type) {
    glGenTextures(1, &TextureID);
    glActiveTexture(texture_slot);           // slot de textura que vamos modificar, um ID pode ter 16 slots
    // ativar antes do glBindTexture()
    glBindTexture(texture_type, TextureID);
    // gera a textura, ainda não preenchida
}

void Texture::ConfigTexture(i32 texture_type, i32 texture_interpolation_type) {
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, texture_interpolation_type);     
    glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, texture_interpolation_type);                
}

/////////////////////////////////////////////////////////////////////////////////
// Load Assets

void Texture::LoadImage(const char* path_image, bool flip_image) {
    if (flip_image == true)
        stbi_set_flip_vertically_on_load(true);     // diz para carregar de forma invertida

    ImageData = stbi_load(path_image, &ImageWidth, &ImageHeight, &nColorChannel, 4);  
    // 4 é padrão e força saida de RGBA pelo stbi_loader

    if (!ImageData)
        InfoLog = "TEXTURES::FAILED_TO_LOAD";
}

void Texture::ProcessImage(bool unbind) {

    if (ImageData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImageWidth, ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);       // transfere da RAM para a VRAM
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        InfoLog = "TEXTURES::FAILED_TO_PROCESS";
    }
    
    ReleaseData();  // releases image data
                    // I made this function to make easy 
                    // to create other off class images

    if (unbind) 
        glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::ReleaseTexture() {
    if (TextureID != 0)
        glDeleteTextures(1, &TextureID);
}

/////////////////////////////////////////////////////////////////////////////////
// Getters

GLuint Texture::GetTextureID() {
    return TextureID;
}

void Texture::ReleaseData() {
    stbi_image_free(ImageData);
}

bool Texture::isPixelBlack(i64 x, i64 y) {
    /*
        precisamos pegar o ponteiro da nossa imagem
        e dar incrementos de posição até chegar no
        pixel que desejamos, afinal, a variavel
        da imagem é apenas um ponteiro para o inicio de 
        um array gigante, que dita a cor do pixel.

        como o calculo funciona?
        a imagem é 2D mas o array é 1D, para chegarmos em 
        X = 3 e Y = 1 (linha 1 e coluna 3) precisamos pegar 
        a largura total da imagem (seria a largura de uma linha)
        e multiplicar por qual linha queremos acessar (no caso: 1)
        e então somar com qual coluna (no caso 3). E os canais apenas 
        dizem que são 4 bytes que devemos pular (como stride do opengl mesmo)
        e então cada largura de linha tera 4x mais seu tamanho.
    */ 

    // offset = (linha * largura + coluna) * canais (RGBA)

    // std::cout << "Width: " << ImageWidth << " - Height: " << ImageHeight << std::endl;

    //i32 offset = (y * (ImageWidth / 2732.66f) + x) * 4;
    
    if ((x < 0) || (x > ImageWidth) || (y < 0) || (y > ImageHeight)) {
      return false;
      // se passar do indice vai dar out of bound.
    }

    
    i32 offset = (y * (ImageWidth) + x) * 4;
    i64 r, g, b, a;
    r = ImageData[offset + 0];
    g = ImageData[offset + 1];
    b = ImageData[offset + 2];
    a = ImageData[offset + 3];
    // apenas move o indice;

    if ((r <= 32) && (g <= 32) && (b <= 32)) {
        return true;
    } else {
        return false;
    }
}

i32 Texture::GetWidth() {
  return ImageWidth;
}

i32 Texture::GetHeight() {
  return ImageHeight;
}
