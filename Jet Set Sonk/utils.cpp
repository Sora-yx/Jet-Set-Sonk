#include "pch.h"

ModelInfo* LoadBasicModel(const char* name) {

	std::string path = modName + "Loading basic model : % s... \n"; 

	PrintDebug(path.c_str(), name);

	std::string fullPath = "system\\models\\";
	fullPath = fullPath + name + ".sa1mdl";

	ModelInfo* mdl = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (mdl->getformat() != ModelFormat_Basic) {
		PrintDebug("Failed!\n");
		delete mdl;
		return nullptr;
	}

	PrintDebug("Done.\n");
	return mdl;
}

ModelInfo* LoadChunkModel(const char* name) {
	PrintDebug("Loading chunk model: %s... ", name);

	std::string fullPath = "system\\models\\";
	fullPath = fullPath + name + ".sa2mdl";

	ModelInfo* mdl = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (mdl->getformat() != ModelFormat_Chunk) {
		PrintDebug("Failed!\n");
		delete mdl;
		return nullptr;
	}

	PrintDebug("Done.\n");
	return mdl;
}

void LoadModelListFuncPtr(const char** names, int count, ModelInfo** mdls, ModelInfo* (*func)(const char*)) {
	for (int i = 0; i < count; ++i) {
		mdls[i] = func(names[i]);
	}
}

void FreeMDL(ModelInfo* pointer) {
	if (pointer) {
		PrintDebug("Freeing model: %s...", pointer->getdescription().c_str());
		delete(pointer);
		pointer = nullptr;
	}
}

// Animation file functions

AnimationFile* LoadAnim(const char* name)
{
	PrintDebug("Loading Animation: %s... ", name);

	std::string fullPath = "system\\anims\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* anm = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (anm->getmodelcount() == 0) {
		PrintDebug("Failed\n");
		delete anm;
		anm = nullptr;
	}

	PrintDebug("Done\n");
	return anm;
}

void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions) 
{

	PrintDebug("Loading Animation: %s... ", name);

	std::string fullPath = "system\\anims\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* anm = new AnimationFile(helperFunctions.GetReplaceablePath(fullPath.c_str()));

	if (anm->getmodelcount() == 0) {
		delete anm;
		*info = nullptr;
	}
	else {
		*info = anm;
	}
};

inline AnimationFile* LoadANM(const char* type, const char* name) 
{

	PrintDebug("Loading Animation: %s... ", name);

	std::string fullPath = "system\\";
	fullPath = fullPath + type + "\\" + name + ".saanim";

	AnimationFile* temp = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (temp->getmodelcount()) {
		PrintDebug("Done.\n");
		return temp;
	}
	else {
		PrintDebug("Failed.\n");
		delete temp;
		return nullptr;
	}
}


void MoveForward(taskwk* entity, float speed) 
{
	njPushMatrix(_nj_unit_matrix_);
	njTranslateEx(&entity->pos);
	njRotateY(0, entity->ang.y);
	njRotateX(0, entity->ang.x);
	njTranslate(0, 0, 0, speed);
	njGetTranslation(0, &entity->pos);
	njPopMatrix(1u);
}

void LookAt(NJS_VECTOR* unit, Angle* outx, Angle* outy) 
{
	if (outy) {
		*outy = static_cast<Angle>(njArcTan2(unit->x, unit->z));
	}

	if (outx) {
		Float len = 1.0f / squareroot(unit->z * unit->z + unit->x * unit->x + unit->y * unit->y);

		*outx = static_cast<Angle>((njArcCos(len * 3.3499999f))
			- (njArcCos(-(len * unit->y))));
	}
}

void LookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy) 
{
	if (!from || !to)
		return;

	NJS_VECTOR unit = *to;

	njSubVector(&unit, from);

	if (outy) 
	{
		*outy = static_cast<Angle>(njArcTan2(unit.x, unit.z));
	}

	if (outx) 
	{
		if (from->y == to->y) 
		{
			*outx = 0;
		}
		else {
			Float len = 1.0f / squareroot(unit.z * unit.z + unit.x * unit.x + unit.y * unit.y);

			*outx = static_cast<Angle>((njArcCos(len * 3.3499999f))
				- (njArcCos(-(len * unit.y))));
		}
	}
}

void PlayerLookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy) 
{
	LookAt(from, to, outx, outy);

	if (outy) 
	{
		*outy = -(*outy) + 0x4000;
	}
}

float GetSquare(NJS_VECTOR* orig, NJS_VECTOR* dest) 
{
	return powf(dest->x - orig->x, 2) + powf(dest->y - orig->y, 2) + powf(dest->z - orig->z, 2);
}

float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest) 
{
	return sqrtf(GetSquare(orig, dest));
}

bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius) {
	return GetDistance(center, pos) <= radius;
}

int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius) {
	for (uint8_t player = 0; player < pMax; ++player) {
		if (!EntityData1Ptrs[player])
			continue;

		if (IsPointInsideSphere(center, &EntityData1Ptrs[player]->Position, radius)) {
			return player + 1;
		}
	}

	return 0;
}

void ResetPlayerLook(uint8_t pnum)
{
	auto p = playertwp[pnum];
	if (p) {
		p->ewp->look.ang = { 0, 0, 0 };
		p->ewp->look.mode = 0;
		p->ewp->look.obj = 0;
	}
}


bool IsPathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

//make sprite render properly
void SetSpriteParam()
{
	njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
	njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
	SetMaterial(1.0f, 1.0, 1.0f, 1.0f);
}

void ResetSpriteParam()
{
	ResetMaterial();
	njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
	njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
}

void ScaleUI(uiscale::Align type)
{
	HelperFunctionsGlobal.PushScaleUI((uiscale::Align)(type), false, 1.0f, 1.0f);
}

void ResetScaleUI()
{
	HelperFunctionsGlobal.PopScaleUI();
}


Float randomFloat()
{
	return (Float)rand() / RAND_MAX;
}