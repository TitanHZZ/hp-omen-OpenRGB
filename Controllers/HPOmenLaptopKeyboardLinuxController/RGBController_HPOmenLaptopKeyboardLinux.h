#pragma once

#include "RGBController.h"
#include "HPOmenLaptopKeyboardLinuxController.h"

class RGBController_HPOmenLaptopKeyboardLinux : public RGBController
{
public:
    RGBController_HPOmenLaptopKeyboardLinux(HPOmenLaptopKeyboardLinuxController* controller_ptr);
    virtual ~RGBController_HPOmenLaptopKeyboardLinux();

    void            SetupZones() override;

    void            ResizeZone(int zone, int new_size) override; /* Not supported */

    void            DeviceUpdateLEDs() override;
    void            UpdateZoneLEDs(int zone) override;
    void            UpdateSingleLED(int led) override; /* Not supported */

    void            DeviceUpdateMode() override;

private:
    HPOmenLaptopKeyboardLinuxController* controller;
};

