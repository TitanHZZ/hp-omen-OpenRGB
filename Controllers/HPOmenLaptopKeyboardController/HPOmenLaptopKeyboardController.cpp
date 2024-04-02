#ifdef _WIN32

#include "HPOmenLaptopKeyboardController.h"

HPOmenLaptopKeyboardController::HPOmenLaptopKeyboardController()
{   /*---------------------------------------------------------*\
    | Load C# Dll                                               |
    \*---------------------------------------------------------*/
    this->lib = LoadLibrary(TEXT("OmenFourZoneLighting.dll"));

    if (!lib) {
        return;
    }

    /*---------------------------------------------------------*\
    | Get C# Dll functions addrs                                |
    \*---------------------------------------------------------*/
    this->pSetZoneColors = (SetZoneColorsType)GetProcAddress(lib, "SetZoneColors");
    this->pIsLightingSupported = (IsLightingSupportedType)GetProcAddress(lib, "IsLightingSupported");
    this->pGetKeyboardType = (GetKeyboardTypeType)GetProcAddress(lib, "GetKeyboardType");
    this->pSetFnF4Status = (SetFnF4StatusType)GetProcAddress(lib, "SetFnF4Status");
}

HPOmenLaptopKeyboardController::~HPOmenLaptopKeyboardController()
{   /*---------------------------------------------------------*\
    | Unload C# Dll                                             |
    \*---------------------------------------------------------*/
    FreeLibrary(lib);
}

int HPOmenLaptopKeyboardController::checkSupport()
{
    /*---------------------------------------------------------*\
    | Check if something went wrong loading the Dll or          |
    | some of its functions                                     |
    \*---------------------------------------------------------*/
    if (!lib || !pSetZoneColors || !pIsLightingSupported || !pGetKeyboardType || !pSetFnF4Status) {
        return 0;
    }

    return pIsLightingSupported() && (KeyboardType)pGetKeyboardType() == KeyboardType::WITHOUT_NUMPAD;
}

#endif
