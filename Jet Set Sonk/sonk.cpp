#include "pch.h"
#include "objects.h"

//hack Sonk Display function to add objects, effects etc.

NJS_MATRIX rightToeMtx;
NJS_MATRIX leftToeMtx;
NJS_MATRIX rightHeelMtx;
NJS_MATRIX leftHeelMtx;
NJS_MATRIX rightFingers;

enum
{
	root,
	ss = 22,
	curled = 66
};


TaskHook SonicDisplay_t(SonicDisplay);

void (*backupCallback)(NJS_OBJECT* obj) = NULL;

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

	if (obj == SONIC_OBJECTS[root]->getnode(32) || obj == SONIC_OBJECTS[ss]->getnode(32) || obj == SONIC_OBJECTS[curled]->getnode(33)) //curled hierarchy is different
	{
		njSetMatrix(rightFingers, _nj_current_matrix_ptr_);
	}

	if (backupCallback)
		backupCallback(obj);
}

static void SonkDisplay_r(task* tp)
{
	auto pwp = reinterpret_cast<playerwk*>(tp->mwp->work.ptr);
	auto twp = tp->twp;

	backupCallback = *NodeCallbackFuncPtr; //save current nodecallback for mods compatibility
	*NodeCallbackFuncPtr = SonkCallBack;
	SonicDisplay_t.Original(tp);
	DrawSkatingEffects(pwp);
	drawSprayPaintHand(twp, pwp);
	*NodeCallbackFuncPtr = *backupCallback; //restore
}


void initSonkEff()
{
	SonicDisplay_t.Hook(SonkDisplay_r);
}