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

static ModelInfo* headPhone = nullptr;
static ModelInfo* goggles = nullptr;

enum
{
	root,
	ss = 22,
	curled = 66
};

TaskHook SonicExec_t(SonicTheHedgehog);
TaskHook SonicDisplay_t(SonicDisplay);

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

extern bool isAccessoryMod;
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
}