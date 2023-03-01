#pragma once


#define TaskHook static FunctionHook<void, task*>

constexpr char pMax = 8;
constexpr char actMax = 8;

void ReadConfig(const char* path, const HelperFunctions& helperFunctions);

extern std::string modName;
extern std::string modpath;
extern HelperFunctions HelperFunctionsGlobal;
void init_chrModel();
void SonicJVList();
void initAnims();
void initSkatingEffects();
void initSonkEff();
void init_SH();
