#pragma once
#ifndef TOOLKITENGINEV3_EZSOUNDSYS_H
#define TOOLKITENGINEV3_EZSOUNDSYS_H

#include "misc.h"
#include "Nickable.h"

class SoundSystem {
public:
    // opaque type
    typedef void* SoundDataHandle;

    enum PlayState {
        UNLOADED,
        STOPPED,
        PLAYING
    };

    enum SoundType {
        EFFECT,
        MUSIC
    };

    class Sound : public Nickable {
    public:
        explicit Sound(SoundType soundType) : type(soundType) { }
        explicit Sound(SoundType soundType, int vol = MIX_MAX_VOLUME, const char* nick = nullptr) : Nickable(nick), type(soundType), volume(vol) { }
        const SoundType type = EFFECT;
        int setVolume(int v);
        [[nodiscard]] inline bool isArmed() const { return armed; }
    private:
        friend class SoundSystem;
        unsigned char volume = MIX_MAX_VOLUME;
        SoundDataHandle handle = nullptr;
        const char* filename = nullptr;
        bool armed = false;
    };

    static bool setMusic(Sound* mus);
    static PlayState stopMusic();
    static PlayState playMusic(int loops = -1);
    [[nodiscard]] static RETURN_MAY_BE_NULL Sound* getActiveMusic();
    static bool playSound(Sound *sound, int loops = 0);
//    static bool stopSound(Sound *sound);
    static bool armSound(Sound* sound, const char* file);
    static void disarmSound(Sound* sound);
private:
    friend class Manager;
    static void flush();
    static int init();
    SoundSystem() = default;
};

#endif // TOOLKITENGINEV3_EZSOUNDSYS_H
