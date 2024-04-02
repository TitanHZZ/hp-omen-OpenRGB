#pragma once

#ifdef _WIN32

#include <Windows.h>

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

class HPOmenLaptopKeyboardController
{
private:
    /*---------------------------------------------------------*\
    | C# Dll functions definitions                              |
    \*---------------------------------------------------------*/
    typedef void(__cdecl *SetZoneColorsType)(unsigned int zone1, unsigned int zone2, unsigned int zone3, unsigned int zone4);
    typedef bool(__cdecl *IsLightingSupportedType)();
    typedef int (__cdecl *GetKeyboardTypeType)();
    typedef void(__cdecl *SetFnF4StatusType)(bool enable);

    /*---------------------------------------------------------*\
    | C# Dll pointer                                            |
    \*---------------------------------------------------------*/
    HMODULE lib;

public:
    HPOmenLaptopKeyboardController();
    ~HPOmenLaptopKeyboardController();

    /*---------------------------------------------------------*\
    | For use with the detector                                 |
    \*---------------------------------------------------------*/
    int checkSupport();

    /*---------------------------------------------------------*\
    | C# Dll lib functions pointers                             |
    \*---------------------------------------------------------*/
    SetZoneColorsType pSetZoneColors;
    IsLightingSupportedType pIsLightingSupported;
    GetKeyboardTypeType pGetKeyboardType;
    SetFnF4StatusType pSetFnF4Status;
};

#endif
