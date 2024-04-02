/*-----------------------------------------*\
|  AsusSagarisKeyboardController.h         |
|                                           |
|  Definitions and types for ASUS Sagaris  |
|  USB RGB lighting controller              |
|                                           |
|  Mola19 08/20/2023                        |
\*-----------------------------------------*/

#include "RGBController.h"

#include <string>
#include <vector>
#include <hidapi/hidapi.h>

#pragma once

enum
{
    SAGARIS_KEYBOARD_MODE_OFF           = 0,
    SAGARIS_KEYBOARD_MODE_STATIC        = 1,
    SAGARIS_KEYBOARD_MODE_SPRIAL        = 2,
    SAGARIS_KEYBOARD_MODE_CUSTOM        = 3,
    SAGARIS_KEYBOARD_MODE_BREATHING     = 4,
    SAGARIS_KEYBOARD_MODE_REACTIVE      = 5,
    SAGARIS_KEYBOARD_MODE_STARRY_NIGHT  = 6,
    SAGARIS_KEYBOARD_MODE_LASER         = 7,
};

enum
{
    SAGARIS_KEYBOARD_BRIGHTNESS_MIN     = 0,
    SAGARIS_KEYBOARD_BRIGHTNESS_MAX     = 3,
    SAGARIS_KEYBOARD_BRIGHTNESS_DEFAULT = 3
};

enum
{
    SAGARIS_KEYBOARD_SPEED_MIN     = 0,
    SAGARIS_KEYBOARD_SPEED_MAX     = 3,
    SAGARIS_KEYBOARD_SPEED_DEFAULT = 2
};

typedef struct
{
    uint8_t                 mode;
    uint8_t                 brightness;
    uint8_t                 speed;
    uint8_t                 colorIndex;
} sagaris_mode;


class AsusSagarisKeyboardController
{
public:
    AsusSagarisKeyboardController(hid_device* dev_handle, const char* path, unsigned short rev_version);
    ~AsusSagarisKeyboardController();

    std::string GetVersion();
    std::string GetDeviceLocation();
    std::string GetSerialString();

    sagaris_mode          GetMode();
    std::vector<RGBColor> GetColors();

    void SetMode(uint8_t mode, uint8_t brightness, uint8_t speed, uint8_t colorIndex);
    void SetColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

    void AwaitResponse(int ms);
    void ClearResponses();

private:
    hid_device*                 dev;
    std::string                 location;
    unsigned short              version;
};
