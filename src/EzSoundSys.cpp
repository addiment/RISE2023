#include "EzSoundSys.h"

using namespace std;

constexpr uint16_t  audioFormat = MIX_DEFAULT_FORMAT;
constexpr int       audioFrequency = MIX_DEFAULT_FREQUENCY,
audioChannels = MIX_DEFAULT_CHANNELS,
audioChunkSize = 4096;

SoundSystem::Sound* activeMusic = nullptr;

bool SoundSystem::armSound(Sound* sound, const char *file) {
    if (!file || !sound) return false;
    if (sound->armed) disarmSound(sound);

    switch (sound->type) {
        case EFFECT: {
            sound->handle = Mix_LoadWAV(file);
            if (sound->handle) {
                sound->armed = true;
                return true;
            } else sound->handle = nullptr;
            break;
        }
        case MUSIC: {
            sound->handle = Mix_LoadMUS(file);
            if (sound->handle) {
                sound->armed = true;
                return true;
            } else sound->handle = nullptr;
            break;
        }
        default: break;
    }

    return false;
}

void SoundSystem::disarmSound(Sound *sound) {
    if (!sound) return;
    sound->armed = false;
    if (sound->handle) switch (sound->type) {
        case EFFECT: {
            Mix_FreeChunk((Mix_Chunk*)sound->handle);
            break;
        }
        case MUSIC: {
            Mix_HaltMusic();
            Mix_FreeMusic((Mix_Music*)sound->handle);
            break;
        }
        default: return;
    }
}

int SoundSystem::init() {

//    int nd = SDL_GetNumAudioDevices(0);
//    for (int i = 0; i < nd; i++) {
//        const char *dn = SDL_GetAudioDeviceName(i, false);
//        if (!dn) dn = "!!! NULL device !!!";
//        SDL_Log("%s", dn);
//    }

//    char* dname = nullptr;
//    {
//        SDL_AudioSpec spec{};
//        int res = SDL_GetDefaultAudioInfo(&dname, &spec, false);
//        if (res || !dname) return res;
//        SDL_Log("DEFAULT SOUND DEVICE: %s", dname);
//    }
//
//    int res = Mix_OpenAudioDevice(audioFrequency, audioFormat, audioChannels, audioChunkSize, dname, 0);
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

SoundSystem::PlayState SoundSystem::playMusic(int loops) {
    if (!activeMusic) return PlayState::UNLOADED;
    if (Mix_PausedMusic() || Mix_PlayingMusic()) Mix_ResumeMusic();
    else Mix_PlayMusic((Mix_Music*)activeMusic->handle, loops);
    Mix_VolumeMusic(activeMusic->volume);
    return SoundSystem::PLAYING;
}

bool SoundSystem::setMusic(Sound *mus) {
    if (!mus) {
        stopMusic();
        activeMusic = nullptr;
        return true;
    }
    if (!mus->armed || mus->type != MUSIC) return false;
    Mix_VolumeMusic(mus->volume);
    activeMusic = mus;
    return true;
}

SoundSystem::PlayState SoundSystem::stopMusic() {
    if (!activeMusic) return PlayState::UNLOADED;
    Mix_VolumeMusic(activeMusic->volume);
    Mix_PauseMusic();
    return SoundSystem::STOPPED;
}

SoundSystem::Sound *SoundSystem::getActiveMusic() { return activeMusic; }

void SoundSystem::flush() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
}

//bool SoundSystem::stopSound(SoundSystem::Sound *sound) {
//    return false;
//}



int SoundSystem::Sound::setVolume(int v) {
    if (v > MIX_MAX_VOLUME || v < 0) return -1;
    this->volume = v;
    switch (type) {
        case EFFECT: {
            return Mix_VolumeChunk((Mix_Chunk*)handle, volume);
        }
        case MUSIC: {
            return Mix_VolumeMusic(volume);
        }
        default: return v;
    }
}
