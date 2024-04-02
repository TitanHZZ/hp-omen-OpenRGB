#include "Detector.h"
#include "RGBController.h"
#include "RGBController_HPOmenLaptopKeyboardLinux.h"
#include "HPOmenLaptopKeyboardLinuxController.h"

/******************************************************************************************\
*                                                                                          *
*   DetectHPOmenLaptopKeyboardControllers                                                  *
*                                                                                          *
*       Checks if the wmi class for the keyboard exists.                                   *
*                                                                                          *
\******************************************************************************************/

void DetectHPOmenLaptopKeyboardControllers()
{
    HPOmenLaptopKeyboardLinuxController* controller = new HPOmenLaptopKeyboardLinuxController();

    /*---------------------------------------------------------*\
    | Check if the device is supported by this driver           |
    \*---------------------------------------------------------*/
    if (!controller->checkSupport()) {
        delete controller;
        return;
    }

    RGBController* new_controller = new RGBController_HPOmenLaptopKeyboardLinux(controller);
    ResourceManager::get()->RegisterRGBController(new_controller);
}

REGISTER_DETECTOR("Omen Laptop Keyboard WMI", DetectHPOmenLaptopKeyboardControllers);
