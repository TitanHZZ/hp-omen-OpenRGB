#pragma once
#include <stdio.h>

typedef unsigned char byte;

enum KeyboardType
{
    NORMAL,
    WITH_NUMPAD,
    WITHOUT_NUMPAD,
    RGB
};

enum KeyboardMode
{
    OFF,
    DIRECT
};

class HPOmenLaptopKeyboardLinuxController
{
private:
    FILE *fp;
public:
    HPOmenLaptopKeyboardLinuxController();
    ~HPOmenLaptopKeyboardLinuxController();

    /*---------------------------------------------------------*\
    | For use with the detector                                 |
    \*---------------------------------------------------------*/
    int checkSupport();

    /*---------------------------------------------------------*\
    | Functions definitions                                     |
    \*---------------------------------------------------------*/
    void SetZoneColors(unsigned int zone1, unsigned int zone2, unsigned int zone3, unsigned int zone4);
    bool IsLightingSupported();
    int  GetKeyboardType();
    void SetFnF4Status(bool enable);
};

