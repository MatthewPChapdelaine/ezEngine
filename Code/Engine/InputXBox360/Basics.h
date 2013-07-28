#pragma once

#include <Core/Input/InputManager.h>

// Configure the DLL Import/Export Define
#if EZ_ENABLED(EZ_COMPILE_ENGINE_AS_DLL)
  #ifdef BUILDSYSTEM_BUILDING_INPUTXBOX360_LIB
    #define EZ_INPUTXBOX360_DLL __declspec(dllexport)
    #define EZ_INPUTXBOX360_TEMPLATE
  #else
    #define EZ_INPUTXBOX360_DLL __declspec(dllimport)
    #define EZ_INPUTXBOX360_TEMPLATE extern
  #endif
#else
  #define EZ_INPUTXBOX360_DLL
  #define EZ_INPUTXBOX360_TEMPLATE
#endif
