#include "pch.h"
#include "objects.h"

TaskHook TornadoEventDisp_t(0x6F8800);
TaskHook TornadoDisp_t((intptr_t)Tornado_Display);
TaskHook Tornado2TransfoDisp_t((intptr_t)0x62AB90);
TaskHook Tornado2EventDisp_t(0x4188D0);

static void (*backupCallBack)(NJS_OBJECT* obj) = NULL;

static NJS_MATRIX SonkMtx;

const uint8_t Tornado1_SonkNodes = 31;
const uint8_t Tornado1EventShot_SonkNodes = 13;
const uint8_t Tornado2Before_SonkNodes = 30;
const uint8_t Tornado2Transfo_SonkNodes = 101;
const uint8_t Tornado2Change_SonkNodes = 32;

struct objNode
{
	NJS_OBJECT obj;
	uint8_t node;
};

objNode AllTornadoSonk[]
{
	{ Tornado1_Object, Tornado1_SonkNodes },
	{ Tornado1_EventObj, Tornado1_SonkNodes },
	{ Tornado1_EventShot, Tornado1EventShot_SonkNodes},
	{ Tornado2Before_Object, Tornado2Before_SonkNodes},
	{ Tornado2Transfo_Object, Tornado2Transfo_SonkNodes},
	{ Tornado2Change_Object, Tornado2Change_SonkNodes},
	{ Tornado2_EventObj, Tornado2Change_SonkNodes},
	{ Tornado2TakeOff_EventObj, Tornado2Before_SonkNodes},
};

static void TornadoCallBack(NJS_OBJECT* obj)
{
	for (uint16_t i = 0; i < LengthOfArray(AllTornadoSonk); i++) //we browse the array of all the tornado objs with Sonic/Tails nodes
	{
		const uint8_t node = AllTornadoSonk[i].node;

		if (obj == AllTornadoSonk[i].obj.getnode(node)) //if the game is about to draw a specific part of the body
		{
			njSetMatrix(SonkMtx, _nj_current_matrix_ptr_); //copy matrix
		}
	}

	if (backupCallBack)
		backupCallBack(obj);
}

static void DrawHeadItems()
{
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njSetTexture(&SONIC_TEXLIST);
	njPushMatrix(SonkMtx);
	late_DrawObjectClipMesh(headPhone->getmodel(), LATE_LIG, 0.0f);
	late_DrawObjectClipMesh(goggles->getmodel(), LATE_LIG, 0.0f);
	njPopMatrix(1);
	ResetMaterial();
}

//Hack tornado display 
void TornadoDisp_r(task* tp)
{
	backupCallBack = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
	*NodeCallbackFuncPtr = TornadoCallBack;

	TornadoDisp_t.Original(tp);
	DrawHeadItems();

	*NodeCallbackFuncPtr = backupCallBack;
}

//Hack tornado transfo display 
void Tornado2TransfoDisp_r(task* tp)
{
	backupCallBack = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
	*NodeCallbackFuncPtr = TornadoCallBack;

	Tornado2TransfoDisp_t.Original(tp);
	DrawHeadItems();

	*NodeCallbackFuncPtr = backupCallBack;
}

void TornadoEventDisp_r(task* tp)
{
	backupCallBack = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
	*NodeCallbackFuncPtr = TornadoCallBack;

	TornadoEventDisp_t.Original(tp);
	DrawHeadItems();

	*NodeCallbackFuncPtr = backupCallBack;
}

void Tornado2EventDisp_r(task* tp)
{
	bool isTR2 = (TR2TakeOffEVPtr && TR2TakeOffEVPtr == tp || TR2TailsRM && TR2TailsRM == tp || TR2SonkRM && TR2SonkRM == tp);

	if (isTR2)
	{
		backupCallBack = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
		*NodeCallbackFuncPtr = TornadoCallBack;
	}

	Tornado2EventDisp_t.Original(tp);

	if (isTR2)
	{
		DrawHeadItems();
		*NodeCallbackFuncPtr = backupCallBack;
	}
}

void InitTornado()
{
	if (!isAccessoryMod)
	{
		TornadoDisp_t.Hook(TornadoDisp_r);
		TornadoEventDisp_t.Hook(TornadoEventDisp_r);

		Tornado2TransfoDisp_t.Hook(Tornado2TransfoDisp_r);
		Tornado2EventDisp_t.Hook(Tornado2EventDisp_r);
	}
}