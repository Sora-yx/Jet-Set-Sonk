#include "pch.h"

HelperFunctions HelperFunctionsGlobal;
std::string modpath;
std::string modName = "";


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



		HelperFunctionsGlobal = helperFunctions; // Save the helper pointer for external use

		modpath = path;
		ReadConfig(path, helperFunctions);
		init_chrModel();

	}


	__declspec(dllexport) void __cdecl OnFrame()
	{

	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}