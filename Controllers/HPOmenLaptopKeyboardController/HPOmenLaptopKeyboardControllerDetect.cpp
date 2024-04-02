#ifdef __WIN32

#include "Detector.h"
#include "RGBController.h"
#include "RGBController_HPOmenLaptopKeyboard.h"
#include "HPOmenLaptopKeyboardController.h"

/******************************************************************************************\
*                                                                                          *
*   DetectHPOmenLaptopKeyboardControllers                                                  *
*                                                                                          *
*       Checks if the wmi class for the keyboard exists.                                   *
*                                                                                          *
\******************************************************************************************/

void DetectHPOmenLaptopKeyboardControllers()
{
    HPOmenLaptopKeyboardController* controller = new HPOmenLaptopKeyboardController();

    /*---------------------------------------------------------*\
    | Check if the device is supported by this driver           |
    \*---------------------------------------------------------*/
    if (!controller->checkSupport()) {
        delete controller;
        return;
    }

    RGBController* new_controller = new RGBController_HPOmenLaptopKeyboard(controller);
    ResourceManager::get()->RegisterRGBController(new_controller);
}

REGISTER_DETECTOR("Omen Laptop Keyboard WMI", DetectHPOmenLaptopKeyboardControllers);

#endif
