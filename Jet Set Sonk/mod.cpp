#include "pch.h"
#include "objects.h"
#include "jingle.h"

HelperFunctions HelperFunctionsGlobal;
std::string modpath;
std::string modName = "";
bool isAccessoryMod = false;

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{	
		modName = "Jet Set Sonk";

		if (helperFunctions.Version < 14)
		{
			MessageBox(WindowHandle,
				L"Error, your version of the mod loader does not support API version 14. Some functionality will not be available.\nPlease exit the game and update the mod loader for the best experience.",
				L"Jet Set Sonk Error: Mod Loader out of date", MB_OK | MB_ICONERROR);
		}

		isAccessoryMod = GetModuleHandle(L"CustomCharacters") != nullptr;

		HelperFunctionsGlobal = helperFunctions; // Save the helper pointer for external use
		modpath = path;
		ReadConfig(path, helperFunctions);
		init_chrModel();
		init_Sonk();
		init_SH();
		initSH_Objects();
		Sounds_Init();
		init_jingle(helperFunctions);
		init_HardMode();
		initMissionsCardsHack();
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		if (IsIngame())
		{
			RunCustomSounds();
		}

	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}