#include "EzInputSys.h"

using namespace std;

//static SDL_GameController*          activeGameController = nullptr;
SMOG_InputHandle               activeSmogControllerHandle;
SMOG_InputHandle               handles[SMOG_MAX_INPUT_HANDLES]{};
SMOG_ActionSetHandle     actionSetHandles    [(size_t)InputSystem::ActionSet::NumSets        ]{};
SMOG_AnalogActionHandle  analogActionHandles [(size_t)InputSystem::AnalogAction::NumActions  ]{};
SMOG_DigitalActionHandle digitalActionHandles[(size_t)InputSystem::DigitalAction::NumActions ]{};

InputSystem::ActionSet activeActionSet;

void InputSystem::init() {

    // Digital actions
    digitalActionHandles[(size_t)InputSystem::DigitalAction::Jump           ] = SMOG_GetDigitalActionHandle("jump");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::Special        ] = SMOG_GetDigitalActionHandle("special");
//    digitalActionHandles[(size_t)InputSystem::DigitalAction::PauseMenu      ] = SteamInput_GetDigitalActionHandle("pause_menu"); // WRONG
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuUp         ] = SMOG_GetDigitalActionHandle("menu_up");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuDown       ] = SMOG_GetDigitalActionHandle("menu_down");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuLeft       ] = SMOG_GetDigitalActionHandle("menu_left");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuRight      ] = SMOG_GetDigitalActionHandle("menu_right");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuSelect     ] = SMOG_GetDigitalActionHandle("menu_select");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuCancel     ] = SMOG_GetDigitalActionHandle("menu_cancel");
    // Analog actions
    analogActionHandles[(size_t)InputSystem::AnalogAction::AnalogControls   ] = SMOG_GetAnalogActionHandle ( "AnalogControls");
    // Action set handles
    actionSetHandles[(size_t)InputSystem::ActionSet::GameControls           ] = SMOG_GetActionSetHandle("GameControls");
    actionSetHandles[(size_t)InputSystem::ActionSet::MenuControls           ] = SMOG_GetActionSetHandle("MenuControls");
}

void InputSystem::update() {
    // TODO: this comment is from Spacewar, consider?
    // There's a bug where the action handles aren't non-zero until a config is done loading. Soon config
    // information will be available immediately. Until then try to init as long as the handles are invalid.

    int numHandles = SMOG_GetConnectedControllers(handles);
    // If there's an active controller, and if we're not already using it, select the first one.
    if (numHandles && (activeSmogControllerHandle != handles[0])) {
        activeSmogControllerHandle = handles[0];
    }

//    for (int i = 0; i < STEAM_INPUT_MAX_COUNT; i++) {
//        if (handles[i] == 0) continue; // Skip invalid handles
//        SteamInput_ActivateActionSet(inputHandles[i], actionSet);
//        // TODO: replace with for(:), this should be more dynamic
//        InputAnalogActionData_t gyroData = SteamInput_GetAnalogActionData(inputHandles[i], TiltCube);
//        InputDigitalActionData_t resetData = SteamInput_GetDigitalActionData(inputHandles[i], ResetCamera);
//    }
}

void InputSystem::setActionSet(ActionSet set) {
    activeActionSet = set;
    SMOG_ActivateActionSet(activeSmogControllerHandle, actionSetHandles[(size_t)set]);
}

FVec2 InputSystem::getAnalogActionValue(AnalogAction action) {
    SMOG_AnalogActionHandle h = analogActionHandles[(size_t)action];
    if (h && activeSmogControllerHandle) {
        SMOG_AnalogActionData data = SMOG_GetAnalogActionData(activeSmogControllerHandle, h);
        return {data.x, data.y};
    } else return { 0, 0 };
}

bool InputSystem::getDigitalActionValue(DigitalAction action) {
    SMOG_DigitalActionHandle h = digitalActionHandles[(size_t)action];
    if (h && activeSmogControllerHandle) {
        SMOG_DigitalActionData data = SMOG_GetDigitalActionData(activeSmogControllerHandle, h);
        return data.bState;
    } else {
        return false;
    }
}

InputSystem::ActionSet InputSystem::getCurrentActionSet() {
    return activeActionSet;
}