#include "EzSoundSys.h"

using namespace std;

void SoundSystem::armSound(Sound* sound, const char *file) {
    if (!file || !sound) return;
    if (sound->armed) disarmSound(sound);

    switch (sound->type) {
        case EFFECT: {
            sound->handle = Mix_LoadWAV(file);
            if (sound->handle) {
                sound->armed = true;
            } else sound->handle = nullptr;
            break;
        }
        case MUSIC: {
            sound->handle = Mix_LoadMUS(file);
            if (sound->handle) {
                sound->armed = true;
            } else sound->handle = nullptr;
            break;
        }
        default: return;
    }
}

void SoundSystem::disarmSound(Sound *sound) {
    if (!sound) return;
    sound->armed = false;
    // TODO: avoid blocking calls by stopping the music if it's playing
    if (sound->handle) switch (sound->type) {
        case EFFECT: {
            Mix_FreeChunk((Mix_Chunk*)sound->handle);
            break;
        }
        case MUSIC: {
            Mix_FreeMusic((Mix_Music*)sound->handle);
            break;
        }
        default: return;
    }
}

constexpr uint16_t audioFormat = MIX_DEFAULT_FORMAT;
constexpr int audioFrequency = MIX_DEFAULT_FREQUENCY, audioChannels = MIX_DEFAULT_CHANNELS, audioChunkSize = 4096;

int SoundSystem::init() {
    int res = Mix_OpenAudio(audioFrequency, audioFormat, audioChannels, audioChunkSize);
    if (res < 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_AUDIO, "Couldn't open audio: %s\n", Mix_GetError());
        return res;
    }
    Mix_AllocateChannels(24);
    return 0;
}

// SoundSystem::SoundPlayHandle
bool SoundSystem::playSound(Sound *sound, int loops) {
    if (!sound || sound->type != EFFECT) return false;
    /*int res = */
    Mix_PlayChannel(-1, (Mix_Chunk*)sound->handle, loops);
    return true;
}

//bool SoundSystem::stopSound(SoundSystem::Sound *sound) {
//    return false;
//}
