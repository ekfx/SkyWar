#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <iostream>
#include "../include/miniaudio/miniaudio.h"

class SoundCore {       // A ESTUDAR MELHOR
private:
    ma_result statusSoundCore;
    ma_engine engineSoundCore;
    std::string infoLog;

public:
    // construtor e destrutor
    SoundCore() {};
    ~SoundCore() {};

    // Utilitarios
    bool Init();    // thanks to SplinterOfChaos if you're seeing it
    void Release();
    void _PlaySound(const char* audio_path); // tocar som simples

};

#endif // SOUND_H