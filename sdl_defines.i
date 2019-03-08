%define SDL_BUTTON_LEFT     1
%enddef
%define SDL_BUTTON_MIDDLE   2
%enddef
%define SDL_BUTTON_RIGHT    3
%enddef
%define SDL_BUTTON_X1       4
%enddef

%{
#include <SDL_scancode.h>
typedef enum EE_Enum
{    /* Joystick events */
    EE_JOYAXISMOTION  = 0x600, /**< Joystick axis motion */
    EE_JOYBALLMOTION,          /**< Joystick trackball motion */
    EE_JOYHATMOTION,           /**< Joystick hat position change */
    EE_JOYBUTTONDOWN,          /**< Joystick button pressed */
    EE_JOYBUTTONUP,            /**< Joystick button released */
    EE_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
    EE_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

    /* Game controller events */
    EE_CONTROLLERAXISMOTION  = 0x650, /**< Game controller axis motion */
    EE_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
    EE_CONTROLLERBUTTONUP,            /**< Game controller button released */
    EE_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
    EE_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
    EE_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

    /* Touch events */
    EE_FINGERDOWN      = 0x700,
    EE_FINGERUP,
    EE_FINGERMOTION,

    /* Gesture events */
    EE_DOLLARGESTURE   = 0x800,
    EE_DOLLARRECORD,
    EE_MULTIGESTURE,
};

%}

%include "Dependencies\SDL2-2.0.0\include\SDL_scancode.h"