#pragma once
#ifndef RISE_EZINPUTSYS_H
#define RISE_EZINPUTSYS_H

#include <unordered_set>
#include <SDL2/SDL.h>
#include "../smog/smog.h"
#include "misc.h"

class InputSystem {
public:
    enum class DigitalAction : size_t {
        Jump,
        PauseMenu,

        MenuUp,
        MenuDown,
        MenuLeft,
        MenuRight,
        MenuSelect,
        MenuCancel,

        NumActions
    };
    enum class AnalogAction : size_t {
        AnalogControls,

        NumActions
    };
    enum class ActionSet : size_t {
        GameControls,
        MenuControls,

        NumSets
    };
    static void setActionSet(ActionSet set);
    static ActionSet getCurrentActionSet();
    static FVec2 getAnalogActionValue(AnalogAction action);
    static bool getDigitalActionValue(DigitalAction action);
    static void update();
private:
    friend class Manager;
    InputSystem() = default;
    static void init();
};

#endif // RISE_EZINPUTSYS_H
