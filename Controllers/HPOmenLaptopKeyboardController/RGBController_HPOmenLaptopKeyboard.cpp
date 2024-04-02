#ifdef __WIN32

#include "RGBController_HPOmenLaptopKeyboard.h"

RGBController_HPOmenLaptopKeyboard::RGBController_HPOmenLaptopKeyboard(HPOmenLaptopKeyboardController* controller_ptr)
{
    this->controller = controller_ptr;

    this->name = "HP Omen 15";
    this->vendor = "HP";
    this->description = "HP Omen 15 Keyboard Device";
    this->location = "ROOT\WMI:hpqBIntM";
    this->type = DEVICE_TYPE_KEYBOARD;

    mode Direct;
    Direct.name = "Direct";
    Direct.value = KeyboardMode::DIRECT;
    Direct.flags = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode = MODE_COLORS_PER_LED;
    Direct.brightness = 255;
    Direct.brightness_min = 0;
    Direct.brightness_max = 255;
    this->modes.push_back(Direct);

    mode Off;
    Off.name = "Off";
    Off.value = KeyboardMode::OFF;
    Off.flags = 0;
    Off.color_mode = MODE_COLORS_NONE;
    Off.brightness = 0;
    Off.brightness_min = 0;
    Off.brightness_max = 0;
    this->modes.push_back(Off);

    SetupZones();
}

RGBController_HPOmenLaptopKeyboard::~RGBController_HPOmenLaptopKeyboard()
{
    delete controller;
}

void RGBController_HPOmenLaptopKeyboard::SetupZones()
{
    /*---------------------------------------------------------*\
    | Set up zones                                              |
    \*---------------------------------------------------------*/
    zone keyboard_zone;
    keyboard_zone.leds_count = 4;
    keyboard_zone.leds_min = 0;
    keyboard_zone.leds_max = 4;
    keyboard_zone.name = "Keyboard";
    keyboard_zone.matrix_map = NULL;
    keyboard_zone.type = ZONE_TYPE_LINEAR;
    this->zones.push_back(keyboard_zone);

    /*---------------------------------------------------------*\
    | Set up LEDs                                               |
    \*---------------------------------------------------------*/
    led zone1_leds;
    zone1_leds.name = "Zone 1";
    zone1_leds.value = 0;
    this->leds.push_back(zone1_leds);

    led zone2_leds;
    zone2_leds.name = "Zone 2";
    zone2_leds.value = 0;
    this->leds.push_back(zone2_leds);

    led zone3_leds;
    zone3_leds.name = "Zone 3";
    zone3_leds.value = 0;
    this->leds.push_back(zone3_leds);

    led zone4_leds;
    zone4_leds.name = "Zone 4";
    zone4_leds.value = 0;
    this->leds.push_back(zone4_leds);

    SetupColors();
}

void RGBController_HPOmenLaptopKeyboard::ResizeZone(int zone, int new_size)
{
    /*---------------------------------------------------------*\
    | Not Supported                                             |
    \*---------------------------------------------------------*/
}

void RGBController_HPOmenLaptopKeyboard::DeviceUpdateLEDs()
{
    /*---------------------------------------------------------*\
    | brg to rgb                                                |
    \*---------------------------------------------------------*/
    unsigned int color_zone1 = ((colors[0] & 0x00FF0000) >> 0x10) | ((colors[0] & 0x000000FF) << 0x10) | (colors[0] & 0x0000FF00) | 0xFF000000;
    unsigned int color_zone2 = ((colors[1] & 0x00FF0000) >> 0x10) | ((colors[1] & 0x000000FF) << 0x10) | (colors[1] & 0x0000FF00) | 0xFF000000;
    unsigned int color_zone3 = ((colors[2] & 0x00FF0000) >> 0x10) | ((colors[2] & 0x000000FF) << 0x10) | (colors[2] & 0x0000FF00) | 0xFF000000;
    unsigned int color_zone4 = ((colors[3] & 0x00FF0000) >> 0x10) | ((colors[3] & 0x000000FF) << 0x10) | (colors[3] & 0x0000FF00) | 0xFF000000;

    controller->pSetZoneColors(color_zone1, color_zone2, color_zone3, color_zone4);
}

void RGBController_HPOmenLaptopKeyboard::UpdateZoneLEDs(int zone)
{
    DeviceUpdateLEDs();
}

void RGBController_HPOmenLaptopKeyboard::UpdateSingleLED(int led)
{
    DeviceUpdateLEDs();
}

void RGBController_HPOmenLaptopKeyboard::DeviceUpdateMode()
{
    if (modes[active_mode].value == KeyboardMode::OFF) {
        controller->pSetFnF4Status(false);
    } else {
        controller->pSetFnF4Status(true);
    }
}

#endif
