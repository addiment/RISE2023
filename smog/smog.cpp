#include "smog.h"
#include <steam/isteaminput.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

SMOG_AnalogActionHandle SMOG_GetAnalogActionHandle(SMOG_IN const char *analogActionName) {
    return (SMOG_AnalogActionHandle)SteamInput()->GetAnalogActionHandle(analogActionName);
}

SMOG_DigitalActionHandle SMOG_GetDigitalActionHandle(SMOG_IN const char *digitalActionName) {
    return (SMOG_DigitalActionHandle)SteamInput()->GetDigitalActionHandle(digitalActionName);
}

SMOG_ActionSetHandle SMOG_GetActionSetHandle(SMOG_IN const char *actionSetName) {
    return (SMOG_ActionSetHandle)SteamInput()->GetActionSetHandle(actionSetName);
}

SMOG_AnalogActionData SMOG_GetAnalogActionData(SMOG_IN SMOG_InputHandle inputHandle, SMOG_IN SMOG_AnalogActionHandle analogActionHandle) {
    InputAnalogActionData_t res = SteamInput()->GetAnalogActionData(
        (InputHandle_t)inputHandle,
        (InputAnalogActionHandle_t)analogActionHandle
    );
    return {
        res.x, res.y,
        res.bActive
    };
}

SMOG_DigitalActionData SMOG_GetDigitalActionData(SMOG_IN SMOG_InputHandle inputHandle, SMOG_IN SMOG_DigitalActionHandle digitalActionHandle) {
    InputDigitalActionData_t res = SteamInput()->GetDigitalActionData(
        (InputHandle_t)inputHandle,
        (InputDigitalActionHandle_t)digitalActionHandle
    );
    return {
        res.bState,
        res.bActive
    };
}

int SMOG_GetConnectedControllers(SMOG_OUT SMOG_InputHandle* handlesOut) {
    return SteamInput()->GetConnectedControllers((InputHandle_t*)handlesOut);
}

void SMOG_ActivateActionSet(SMOG_IN SMOG_InputHandle inputHandle, SMOG_IN SMOG_ActionSetHandle actionSetHandle) {
    SteamInput()->ActivateActionSet((InputHandle_t)inputHandle, (InputActionSetHandle_t)actionSetHandle);
}

#ifdef __cplusplus
}
#endif // __cplusplus