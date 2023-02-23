#include "pch.h"

FunctionHook<void> InitSonicAnimData_t(InitSonicAnimData); 

AnimationFile* walk3Anm = nullptr;
AnimationFile* run1Anm = nullptr;
AnimationFile* run2Anm = nullptr;


void InitSonkAnimData_r()
{
	InitSonicAnimData_t.Original(); //we let the game set all the anims in the list and then we edit them

	if (walk3Anm)
	{
		//replace walk and run anim with skating from SA2 Shadow.
		SONIC_ACTIONS[5]->motion = walk3Anm->getmotion();
		SONIC_ACTIONS[6]->motion = run1Anm->getmotion();
		SONIC_ACTIONS[18]->motion = run2Anm->getmotion();

		//adjust skate anim speed so it doesn't look goofy
		SonicAnimData[11].AnimationSpeed = 0.12f;
		SonicAnimData[11].TransitionSpeed = 0.25f;
		SonicAnimData[12].AnimationSpeed = 0.15f;
		SonicAnimData[12].TransitionSpeed = 0.25f;
		SonicAnimData[13].AnimationSpeed = 0.2f;
		SonicAnimData[13].TransitionSpeed = 0.5f;
	}
}

void initAnims()
{
	walk3Anm = LoadAnim("005");
	run1Anm = LoadAnim("006");
	run2Anm = LoadAnim("018");

	if (walk3Anm)
	{
		InitSonicAnimData_t.Hook(InitSonkAnimData_r);
	}
}