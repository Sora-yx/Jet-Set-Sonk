#include "pch.h"

FunctionHook<void> InitSonicAnimData_t(InitSonicAnimData); 
TaskHook SonicExec_t(SonicTheHedgehog);

AnimationFile* walk3Anm = nullptr;
AnimationFile* run1Anm = nullptr;
AnimationFile* run2Anm = nullptr;

static const char animEdited = 3;
NJS_MOTION BackupMotion[animEdited];
AnimData BackupAnimData[animEdited];

//since Metal sonic and Sonic share the same anims, we have to restore them when the player use Metal
void restoreAnims()
{
	SONIC_ACTIONS[5]->motion = &BackupMotion[0];
	SONIC_ACTIONS[6]->motion = &BackupMotion[1];
	SONIC_ACTIONS[18]->motion = &BackupMotion[2];

	memcpy(&SonicAnimData[11], BackupAnimData, sizeof(AnimData) * animEdited);
}

void backupAnims()
{
	BackupMotion[0] = *SONIC_ACTIONS[5]->motion;
	BackupMotion[1] = *SONIC_ACTIONS[6]->motion;
	BackupMotion[2] = *SONIC_ACTIONS[18]->motion;

	memcpy(BackupAnimData, &SonicAnimData[11], sizeof(AnimData) * animEdited);	
}

void SetNewAnims()
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

void SonicExec_r(task* tp)
{
	auto twp = tp->twp;

	if (!twp->mode)
	{
		if (MetalSonicFlag)
			restoreAnims();
		else
			SetNewAnims();
	}

	SonicExec_t.Original(tp);
}

void InitSonkAnimData_r()
{
	InitSonicAnimData_t.Original(); //we let the game set all the anims in the list and then we edit them

	if (walk3Anm)
	{
		backupAnims();
		SetNewAnims();
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
		SonicExec_t.Hook(SonicExec_r);
	}
}