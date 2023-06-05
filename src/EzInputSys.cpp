#include "EzInputSys.h"
#include <steam/steam_api.h>
#include <steam/isteaminput.h>

using namespace std;

static SDL_GameController*          activeGameController = nullptr;
static InputHandle_t                activeSteamControllerHandle;
static InputActionSetHandle_t       actionSetHandles    [(size_t)InputSystem::ActionSet::NumSets        ];
static InputAnalogActionHandle_t    analogActionHandles [(size_t)InputSystem::AnalogAction::NumActions  ];
static InputDigitalActionHandle_t   digitalActionHandles[(size_t)InputSystem::DigitalAction::NumActions ];

void InputSystem::init() {
    // Digital actions
    digitalActionHandles[(size_t)InputSystem::DigitalAction::Jump           ] = SteamInput()->GetDigitalActionHandle("jump");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::PauseMenu      ] = SteamInput()->GetDigitalActionHandle("pause_menu");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuUp         ] = SteamInput()->GetDigitalActionHandle("menu_up");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuDown       ] = SteamInput()->GetDigitalActionHandle("menu_down");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuLeft       ] = SteamInput()->GetDigitalActionHandle("menu_left");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuRight      ] = SteamInput()->GetDigitalActionHandle("menu_right");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuSelect     ] = SteamInput()->GetDigitalActionHandle("menu_select");
    digitalActionHandles[(size_t)InputSystem::DigitalAction::MenuCancel     ] = SteamInput()->GetDigitalActionHandle("menu_cancel");
    // Analog actions
    analogActionHandles[(size_t)InputSystem::AnalogAction::AnalogControls   ] = SteamInput()->GetAnalogActionHandle ( "analog_controls");
    // Action set handles
    actionSetHandles[(size_t)InputSystem::ActionSet::GameControls           ] = SteamInput()->GetActionSetHandle("ship_controls");
    actionSetHandles[(size_t)InputSystem::ActionSet::MenuControls           ] = SteamInput()->GetActionSetHandle("menu_controls");
}

void InputSystem::update() {
    // TODO: this is old code, clean it up
    inputHandleCount = SteamInput()->GetConnectedControllers(inputHandles);
    if (inputHandleCount != lastInputHandleCount) {
        lastInputHandleCount = inputHandleCount;
        updateInputHandles(); // Required for connecting controllers after game launch
    }
    SteamInput()->RunFrame();
    for (int i = 0; i < STEAM_INPUT_MAX_COUNT; i++) {
        if (inputHandles[i] == 0) continue; // Skip invalid handles
        SteamInput()->ActivateActionSet(inputHandles[i], actionSet);
        // TODO: replace with for(:), this should be more dynamic
        InputAnalogActionData_t gyroData = SteamInput()->GetAnalogActionData(inputHandles[i], TiltCube);
        InputDigitalActionData_t resetData = SteamInput()->GetDigitalActionData(inputHandles[i], ResetCamera);
    }
}