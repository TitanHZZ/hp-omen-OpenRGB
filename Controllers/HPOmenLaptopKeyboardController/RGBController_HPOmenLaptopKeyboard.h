#pragma once

#ifdef __WIN32

#include "HPOmenLaptopKeyboardController.h"
#include "RGBController.h"

class RGBController_HPOmenLaptopKeyboard : public RGBController
{
public:
    RGBController_HPOmenLaptopKeyboard(HPOmenLaptopKeyboardController* controller_ptr);
    virtual ~RGBController_HPOmenLaptopKeyboard();

    void            SetupZones() override;

    void            ResizeZone(int zone, int new_size) override; /* Not supported */

    void            DeviceUpdateLEDs() override;
    void            UpdateZoneLEDs(int zone) override;
    void            UpdateSingleLED(int led) override; /* Not supported */

    void            DeviceUpdateMode() override;

private:
    HPOmenLaptopKeyboardController* controller;
};

#endif
