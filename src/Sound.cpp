#define MINIAUDIO_IMPLEMENTATION
#include "Sound.h"

bool SoundCore::Init() {
    statusSoundCore = ma_engine_init(NULL, &engineSoundCore);
    if (statusSoundCore != MA_SUCCESS) {
        return false;
    }
    return true;
}

void SoundCore::Release() {
    ma_engine_uninit(&engineSoundCore);
    // the null verification is already in the function
    /*
77799    if (pEngine == NULL) {
77800        return;
77801    }
    */
}

void SoundCore::_PlaySound(const char* audio_path) {
    // the name is strange because the standard windows function that have
    // the name PlaySound
    if (statusSoundCore == MA_SUCCESS) {
        ma_engine_play_sound(&engineSoundCore, audio_path, NULL);
    }
    // funcao padrao
}