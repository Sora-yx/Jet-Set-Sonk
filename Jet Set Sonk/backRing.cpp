#include "pch.h"
#include "tags.h"
#include "UsercallFunctionHandler.h"

extern NJS_OBJECT object_GoalRing;
extern NJS_TEXLIST GoalRingTextures;

UsercallFuncVoid(SHACT2_Trigger_t, (task* a1), (a1), 0x610050, rEAX);
TaskHook SHACT3_Trigger_t(0x610300);

int getPlayerStartRot()
{
	for (uint16_t i = 0; i < SonicStartArray.size(); i++)
	{
		if (SonicStartArray[i].LevelID == CurrentLevel && SonicStartArray[i].ActID == CurrentAct)
		{
			return SonicStartArray[i].YRot;
		}
	}

	return 0x0;
}

NJS_POINT3 getPlayerStartPos()
{
	for (uint16_t i = 0; i < SonicStartArray.size(); i++)
	{
		if (SonicStartArray[i].LevelID == CurrentLevel && SonicStartArray[i].ActID == CurrentAct)
		{
			return SonicStartArray[i].Position;
		}
	}

	return { -1, -1, -1 };
}

void BackRingDisp(task* tp)
{
	auto twp = tp->twp;

	if (!MissedFrames)
	{
		njSetTexture(&GoalRingTextures);
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		njRotateY(0, twp->ang.y);
		DrawObject(&object_GoalRing);
		njPopMatrix(1);
	}
}

bool useBackRing = false;
void BackRing(task* tp)
{
	if (CheckRangeOut(tp))
		return;

	auto twp = tp->twp;

	if (tagsLeft[CurrentAct] <= 0)
	{
		twp->mode = 3;
	}


	switch (twp->mode)
	{
	case 0:
		twp->pos.y += 35.0f;
		tp->disp = BackRingDisp;
		twp->mode++;
		break;
	case 1:

		twp->ang.y += 300;

		if (CheckCollisionP(&twp->pos, 40.0f))
		{
			for (uint8_t i = 0; i < pMax; i++)
			{
				if (playertwp[i])
				{
					DisableControl();
					CharColliOff(playertwp[i]);
					PClearSpeed(playermwp[i], playerpwp[i]);
				}
			}

			useBackRing = true;
			CreateElementalTask(LoadObj_Data1, 1, FadeoutScreen);
			twp->mode++;
		}
		break;
	case 2:
		twp->ang.y += 300;

		if (++twp->wtimer == 30)
		{
			for (uint8_t i = 0; i < pMax; i++)
			{
				if (playertwp[i])
				{
					playertwp[i]->pos = getPlayerStartPos();
					playertwp[i]->ang.y = getPlayerStartRot();

				}
			}
			twp->mode++;
		}
		break;
	}

	if (tp->disp && twp->mode < 3)
		tp->disp(tp);
}

void SHACT2_Trigger_r(task* tp)
{
	if (isTagLevel() && CurrentCharacter == Characters_Sonic)
	{
		if (tagsLeft[CurrentAct] > 0)
		{
			return;
		}
	}

	SHACT2_Trigger_t.Original(tp);
}

void SHACT3_Trigger_r(task* tp)
{
	if (isTagLevel() && CurrentCharacter == Characters_Sonic)
	{
		if (tagsLeft[CurrentAct] > 0)
		{
			return;
		}
	}

	SHACT3_Trigger_t.Original(tp);
}

void init_BackRing()
{
	SHACT2_Trigger_t.Hook(SHACT2_Trigger_r);
	SHACT3_Trigger_t.Hook(SHACT3_Trigger_r);
}