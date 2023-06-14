#include "EzInputSys.h"
#include <steam/steam_api_flat.h>
#include <steam/isteaminput.h>

using namespace std;

//static SDL_GameController*          activeGameController = nullptr;
InputHandle_t               activeSteamControllerHandle;
InputHandle_t               handles[STEAM_INPUT_MAX_COUNT]{};
InputActionSetHandle_t    actionSetHandles    [(size_t)InputSystem::ActionSet::NumSets        ]{};
InputAnalogActionHandle_t analogActionHandles [(size_t)InputSystem::AnalogAction::NumActions  ]{};
InputDigitalActionHandle_t digitalActionHandles[(size_t)InputSystem::DigitalAction::NumActions ]{};

InputSystem::ActionSet activeActionSet;

void InputSystem::init() {

    // Digital actions
    digitalActionHandles[(size_t)InputSystem::DigitalAction::Jump           ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(), "jump");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::Special        ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"special");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuUp         ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"menu_up");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuDown       ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"menu_down");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuLeft       ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"menu_left");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuRight      ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"menu_right");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuSelect     ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"menu_select");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuCancel     ] = SteamAPI_ISteamInput_GetDigitalActionHandle(SteamAPI_SteamInput(),"menu_cancel");
    // Analog actions
    analogActionHandles[(size_t)InputSystem::AnalogAction::AnalogControls   ] = SteamAPI_ISteamInput_GetAnalogActionHandle(SteamAPI_SteamInput(), "AnalogControls");
    // Action set handles
    actionSetHandles[(size_t)InputSystem::ActionSet::GameControls           ] = SteamAPI_ISteamInput_GetActionSetHandle(SteamAPI_SteamInput(), "GameControls");
    actionSetHandles[(size_t)InputSystem::ActionSet::MenuControls           ] = SteamAPI_ISteamInput_GetActionSetHandle(SteamAPI_SteamInput(), "MenuControls");
}

void InputSystem::update() {
    // TODO: this comment is from Spacewar, consider?
    // There's a bug where the action handles aren't non-zero until a config is done loading. Soon config
    // information will be available immediately. Until then try to init as long as the handles are invalid.

    int numHandles = SteamAPI_ISteamInput_GetConnectedControllers(SteamAPI_SteamInput(), handles);
    // If there's an active controller, and if we're not already using it, select the first one.
    if (numHandles && (activeSteamControllerHandle != handles[0])) {
        activeSteamControllerHandle = handles[0];
    }
}

void InputSystem::setActionSet(ActionSet set) {
    activeActionSet = set;
    SteamAPI_ISteamInput_ActivateActionSet(SteamAPI_SteamInput(), activeSteamControllerHandle, actionSetHandles[(size_t)set]);
}

FVec2 InputSystem::getAnalogActionValue(AnalogAction action) {
    InputAnalogActionHandle_t h = analogActionHandles[(size_t)action];
    if (h && activeSteamControllerHandle) {
        InputAnalogActionData_t data = SteamAPI_ISteamInput_GetAnalogActionData(SteamAPI_SteamInput(), activeSteamControllerHandle, h);
        return {data.x, data.y};
    } else return { 0, 0 };
}

bool InputSystem::getDigitalActionValue(DigitalAction action) {
    InputDigitalActionHandle_t h = digitalActionHandles[(size_t)action];
    if (h && activeSteamControllerHandle) {
        InputDigitalActionData_t data = SteamAPI_ISteamInput_GetDigitalActionData(SteamAPI_SteamInput(), activeSteamControllerHandle, h);
        return data.bState;
    } else {
        return false;
    }
}

InputSystem::ActionSet InputSystem::getCurrentActionSet() {
    return activeActionSet;
}

void InputSystem::setAction(InputSystem::DigitalAction digitalAction, bool value) {

}

void InputSystem::setAction(InputSystem::AnalogAction analogAction, FVec2 value) {

}
