#include "pch.h"

std::vector<std::string>Subtitles;
std::vector<uint16_t>TimerSubtitles;
uint8_t actCount = 3;
uint8_t copCount = 4;
NJS_POINT3 goalPos[actMax]{ 0, 0, 0 };

void ReadInfo(const char* path, const HelperFunctions& helperFunction)
{
	const std::string iniPath = "SYSTEM\\info.ini";
	const auto originFilePath = HelperFunctionsGlobal.GetReplaceablePath(iniPath.c_str()); //used to make other mods able to replace the strings

	const std::string failed = modName + ": Failed to load mod info...\n";
	if (!IsPathExist(originFilePath))
	{
		PrintDebug(failed.c_str());
		return;
	}

	const IniFile* textIni = new IniFile(std::string(originFilePath));

	uint16_t count = 0;

	while (textIni->hasKey("Strings", std::to_string(count)))
	{
		Subtitles.push_back(textIni->getString("Strings", std::to_string(count)));
		count++;
	}	

	count = 0;

	while (textIni->hasKey("timerStrings", std::to_string(count)))
	{
		TimerSubtitles.push_back(textIni->getInt("timerStrings", std::to_string(count)));
		count++;
	}

	actCount = textIni->getInt("Level", "Act", actCount);
	copCount = textIni->getInt("Level", "cop", copCount);

	count = 0;
}

bool tagLvl = true;
bool hardMode = false;

void ReadModSettings(const char* path)
{
	const std::string failed = modName + ": Failed to load mod config...\n";
	if (!IsPathExist(std::string(path) + "\\config.ini"))
	{
		PrintDebug(failed.c_str());
		return;
	}

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");


	tagLvl = config->getBool("Main", "tagLvl", tagLvl);
	hardMode = config->getBool("Main", "hardMode", hardMode);

	delete config;
}


void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	ReadModSettings(path);
	ReadInfo(path, helperFunctions);
}