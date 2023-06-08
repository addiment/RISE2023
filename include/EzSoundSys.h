#pragma once
#ifndef RISE_EZSOUNDSYS_H
#define RISE_EZSOUNDSYS_H

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
        explicit Sound(SoundType soundType, float vol = 1.0, const char* nick = nullptr) : Nickable(nick), type(soundType) { }
        float volume = 1.0; // TODO: change type?
        const SoundType type = EFFECT;
        [[nodiscard]] inline bool isArmed() const { return armed; }
    private:
        friend class SoundSystem;
        SoundDataHandle handle = nullptr;
        const char* filename = nullptr;
        bool armed = false;
    };

    static int setMusic();
    static PlayState stopMusic();
    static PlayState playMusic();
    [[nodiscard]] static placeholder_tc("music name/struct or something") getActiveMusic();
    static RETURN_MAY_BE_NULL bool playSound(Sound *sound, int loops = 0);
//    static bool stopSound(Sound *sound);
    static void armSound(Sound* sound, const char* file);
    static void disarmSound(Sound* sound);
private:
    friend class Manager;
    static int init();
    SoundSystem() = default;
};

#endif // RISE_EZSOUNDSYS_H
