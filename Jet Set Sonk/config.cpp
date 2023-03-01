#include "pch.h"

std::vector<std::string>Subtitles;
std::vector<uint16_t>TimerSubtitles;
NJS_POINT3 goalPos[actMax]{ 0, 0, 0 };

void ReadInfo(const char* path, const HelperFunctions& helperFunction)
{
	const std::string iniPath = "SYSTEM\\info.ini";
	const auto originFilePath = HelperFunctionsGlobal.GetReplaceablePath(iniPath.c_str()); //used to make other mods able to replace the strings

	if (!IsPathExist(originFilePath))
	{
		PrintDebug("Failed to load mod info...\n");
		return;
	}

	const IniFile* textIni = new IniFile(std::string(originFilePath));

	uint16_t count = 0;

	while (textIni->hasKey("Strings", std::to_string(count)))
	{
		Subtitles.push_back(textIni->getString("Strings", std::to_string(count)));
		count++;
	}	

	uint16_t count2 = 0;

	while (textIni->hasKey("timerStrings", std::to_string(count2)))
	{
		TimerSubtitles.push_back(textIni->getInt("timerStrings", std::to_string(count2)));
		count2++;
	}
}

void ReadModSettings(const char* path)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	delete config;
}


void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	ReadModSettings(path);
	ReadInfo(path, helperFunctions);
}