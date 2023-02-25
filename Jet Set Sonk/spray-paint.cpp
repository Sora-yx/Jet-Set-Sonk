#include "pch.h"
#include "objects.h"

CCL_INFO SprayCollision = { 0, 0x0, 0xb0, 0x0, 0x0, { 0.0, 3.0, 0.0 }, 4.5, 0.0, 0.0, 0.0, 0, 0, 0 };

static ModelInfo* sprayMdl = nullptr;
static ModelInfo* sprayHoldMdl = nullptr;
uint8_t sprayPaintCount[pMax]{ 0 };
static uint8_t sprayPaintMax = 20;
extern NJS_MATRIX rightFingers;

void drawSprayPaintHand(taskwk* twp, playerwk* pwp)
{
	if (!isTag())
		return;

	bool SS = playerpwp[twp->counter.b[0]]->equipment & Upgrades_SuperSonic;
	NJS_POINT3 scl = { 2.5f, 2.5f, 2.5f };
	NJS_POINT3 pos{ NULL };
	pos.z -= 0.5f;
	auto backup = SS ? &SUPERSONIC_TEXLIST : &SONIC_TEXLIST;

	___dsSetPalette(2);
	njSetTexture(&graffitiTexlist);
	njPushMatrix(rightFingers);

	njTranslateV(0, &pos);
	njScaleV(0, &scl);
	late_DrawObjectClipMesh(sprayHoldMdl->getmodel(), LATE_LIG, 0.0f);
	njPopMatrixEx();

	NJS_POINT3 sprayPos;
	sprayPos = pwp->righthand_pos;

	njPushMatrix(nj_unit_matrix_);
	njRotateZ(0, twp->ang.z);
	njRotateX(0, twp->ang.x);
	njRotateY(0, (0x8000 - twp->ang.y));
	njCalcVector(_nj_current_matrix_ptr_, &sprayPos, &sprayPos);
	njPopMatrix(1u);
	njAddVector(&sprayPos, &twp->cwp->info->center);

	CreateWater(&sprayPos, &scl, 1.2f);


	___dsSetPalette(0);
	njSetTexture(backup);
}

void sprayPaintAdd(char pnum, char count)
{
	if (sprayPaintCount[pnum] + count < sprayPaintMax)
	{
		sprayPaintCount[pnum] += count;
	}
	else
	{
		sprayPaintCount[pnum] = sprayPaintMax;
	}
}

void sprayPaint_Disp(task* tp)
{
	if (MissedFrames || tp->twp->mode > 1)
		return;

	auto twp = tp->twp;

	NJS_POINT3 scl= { 1.0f, 1.0f, 1.0f };
	NJS_ARGB color = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (twp->scl.x >= 2.0f)
	{
		scl = {2.0f, 2.0f, 2.0f };
		color.r = 0.0f;
		color.g = 0.0f;
	}

	SetMaterial(color.a, color.r, color.g, color.b);
	njSetTexture(&graffitiTexlist);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	njRotateX(0, twp->ang.x);
	njRotateY(0, twp->ang.y);

	njScaleV(0, &scl);
	dsDrawObject(sprayMdl->getmodel());
	njPopMatrix(1u);
	ResetMaterial();
}

void sprayPaint_Exec(task* tp)
{
	if (CheckRangeOut(tp))
		return;

	auto twp = tp->twp;
	taskwk* player = nullptr;
	char count = twp->scl.x == 2 ? 5 : 1;

	switch (twp->mode)
	{
	case 0:
	default:
		CCL_Init(tp, &SprayCollision, 1, 4u);
		tp->disp = sprayPaint_Disp;
		if (twp->scl.x > 2)
			twp->scl.x = 2;
		else if (twp->scl.x < 0)
			twp->scl.x = 0;

		twp->mode = 1;
		break;
	case 1:
		twp->ang.y += 800;
		player = (taskwk*)GetCollidingEntityA((EntityData1*)twp);
		if (player)
		{
			//if Miles AI grab a spray, give it to Sonk
			if (player == playertwp[1] && TailsAI_ptr->Data1->CharIndex == 1) 
				sprayPaintAdd(0, count);
			else
				sprayPaintAdd(player->counter.b[0], count);

			twp->mode++;
		}
		break;
	case 2:
		if (++twp->wtimer == 2000) //respawn timer
		{
			twp->wtimer = 0;
			twp->mode--;
		}
		break;

	}

	if (twp->mode == 1)
	{
		tp->disp(tp);
		EntryColliList(twp);
	}
}


void initSprayMdl()
{
	sprayMdl = LoadBasicModel("sprayPaint");
	sprayHoldMdl = LoadBasicModel("sprayPaintHold");
}