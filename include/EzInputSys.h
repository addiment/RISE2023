#pragma once
#ifndef TOOLKITENGINEV3_EZINPUTSYS_H
#define TOOLKITENGINEV3_EZINPUTSYS_H

#include <unordered_map>
#include <unordered_set>
#include <SDL2/SDL.h>
#include "misc.h"

class InputSystem {
public:
    enum class DigitalAction : size_t {
        Jump,
        Special,
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
    static void setAction(DigitalAction digitalAction, bool value);
    static void setAction(AnalogAction analogAction, FVec2 value);
private:
    friend class Manager;
    InputSystem() = default;
    static void init();
};

#endif // TOOLKITENGINEV3_EZINPUTSYS_H
