#include "pch.h"

NJS_TEXNAME MissionCardsTex[2]{ NULL };

static FunctionHook<void> MissionCard_Result_t(0x457BB0);
static FunctionHook<void> LoadMissionImage_t(0x457450);

void SetMissionCardTexture()
{
	StageMissionTexlist.textures = MissionCardsTex;
	StageMissionTexlist.nbTexture = 1;
	LoadPVM("missionCards", &StageMissionTexlist);
	MissionSpriteAnim.texid = hardMode ? 1 : 0;
}

void MissionCard_Result_r()
{
	if (!isTagLevel() || CurrentCharacter != Characters_Sonic)
	{
		MissionSpriteAnim.texid = 0;
		return MissionCard_Result_t.Original();
	}

	//edit the texlist of the mission card to make it use our card instead
	SetMissionCardTexture(); 

	//load the task which will diplay the mission card
	task* tp = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
	tp->twp->mode = 0;
	tp->twp->counter.b[1] = GetPlayerNumber();
	tp->twp->wtimer = (MissedFrames_B * 72.0f);
	tp->twp->pos.x = 320.0f;
	tp->twp->pos.y = 240.0f;
	tp->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void LoadMissionImage_r()
{
	if (!isTagLevel() || CurrentCharacter != Characters_Sonic)
	{
		MissionSpriteAnim.texid = 0;
		return LoadMissionImage_t.Original();
	}

	//edit the texlist of the mission card to make it use our card instead
	SetMissionCardTexture();

	//load the task which will diplay the mission card
	task* task = CreateElementalTask(LoadObj_Data1, 6, (TaskFuncPtr)0x457B60);
	task->twp->mode = 0;
	task->twp->counter.b[1] = GetPlayerNumber();
	task->twp->wtimer = 120;
	task->twp->pos.x = 320.0f;
	task->twp->pos.y = 360.0f;
	task->dest = (TaskFuncPtr)FreeStageMissionImage;
}

void initMissionsCardsHack()
{
	if (!tagLvl)
		return;

	MissionCard_Result_t.Hook(MissionCard_Result_r);
	LoadMissionImage_t.Hook(LoadMissionImage_r);
}