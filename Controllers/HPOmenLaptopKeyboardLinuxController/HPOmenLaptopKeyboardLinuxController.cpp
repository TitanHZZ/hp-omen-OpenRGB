#include "HPOmenLaptopKeyboardLinuxController.h"
#include <stdio.h>
#include <unistd.h>
#include "QDebug"

HPOmenLaptopKeyboardLinuxController::HPOmenLaptopKeyboardLinuxController() {}
HPOmenLaptopKeyboardLinuxController::~HPOmenLaptopKeyboardLinuxController() {}

int HPOmenLaptopKeyboardLinuxController::checkSupport()
{
    /*---------------------------------------------------------*\
    | Check if the file 'omendrv0' exists                       |
    | If it does, the kernel supports this device               |
    \*---------------------------------------------------------*/
    return access("/dev/omendrv0", F_OK) == 0;
}

void HPOmenLaptopKeyboardLinuxController::SetZoneColors(unsigned int zone1, unsigned int zone2, unsigned int zone3, unsigned int zone4)
{   
    /*---------------------------------------------------------*\
    | Open driver file                                          |
    \*---------------------------------------------------------*/
    FILE *f = fopen("/dev/omendrv0", "w");

    if (f) {
        /*---------------------------------------------------------*\
        | Set the new color                                         |
        \*---------------------------------------------------------*/
        fprintf(f, "%03u%03u%03u%03u%03u%03u%03u%03u%03u%03u%03u%03u", (byte)(zone1 & 0x000000FF), (byte)((zone1 & 0x0000FF00) >> 0x08), (byte)((zone1 & 0x00FF0000) >> 0x10),
                                                                       (byte)(zone2 & 0x000000FF), (byte)((zone2 & 0x0000FF00) >> 0x08), (byte)((zone2 & 0x00FF0000) >> 0x10),
                                                                       (byte)(zone3 & 0x000000FF), (byte)((zone3 & 0x0000FF00) >> 0x08), (byte)((zone3 & 0x00FF0000) >> 0x10),
                                                                       (byte)(zone4 & 0x000000FF), (byte)((zone4 & 0x0000FF00) >> 0x08), (byte)((zone4 & 0x00FF0000) >> 0x10));

        /*---------------------------------------------------------*\
        | Close driver file                                         |
        \*---------------------------------------------------------*/
        fclose(f);
    }
}

bool HPOmenLaptopKeyboardLinuxController::IsLightingSupported()
{
    return checkSupport();
}

int HPOmenLaptopKeyboardLinuxController::GetKeyboardType()
{
    if (checkSupport()) {
        return KeyboardType::WITHOUT_NUMPAD;
    }
}

void HPOmenLaptopKeyboardLinuxController::SetFnF4Status(bool enable)
{
    // TODO --> implement fnf4 status control in the linux driver

    /*---------------------------------------------------------*\
    | Not supported in the linux driver yet                     |
    \*---------------------------------------------------------*/
}
