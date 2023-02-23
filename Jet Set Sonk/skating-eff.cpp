#include "pch.h"

//port SA2 Shadow skating effects

enum
{
	leftToeNarrow,
	leftToeWide,
	leftHeelWide,
	leftHeelNarrow,
	rightToeNarrow,
	rightToeWide,
	rightHeelWide,
	rightHeelNarrow,
};

enum
{
	root,
	ss = 22,
	curled = 66
};

static ModelInfo* skatingThrustMdls[8]{ nullptr };

static NJS_MATRIX rightToeMtx;
static NJS_MATRIX leftToeMtx;
static NJS_MATRIX rightHeelMtx;
static NJS_MATRIX leftHeelMtx;

TaskHook SonicDisplay_t(SonicDisplay);

void (*backupCallback)(NJS_OBJECT* obj) = NULL; 

FunctionPointer(void, dsPushPopMotion, (NJS_OBJECT* obj), 0x004050C0);
FunctionHook<void, NJS_OBJECT*> dsPushPopMotion_t(dsPushPopMotion);

static Float _DrawModel_scl = 0.0f;

bool isSkateObj(NJS_OBJECT* obj)
{
	for (uint8_t i = 0; i < LengthOfArray(skatingThrustMdls); i++)
	{
		if (obj == skatingThrustMdls[i]->getmodel())
			return true;
	}

	return false;
}


static void SonkCallBack(NJS_OBJECT* obj)
{
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

	if (backupCallback)
		backupCallback(obj);
}

void DrawSkatingEffects(playerwk* pwp)
{
	if (!pwp || pwp->mj.reqaction != 11 && pwp->mj.reqaction != 12 && pwp->mj.reqaction != 13)
		return;

	___dsSetPalette(2);

	const Angle rotZ = -0x3000;

	njPushMatrix(leftToeMtx);
	njRotateZ(0, rotZ);
	auto leftToeObj = skatingThrustMdls[leftToeNarrow]->getmodel();     // draw Skating Thrust 

	if ((FrameCounterUnpaused & 1) == 0)
	{
		leftToeObj = skatingThrustMdls[leftToeWide]->getmodel();
	}

	late_DrawObjectClipMesh(leftToeObj, LATE_LIG, 0.0f);
	njPopMatrixEx();

	njPushMatrix(rightToeMtx);
	njRotateZ(0, rotZ);
	auto v5 = skatingThrustMdls[rightToeNarrow]->getmodel();

	if ((FrameCounterUnpaused & 1) == 0)
	{
		v5 = skatingThrustMdls[rightToeWide]->getmodel();
	}

	late_DrawObjectClipMesh(v5, LATE_LIG, 0.0f);
	njPopMatrixEx();


	const Angle rotZ_ = -0x1900;
	const NJS_POINT3 offset = { -0.6f, 0.0f, 0.0f };

	njPushMatrix(leftHeelMtx);
	njTranslateV(0, &offset);
	njRotateZ(0, rotZ_);

	auto v6 = skatingThrustMdls[leftHeelWide]->getmodel();

	if ((FrameCounterUnpaused & 1) == 0)
	{
		v6 = skatingThrustMdls[leftHeelNarrow]->getmodel();
	}

	late_DrawObjectClipMesh(v6, LATE_LIG, 0.0f);
	njPopMatrixEx();

	njPushMatrix(rightHeelMtx);
	njTranslateV(0, &offset);
	njRotateZ(0, rotZ_);
	auto v7 = skatingThrustMdls[rightHeelWide]->getmodel();

	if ((FrameCounterUnpaused & 1) == 0)
	{
		v7 = skatingThrustMdls[rightHeelNarrow]->getmodel();
	}

	late_DrawObjectClipMesh(v7, LATE_LIG, 0.0f);
	njPopMatrixEx();

	___dsSetPalette(0);
}

static void SonkDisplay_r(task* tp)
{
	auto pwp = reinterpret_cast<playerwk*>(tp->mwp->work.ptr);
	auto twp = tp->twp;

	backupCallback = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
	*NodeCallbackFuncPtr = SonkCallBack;
	SonicDisplay_t.Original(tp);
	DrawSkatingEffects(pwp);
	*NodeCallbackFuncPtr = *backupCallback; //restore
}


void LoadSkatingThrustModels()
{
	for (uint8_t i = 0; i < LengthOfArray(skatingThrustMdls); i++)
	{
		std::string sL = "skatingThrust" + std::to_string(i);
		skatingThrustMdls[i] = LoadBasicModel(sL.c_str());
	}
}

void initSkatingEffects()
{
	LoadSkatingThrustModels();
	SonicDisplay_t.Hook(SonkDisplay_r);
}