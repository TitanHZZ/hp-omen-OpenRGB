#include "Detector.h"
#include "EVisionKeyboardController.h"
#include "EVisionV2KeyboardController.h"
#include "RGBController.h"
#include "RGBController_EVisionKeyboard.h"
#include "RGBController_EVisionV2Keyboard.h"
#include "SettingsManager.h"
#include <vector>
#include <hidapi/hidapi.h>

/*-----------------------------------------------------*\
| Keyboard product IDs                                  |
\*-----------------------------------------------------*/
#define EVISION_KEYBOARD_VID        0x0C45
#define EVISION_KEYBOARD2_VID       0x320F
#define EVISION_KEYBOARD_USAGE_PAGE 0xFF1C
#define GLORIOUS_GMMK_TKL_PID       0x5064
#define REDRAGON_K550_PID           0x5204
#define REDRAGON_K552_PID           0x5104
#define REDRAGON_K552_V2_PID        0x5000
#define REDRAGON_K556_PID           0x5004
#define TECWARE_PHANTOM_ELITE_PID   0x652F
#define WARRIOR_KANE_TC235          0x8520
#define WOMIER_K87_PID              0x502A
#define WOMIER_K66_PID              0x7698
#define BYGG_CSB_ICL01_PID          0x5041

/******************************************************************************************\
*                                                                                          *
*   DetectEVisionKeyboards                                                                 *
*                                                                                          *
*       Tests the USB address to see if an EVision RGB Keyboard controller exists there.   *
*                                                                                          *
\******************************************************************************************/

void DetectEVisionKeyboards(hid_device_info* info, const std::string& /*name*/)
{
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        EVisionKeyboardController* controller         = new EVisionKeyboardController(dev, info->path);
        RGBController_EVisionKeyboard* rgb_controller = new RGBController_EVisionKeyboard(controller);
        rgb_controller->name = "EVision Keyboard";
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

void DetectEVisionV2Keyboards(hid_device_info* info, const std::string& name)
{
    json settings   = ResourceManager::get()->GetSettingsManager()->GetSettings("EVision2Settings");
    hid_device* dev = hid_open_path(info->path);

    if(dev)
    {
        EVisionV2KeyboardController*    controller      = new EVisionV2KeyboardController(dev, info->path);

        RGBController_EVisionV2Keyboard* rgb_controller = new RGBController_EVisionV2Keyboard(controller, EVISION_V2_KEYBOARD_PART_KEYBOARD);
        rgb_controller->name                            = name;
        ResourceManager::get()->RegisterRGBController(rgb_controller);

        if(!settings.contains("AdditionalZones") || settings["AdditionalZones"] == true)
        {
            rgb_controller = new RGBController_EVisionV2Keyboard(controller, EVISION_V2_KEYBOARD_PART_LOGO);
            rgb_controller->name = name;
            rgb_controller->name += " Logo";
            ResourceManager::get()->RegisterRGBController(rgb_controller);

            rgb_controller        = new RGBController_EVisionV2Keyboard(controller, EVISION_V2_KEYBOARD_PART_EDGE);
            rgb_controller->name  = name;
            rgb_controller->name += " Edge";
            ResourceManager::get()->RegisterRGBController(rgb_controller);
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------------*\
| Keyboards                                                                                                                                     |
\*---------------------------------------------------------------------------------------------------------------------------------------------*/
REGISTER_HID_DETECTOR_IP("EVision Keyboard 0C45:5204", DetectEVisionKeyboards,   EVISION_KEYBOARD_VID,  REDRAGON_K550_PID,         1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 0C45:5104", DetectEVisionKeyboards,   EVISION_KEYBOARD_VID,  REDRAGON_K552_PID,         1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 320F:5000", DetectEVisionKeyboards,   EVISION_KEYBOARD2_VID, REDRAGON_K552_V2_PID,      1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 0C45:5004", DetectEVisionKeyboards,   EVISION_KEYBOARD_VID,  REDRAGON_K556_PID,         1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 0C45:652F", DetectEVisionKeyboards,   EVISION_KEYBOARD_VID,  TECWARE_PHANTOM_ELITE_PID, 1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 0C45:8520", DetectEVisionKeyboards,   EVISION_KEYBOARD_VID,  WARRIOR_KANE_TC235,        1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 320F:502A", DetectEVisionKeyboards,   EVISION_KEYBOARD2_VID, WOMIER_K87_PID,            1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 0C45:7698", DetectEVisionKeyboards,   EVISION_KEYBOARD_VID,  WOMIER_K66_PID,            1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("EVision Keyboard 320F:5064", DetectEVisionKeyboards,   EVISION_KEYBOARD2_VID, GLORIOUS_GMMK_TKL_PID,     1, EVISION_KEYBOARD_USAGE_PAGE);
REGISTER_HID_DETECTOR_IP("CSB/ICL01 Keyboard",         DetectEVisionV2Keyboards, EVISION_KEYBOARD2_VID, BYGG_CSB_ICL01_PID,        1, EVISION_KEYBOARD_USAGE_PAGE);
