/*-------------------------------------------------------------------*\
|  RoccatBurstProAirController.h                                      |
|                                                                     |
|  Driver for Roccat Burst Pro Air Mouse                              |
|                                                                     |
|  Morgan Guimard (morg)   6/16/2022                                  |
\*-------------------------------------------------------------------*/

#pragma once

#include "RGBController.h"
#include <hidapi/hidapi.h>

#define ROCCAT_BURST_PRO_AIR_REPORT_ID               0x06
#define ROCCAT_BURST_PRO_AIR_REPORT_SIZE             30
#define ROCCAT_BURST_PRO_AIR_PRO_NUMBER_OF_LEDS      4

enum
{
    ROCCAT_BURST_PRO_AIR_DIRECT_MODE_VALUE     = 0x01,
    ROCCAT_BURST_PRO_AIR_BLINK_MODE_VALUE      = 0x02,
    ROCCAT_BURST_PRO_AIR_BREATH_MODE_VALUE     = 0x03,
    ROCCAT_BURST_PRO_AIR_WAVE_MODE_VALUE       = 0x04
};

enum
{
    ROCCAT_BURST_PRO_AIR_BRIGHTNESS_MIN = 0x00,
    ROCCAT_BURST_PRO_AIR_BRIGHTNESS_MAX = 0xFF,
    ROCCAT_BURST_PRO_AIR_SPEED_MIN      = 0x00,
    ROCCAT_BURST_PRO_AIR_SPEED_MAX      = 0x0B
};

class RoccatBurstProAirController
{
public:
    RoccatBurstProAirController(hid_device* dev_handle, const hid_device_info& info);
    ~RoccatBurstProAirController();

    std::string     GetSerialString();
    std::string     GetDeviceLocation();
    std::string     GetFirmwareVersion();

    void            SetColors(std::vector<RGBColor> colors);
    void            SetModeValues(unsigned char mode_value, unsigned char speed, unsigned char brightness);

private:
    hid_device*     dev;
    std::string     location;
    std::string     serial_number;
    std::string     version;
};
