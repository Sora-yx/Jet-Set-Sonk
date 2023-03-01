#include "pch.h"
#include "objects.h"
#include "tags.h"

static constexpr uint8_t tagMdlCount = 3;

static ModelInfo* tagMdls[tagMdlCount]{ nullptr };
static ModelInfo* tagArrowMdl = nullptr;
extern uint8_t sprayPaintCount[];
uint8_t tagsLeft[actMax]{ 0 };
uint8_t tagCount{ 0 };
static uint8_t saveTexId[tagMdlCount];
bool isTagging = false;
NJS_POINT3 curTagPos[pMax];


void restoreGraffitiTexs()
{
	for (uint8_t i = 0; i < tagMdlCount; i++)
	{
		NJS_MODEL_SADX* mdl = (NJS_MODEL_SADX*)tagMdls[i]->getmodel()->model;

		mdl->mats[0].attr_texId = saveTexId[i];
	}
}

void saveGraffitiTexs()
{
	for (uint8_t i = 0; i < tagMdlCount; i++)
	{
		NJS_MODEL_SADX* mdl = (NJS_MODEL_SADX*)tagMdls[i]->getmodel()->model;

		if (mdl)
			saveTexId[i] = mdl->mats[0].attr_texId;
	}
}


enum //tag store data task 
{
	tagHP,
	tagDone,
	texID
};

enum //tag task enum
{
	init,
	createChild,
	checkInput,
	wait,
	done,
};

static uint8_t sprayNeeded[3] = {
	1, //small
	3, //normal
	6 //large
};

static void resetTagDataValues(taskwk* twp)
{
	twp->counter.b[texID] = 0; //store texture ID
	twp->counter.b[tagDone] = 0; //check if tag is done
	twp->counter.b[tagHP] = 0; //store tag HP (number of spray needed)
}

static uint8_t getTagTexID(taskwk* twp)
{
	return twp->counter.b[texID];
}

static bool isTagDone(taskwk* twp)
{
	return twp->counter.b[tagDone];
}

static uint8_t getTagHP(taskwk* twp)
{
	return twp->counter.b[tagHP];
}

void SetTagDone(taskwk* twp)
{
	twp->counter.b[tagDone] = TRUE;
	tagsLeft[CurrentAct] = tagsLeft[CurrentAct] > 0 ? --tagsLeft[CurrentAct] : 0;
	tagCount++;
}

void setNumberOfTagToDo()
{
	if (tagsLeft[CurrentAct] > 0)
		return;

	if (!CurrentObjectList || !CurrentSetFile)
		return;

	int listSize = CurrentObjectList->Count;
	SETEntry* Set = CurrentSetFile;
	int setSize = SETTable_Count;

	if (!setSize)
		return;

	uint16_t id = 0;

	for (uint16_t j = 0; j < setSize; j++)
	{
		id = Set[j].ObjectType & 0x7FFF;

		if (!id)
			continue;

		ObjectFuncPtr t = CurrentObjectList->List[id].LoadSub;

		if (t == (ObjectFuncPtr)tag_Exec)
		{
			tagsLeft[CurrentAct]++;
		}
	}
}

void ChildArrowDisp(task* tp)
{
	auto twp = tp->twp;

	if (MissedFrames || tp->ptp->twp->mode >= done)
		return;

	SetMaterial(1.0f, 1.0f, 0.0f, 0.0f); //set red color to the arrow
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	dsDrawObject(tagArrowMdl->getmodel());
	njPopMatrix(1u);
	ResetMaterial();
}

void ChildArrow(task* tp)
{
	auto twp = tp->twp;

	switch (twp->mode)
	{
	case 0:
		tp->disp = ChildArrowDisp;
		twp->pos.y += 9.0f;
		twp->value.f = twp->pos.y;
		twp->mode++;
		break;
	case 1:
		if (twp->pos.y < twp->value.f + 10.0f)
			tp->twp->pos.y++;
		else
			twp->mode++;
		break;
	case 2:
		if (twp->pos.y > twp->value.f)
			tp->twp->pos.y--;
		else
			twp->mode--;
		break;
	}

	tp->disp(tp);
}

void UpdateGraffiti(task* tp, uint8_t pnum)
{
	auto twp = tp->twp;
	twp->counter.b[tagHP]++;
	const uint8_t id = static_cast<uint8_t>(twp->scl.x);
	uint8_t curHP = getTagHP(twp);
	const uint8_t hpMAX = sprayNeeded[id];

	PlayCustomSoundVolume(sprayPaintSnd, 2.0f);

	if (curHP < hpMAX)
	{
		PlayCustomSoundVolume(smallTagSnd + curHP, 3.0f);
		curHP = getTagHP(twp);
	}

	if (curHP >= hpMAX)
	{
		if (tp->ocp)
		{
			if (!SetCPFlag(tp))
			{
				SetBroken(tp);
			}
		}

		SetTagDone(twp);
	}
}

void DoGraffiti(uint8_t pnum, task* tp)
{
	auto twp = tp->twp;
	const uint8_t hpMAX = sprayNeeded[static_cast<uint8_t>(twp->scl.x)];
	NJS_POINT3 vel = { 1.0f, 4.0f, 0.0f };
	auto p = playertwp[pnum];

	if (sprayPaintCount[pnum] > 0)
	{
		curTagPos[pnum] = twp->pos;
		isTagging = true;
		sprayPaintCount[pnum]--;
		SetLookingPoint(pnum, &twp->pos);
		p->ang.y = twp->ang.y;
		ForcePlayerAction(0, 12);
		PlayerLookAt(&p->pos, &twp->pos, 0, &p->ang.y);

		twp->mode = wait;
		return;
	}
	else
	{
		ForcePlayerAction(pnum, 24);
		PlayCustomSoundVolume(noSpraySnd, 2.0f);
	}
}

void CheckGraffitiInput(task* tp, NJS_POINT3 pos, uint8_t pnum)
{
	if (CheckCollisionP(&pos, 35.0f))
	{
		if (Controllers[pnum].PressedButtons & Buttons_Y)
		{
			playertwp[pnum]->flag |= Status_DoNextAction;
			playertwp[pnum]->smode = 20;
			DoGraffiti(pnum, tp);
		}
	}
}


void tag_Disp(task* tp)
{
	auto twp = tp->twp;

	if (MissedFrames || twp->mode < checkInput || !isTagDone(twp) && getTagHP(twp) <= 0)
		return;

	const uint8_t id = static_cast<uint8_t>(twp->scl.x);
	uint8_t texID = getTagTexID(twp);
	NJS_MODEL_SADX* mdl = (NJS_MODEL_SADX*)tagMdls[id]->getmodel()->model;

	if (!mdl)
		return;

	mdl->mats[0].attr_texId = texID - (sprayNeeded[id]) + getTagHP(twp);

	njSetTexture(&graffitiTexlist);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	njRotateZ(0, twp->ang.z);
	njRotateX(0, twp->ang.x);
	njRotateY(0, twp->ang.y);
	dsDrawObject(tagMdls[id]->getmodel());
	njPopMatrix(1u);
}

void tag_Exec(task* tp)
{
	if (CheckRangeOut(tp))
		return;

	auto twp = tp->twp;

	if (twp->scl.x > 2.0f)
		twp->scl.x = 2.0f;
	else if (twp->scl.x < 0.0f)
		twp->scl.x = 0.0f;

	const uint8_t id = static_cast<uint8_t>(twp->scl.x);
	uint8_t pnum = GetTheNearestPlayerNumber(&twp->pos);
	const uint8_t hpMAX = sprayNeeded[id];
	const NJS_MODEL_SADX* mdl = (NJS_MODEL_SADX*)tagMdls[id]->getmodel()->model;

	switch (twp->mode)
	{
	case init:
		SetFlagNoRespawn(tp);
		resetTagDataValues(twp);
		twp->counter.b[texID] = mdl->mats[0].attr_texId; //save tag tex id
		tp->disp = tag_Disp;

		if (!SetCPFlag(tp))
		{
			twp->mode = createChild;
		}
		else
		{
			twp->counter.b[tagHP] = sprayNeeded[id];
			twp->counter.b[tagDone] = TRUE;
			twp->mode = done;
		}
		break;
	case createChild:
		CreateChildTask(2, ChildArrow, tp);
		twp->mode++;
		break;
	case checkInput:
		CheckGraffitiInput(tp, twp->pos, pnum);
		break;
	case wait:
		playerpwp[pnum]->mj.reqaction = 131;

		++twp->wtimer;

		if (twp->wtimer == 10)
		{
			UpdateGraffiti(tp, pnum);
		}
		else if (twp->wtimer == 20)
		{
			if (twp->counter.b[tagDone] == TRUE)
			{
				if (hpMAX == 1)
					PlayCustomSoundVolume(smallTagSnd, 3.0f);
				else
					PlayCustomSoundVolume(sprayFinalSnd, 3.0f);
			}

			ResetPlayerLook(pnum);
			isTagging = false;
			twp->wtimer = 0;
			ForcePlayerAction(0, 24);
			twp->mode = SetCPFlag(tp) ? done : checkInput;
		}
		break;
	}

	LoopTaskC(tp);
	tp->disp(tp);
}

void initGraffitiMdl()
{
	tagMdls[0] = LoadBasicModel("tagSmall");
	tagMdls[1] = LoadBasicModel("tagNormal");
	tagMdls[2] = LoadBasicModel("tagLarge");
	tagArrowMdl = LoadBasicModel("tagArrow");
	saveGraffitiTexs();
}