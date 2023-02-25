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

extern NJS_MATRIX rightToeMtx;
extern NJS_MATRIX leftToeMtx;
extern NJS_MATRIX rightHeelMtx;
extern NJS_MATRIX leftHeelMtx;


static ModelInfo* skatingThrustMdls[8]{ nullptr };

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
	auto rightToeObj = skatingThrustMdls[rightToeNarrow]->getmodel();

	if ((FrameCounterUnpaused & 1) == 0)
	{
		rightToeObj = skatingThrustMdls[rightToeWide]->getmodel();
	}

	late_DrawObjectClipMesh(rightToeObj, LATE_LIG, 0.0f);
	njPopMatrixEx();


	const Angle rotZ_ = -0x1900;
	const NJS_POINT3 offset = { -0.6f, 0.0f, 0.0f };

	njPushMatrix(leftHeelMtx);
	njTranslateV(0, &offset);
	njRotateZ(0, rotZ_);

	auto leftHeelObj = skatingThrustMdls[leftHeelWide]->getmodel();

	if ((FrameCounterUnpaused & 1) == 0)
	{
		leftHeelObj = skatingThrustMdls[leftHeelNarrow]->getmodel();
	}

	late_DrawObjectClipMesh(leftHeelObj, LATE_LIG, 0.0f);
	njPopMatrixEx();

	njPushMatrix(rightHeelMtx);
	njTranslateV(0, &offset);
	njRotateZ(0, rotZ_);
	auto rightHeelObj = skatingThrustMdls[rightHeelWide]->getmodel();

	if ((FrameCounterUnpaused & 1) == 0)
	{
		rightHeelObj = skatingThrustMdls[rightHeelNarrow]->getmodel();
	}

	late_DrawObjectClipMesh(rightHeelObj, LATE_LIG, 0.0f);
	njPopMatrixEx();

	___dsSetPalette(0);
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
}