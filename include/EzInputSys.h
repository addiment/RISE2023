#pragma once
#ifndef RISE_EZINPUTSYS_H
#define RISE_EZINPUTSYS_H

#include <unordered_set>
#include "Manager.h"
#include <SDL2/SDL.h>
#include "../smog/smog.h"

class InputSystem;
inline class InputSystem* InputSystem();

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
    void setActionSet(ActionSet set);
    ActionSet getCurrentActionSet();
    FVec2 getAnalogActionValue(AnalogAction action);
    bool getDigitalActionValue(DigitalAction action);
    void update();
private:
    friend inline class InputSystem* InputSystem() {
        static class InputSystem* global = nullptr;
        if (!global) global = new class InputSystem();
        return global;
    };
    friend class Manager;
    InputSystem() = default;
    void init();
};

#endif // RISE_EZINPUTSYS_H
