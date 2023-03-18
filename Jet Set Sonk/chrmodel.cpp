#include "pch.h"
#include "SSTexlist.h"

ModelInfo* rootMdl = nullptr;
ModelInfo* morphHead = nullptr;
ModelInfo* jumpBall = nullptr;
ModelInfo* curled = nullptr;
ModelInfo* eventHead = nullptr;
ModelInfo* SSRoot = nullptr;

//upgrades
ModelInfo* crystalRing = nullptr;
ModelInfo* wristCrystalRing = nullptr;

AnimationFile* faceMotion = nullptr;

void replaceSonkActions()
{
	auto root = rootMdl->getmodel();
	uint16_t i = 0;

	for (i = 0; i < 73; i++)
	{
		//24, 25 and 26 don't exist
		if (!SONIC_ACTIONS[i])
			continue;

		if (i == 14)
		{
			SONIC_ACTIONS[i]->object = curled->getmodel();
			continue;
		}

		if (i == 21)
		{
			SONIC_ACTIONS[i]->object = jumpBall->getmodel();
			continue;
		}

		SONIC_ACTIONS[i]->object = root;
	}

	//we skip snowboarding anims as we don't need to replace them

	for (i = 87; i < 110; i++)
	{
		SONIC_ACTIONS[i]->object = root;
	}

	for (i = 113; i < 130; i++)
	{
		SONIC_ACTIONS[i]->object = root;
	}


	for (i = 130; i < 134; i++)
	{
		SONIC_ACTIONS[i]->object = SSRoot->getmodel();
	}

	for (i = 134; i < 138; i++)
	{
		SONIC_ACTIONS[i]->object = root;
	}

	for (i = 138; i < 145; i++)
	{
		if (i == 142)
			continue;

		SONIC_ACTIONS[i]->object = SSRoot->getmodel();
	}

	for (i = 145; i < 149; i++)
	{
		SONIC_ACTIONS[i]->object = root;
	}
}

void replaceSonkModels()
{
	//toe
	SONIC_MODELS[0] = rootMdl->getmodel()->getnode(63)->basicdxmodel;
	SONIC_MODELS[1] = rootMdl->getmodel()->getnode(53)->basicdxmodel;

	//head
	SONIC_MODELS[8] = rootMdl->getmodel()->getnode(22)->basicdxmodel;
	SONIC_MODELS[9] = morphHead->getmodel()->basicdxmodel;
}

void replaceSonkObjects()
{
	auto root = rootMdl->getmodel();
	auto ssRoot = SSRoot->getmodel();

	SONIC_OBJECTS[0] = root;

	//right arm
	SONIC_OBJECTS[1] = root->getnode(34);
	SONIC_OBJECTS[2] = root->getnode(33);
	SONIC_OBJECTS[3] = root->getnode(29);
	SONIC_OBJECTS[4] = root->getnode(30);
	SONIC_OBJECTS[5] = root->getnode(32);
	SONIC_OBJECTS[6] = root->getnode(31);

	//left arm
	SONIC_OBJECTS[7] = root->getnode(45);
	SONIC_OBJECTS[8] = root->getnode(44);
	SONIC_OBJECTS[9] = root->getnode(40);
	SONIC_OBJECTS[10] = root->getnode(41);
	SONIC_OBJECTS[11] = root->getnode(43);
	//thumb left isn't stored

	//right leg
	SONIC_OBJECTS[12] = root->getnode(55);
	SONIC_OBJECTS[13] = root->getnode(54);
	SONIC_OBJECTS[14] = root->getnode(51);
	SONIC_OBJECTS[15] = root->getnode(52);
	SONIC_OBJECTS[16] = root->getnode(53);

	//left leg
	SONIC_OBJECTS[17] = root->getnode(65);
	SONIC_OBJECTS[18] = root->getnode(64);
	SONIC_OBJECTS[19] = root->getnode(61);
	SONIC_OBJECTS[20] = root->getnode(62);
	SONIC_OBJECTS[21] = root->getnode(63);

	//Super Sonic
	SONIC_OBJECTS[22] = ssRoot;

	//right arm SS
	SONIC_OBJECTS[23] = ssRoot->getnode(34);
	SONIC_OBJECTS[24] = ssRoot->getnode(33);
	SONIC_OBJECTS[25] = ssRoot->getnode(29);
	SONIC_OBJECTS[26] = ssRoot->getnode(30);
	SONIC_OBJECTS[27] = ssRoot->getnode(32);

	//left arm SS
	SONIC_OBJECTS[28] = ssRoot->getnode(45);
	SONIC_OBJECTS[29] = ssRoot->getnode(44);
	SONIC_OBJECTS[30] = ssRoot->getnode(40);
	SONIC_OBJECTS[31] = ssRoot->getnode(41);
	SONIC_OBJECTS[32] = ssRoot->getnode(43);

	//right leg SS
	SONIC_OBJECTS[33] = ssRoot->getnode(55);
	SONIC_OBJECTS[34] = ssRoot->getnode(54);
	SONIC_OBJECTS[35] = ssRoot->getnode(51);
	SONIC_OBJECTS[36] = ssRoot->getnode(52);
	SONIC_OBJECTS[37] = ssRoot->getnode(53);

	//left leg SS
	SONIC_OBJECTS[38] = ssRoot->getnode(65);
	SONIC_OBJECTS[39] = ssRoot->getnode(64);
	SONIC_OBJECTS[40] = ssRoot->getnode(61);
	SONIC_OBJECTS[41] = ssRoot->getnode(62);
	SONIC_OBJECTS[42] = ssRoot->getnode(63);

	//43 is empty

	SONIC_OBJECTS[44] = jumpBall->getmodel();

	//head
	SONIC_OBJECTS[45] = root->getnode(18);
	SONIC_OBJECTS[46] = root->getnode(22);
	SONIC_OBJECTS[47] = eventHead->getmodel();
	SONIC_OBJECTS[48] = root->getnode(12);
	SONIC_OBJECTS[49] = root->getnode(22);
	SONIC_OBJECTS[50] = root->getnode(11);

	//eyes
	SONIC_OBJECTS[51] = root->getnode(17);
	SONIC_OBJECTS[52] = root->getnode(21);

	SONIC_OBJECTS[62] = root->getnode(28);
	SONIC_OBJECTS[66] = curled->getmodel();
	SONIC_OBJECTS[67] = jumpBall->getmodel();

	//upgrades
	SONIC_OBJECTS[63] = wristCrystalRing->getmodel();
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4]; //fix welds
	SONIC_OBJECTS[64] = crystalRing->getmodel();
}

void ReplaceFaceMotion()
{
	faceMotion = LoadAnim("face_s_head");

	if (faceMotion)
	{
		*SONIC_MOTIONS = faceMotion->getmotion();
	}
}


void init_chrModel()
{
	rootMdl = LoadBasicModel("root");
	morphHead = LoadBasicModel("morphHead");
	jumpBall = LoadBasicModel("jumpBall");
	eventHead = LoadBasicModel("eventHead");
	curled = LoadBasicModel("curled");
	SSRoot = LoadBasicModel("SSRoot");

	crystalRing = LoadBasicModel("crystalRing");
	wristCrystalRing = LoadBasicModel("wristCrystalRing");

	if (rootMdl)
	{
		replaceSonkObjects();
		replaceSonkModels();
		replaceSonkActions();
		ReplaceFaceMotion();
		initAnims();
		initSkatingEffects();
		SonicJVList();
	}

	WriteData<1>((int*)0x493500, 0xC3); //disable morph feet
	WriteJump((void*)0x49BE2D, (void*)0x49BE68); //disable light shoes

	WriteData((NJS_TEXLIST**)0x55E65C, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E751, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E712, SSAura02);
	WriteData((NJS_TEXLIST**)0x55E7CD, SSWaterThing);
	WriteData((NJS_TEXLIST**)0x55F2B3, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1D1, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1DC, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F2BE, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F677, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F669, SSHomingTex3);
	SUPERSONIC_TEXLIST = SS_PVM;
}