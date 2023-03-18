#include "pch.h"
#include "objects.h"
#include "tags.h"

//hack Sonk Display function to add objects, effects etc.

NJS_MATRIX rightToeMtx;
NJS_MATRIX leftToeMtx;
NJS_MATRIX rightHeelMtx;
NJS_MATRIX leftHeelMtx;
NJS_MATRIX rightFingers;
NJS_MATRIX headMtx;

ModelInfo* headPhone = nullptr;
ModelInfo* goggles = nullptr;

enum
{
	root,
	ss = 22,
	curled = 66
};

TaskHook SonicExec_t(SonicTheHedgehog);
TaskHook SonicDisplay_t(SonicDisplay);
TaskHook DrawNPCMainCharSS_t(0x62F1B0);
TaskHook DrawNPCMainCharMR_t(0x52EAA0);
TaskHook DrawNPCMainCharEC0_t(0x51AA60);


void (*backupCallback)(NJS_OBJECT* obj) = NULL;

static void SonkCallBack(NJS_OBJECT* obj)
{
	if (obj == SONIC_OBJECTS[root]->getnode(12) || obj == SONIC_OBJECTS[ss]->getnode(12) || obj == SONIC_OBJECTS[curled]->getnode(13)) //curled hierarchy is different
	{
		njSetMatrix(headMtx, _nj_current_matrix_ptr_);
	}

	if (obj == SONIC_OBJECTS[root]->getnode(53) || obj == SONIC_OBJECTS[ss]->getnode(53) || obj == SONIC_OBJECTS[curled]->getnode(54)) //curled hierarchy is different
	{
		njSetMatrix(rightToeMtx, _nj_current_matrix_ptr_);
	}

	if (obj == SONIC_OBJECTS[root]->getnode(63) || obj == SONIC_OBJECTS[ss]->getnode(63) || obj == SONIC_OBJECTS[curled]->getnode(64)) //curled hierarchy is different
	{
		njSetMatrix(leftToeMtx, _nj_current_matrix_ptr_);
	}

	if (obj == SONIC_OBJECTS[root]->getnode(52) || obj == SONIC_OBJECTS[ss]->getnode(52) || obj == SONIC_OBJECTS[curled]->getnode(53)) //curled hierarchy is different
	{
		njSetMatrix(rightHeelMtx, _nj_current_matrix_ptr_);
	}

	if (obj == SONIC_OBJECTS[root]->getnode(62) || obj == SONIC_OBJECTS[ss]->getnode(62) || obj == SONIC_OBJECTS[curled]->getnode(63)) //curled hierarchy is different
	{
		njSetMatrix(leftHeelMtx, _nj_current_matrix_ptr_);
	}

	if (obj == SONIC_OBJECTS[root]->getnode(32) || obj == SONIC_OBJECTS[ss]->getnode(32) || obj == SONIC_OBJECTS[curled]->getnode(33)) //curled hierarchy is different
	{
		njSetMatrix(rightFingers, _nj_current_matrix_ptr_);
	}

	if (backupCallback)
		backupCallback(obj);
}

void DrawHeadItems()
{
	if (isAccessoryMod)
		return;

	___dsSetPalette(2);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);

	njSetTexture(&SONIC_TEXLIST);
	njPushMatrix(headMtx);
	late_DrawObjectClipMesh(headPhone->getmodel(), LATE_LIG, 0.0f);
	late_DrawObjectClipMesh(goggles->getmodel(), LATE_LIG, 0.0f);
	njPopMatrix(1);

	ResetMaterial();
	___dsSetPalette(0);
}


static void DrawNPCHeadItems_FuncHook(FunctionHook<void, task*> &t, task* tp)
{
	auto twp = tp->twp;
	const bool isSonk = tp->twp->wtimer == 0 || tp->twp->wtimer == 7 && CurrentLevel == LevelIDs_StationSquare;

	if (isSonk)
	{
		backupCallback = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
		*NodeCallbackFuncPtr = SonkCallBack;
	}

	t.Original(tp); //call original function

	if (isSonk)
	{
		if (dsCheckViewV(&twp->pos, 15.0f) && !loop_count && !EV_MainThread_ptr)
			DrawHeadItems();

		*NodeCallbackFuncPtr = *backupCallback; //restore
	}
}

static void DrawNPCMainCharMR_r(task* tp)
{
	DrawNPCHeadItems_FuncHook(DrawNPCMainCharMR_t, tp);
}

static void DrawNPCMainCharSS_r(task* tp)
{
	DrawNPCHeadItems_FuncHook(DrawNPCMainCharSS_t, tp);
}

static void DrawNPCMainCharEC0_r(task* tp)
{
	DrawNPCHeadItems_FuncHook(DrawNPCMainCharEC0_t, tp);
}


static void SonkDisplay_r(task* tp)
{
	auto pwp = reinterpret_cast<playerwk*>(tp->mwp->work.ptr);
	auto twp = tp->twp;

	backupCallback = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
	*NodeCallbackFuncPtr = SonkCallBack;
	SonicDisplay_t.Original(tp);

	if (!MetalSonicFlag && (twp->flag & Status_Ball) == 0 && (twp->wtimer & 2) == 0 && dsCheckViewV(&twp->pos, 15.0f))
	{
		DrawHeadItems();	
		DrawSkatingEffects(pwp);
		drawSprayPaintHand(twp, pwp);
	}

	*NodeCallbackFuncPtr = *backupCallback; //restore
}

static void SonkExec_r(task* tp)
{
	SonicExec_t.Original(tp);

	auto twp = tp->twp;
	auto pwp = (playerwk*)tp->mwp->work.l;

	if ( (twp->flag & Status_Ground) && twp->mode <= 2 && !pwp->ttp)
		out_TagCheckInput(twp, pwp);
}


void initHeadObjects()
{
	if (isAccessoryMod)
		return;

	headPhone = LoadBasicModel("headphoneBeat");
	goggles = LoadBasicModel("gogglesBeat");
}

void init_Sonk()
{
	SonicExec_t.Hook(SonkExec_r);
	SonicDisplay_t.Hook(SonkDisplay_r);
	HelperFunctionsGlobal.RegisterCharacterPVM(Characters_Sonic, graphPVM);
	initHeadObjects();

	if (!isAccessoryMod)
	{
		DrawNPCMainCharSS_t.Hook(DrawNPCMainCharSS_r);
		DrawNPCMainCharMR_t.Hook(DrawNPCMainCharMR_r);
		DrawNPCMainCharEC0_t.Hook(DrawNPCMainCharEC0_r);
	}
}