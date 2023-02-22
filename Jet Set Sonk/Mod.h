#pragma once

void ReadConfig(const char* path, const HelperFunctions& helperFunctions);

extern std::string modName;
extern std::string modpath;
extern HelperFunctions HelperFunctionsGlobal;
void init_chrModel();
void SonicJVList();
void initAnims();