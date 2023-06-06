#pragma once
#ifndef RISE_SMOG_H
#define RISE_SMOG_H

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#include <cstdbool>
extern "C" {
#else // __cplusplus
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#endif // __cplusplus

// idfk
#define STEAMINPUT_INTERFACE_VERSION "SteamInput006"

#define SMOG_IN
#define SMOG_OUT

    typedef uint64_t SMOG_AnalogActionHandle;
    typedef uint64_t SMOG_DigitalActionHandle;
    typedef uint64_t SMOG_ActionSetHandle;
    // Somewhat of a generic name; this refers to a controller, basically.
    typedef uint64_t SMOG_InputHandle;

// parallel to STEAM_INPUT_MAX_COUNT
#define SMOG_MAX_INPUT_HANDLES 16

    typedef struct SMOG_AnalogActionData {
        // The current state of this action; will be delta updates for mouse actions
        float x, y;

        // Whether this action is currently available to be bound in the active action set
        bool bActive;
    } SMOG_AnalogActionData;

    typedef struct SMOG_DigitalActionData {
        // The current state of this action; will be true if currently pressed
        bool bState;

        // Whether this action is currently available to be bound in the active action set
        bool bActive;
    } SMOG_DigitalActionData;

    SMOG_AnalogActionHandle     SMOG_GetAnalogActionHandle  (SMOG_IN const char *analogActionName                                                       );
    SMOG_DigitalActionHandle    SMOG_GetDigitalActionHandle (SMOG_IN const char *digitalActionName                                                      );
    SMOG_ActionSetHandle        SMOG_GetActionSetHandle     (SMOG_IN const char *actionSetName                                                          );

    SMOG_AnalogActionData       SMOG_GetAnalogActionData    (SMOG_IN SMOG_InputHandle inputHandle, SMOG_IN SMOG_AnalogActionHandle analogActionHandle   );
    SMOG_DigitalActionData      SMOG_GetDigitalActionData   (SMOG_IN SMOG_InputHandle inputHandle, SMOG_IN SMOG_DigitalActionHandle digitalActionHandle );

    // Writes an array with size SMOG_MAX_INPUT_HANDLES of input handles to the provided address, and returns the amount of controllers connected.
    int                         SMOG_GetConnectedControllers(SMOG_OUT SMOG_InputHandle* handlesOut                                                      );
    void                        SMOG_ActivateActionSet      (SMOG_IN SMOG_InputHandle inputHandle, SMOG_IN SMOG_ActionSetHandle actionSetHandle         );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // RISE_SMOG_H
