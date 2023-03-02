#pragma once

ModelInfo* LoadBasicModel(const char* name);

ModelInfo* LoadChunkModel(const char* name);

void LoadModelListFuncPtr(const char** names, int count, ModelInfo** mdls, ModelInfo* (*func)(const char*));

void FreeMDL(ModelInfo* pointer);

AnimationFile* LoadAnim(const char* name);

inline AnimationFile* LoadANM(const char* type, const char* name);

void LookAt(NJS_VECTOR* unit, Angle* outx, Angle* outy);
void LookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy);
void PlayerLookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy);
void MoveForward(taskwk* entity, float speed);

float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
bool IsPointInsideSphere(NJS_VECTOR* center, NJS_VECTOR* pos, float radius);
int IsPlayerInsideSphere_(NJS_VECTOR* center, float radius);

static void(__cdecl** NodeCallbackFuncPtr)(NJS_OBJECT* obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;


using ModelFuncPtr = void(__cdecl*)(NJS_OBJECT*);
DataPointer(ModelFuncPtr, ObjectDraw, 0x3AB9878);


using ModelFuncPtr2 = void(__cdecl*)(NJS_MODEL_SADX*, int, float);
DataPointer(ModelFuncPtr2, _DrawModel_func, 0x3ABD95C);

DataPointer(DWORD, CallbackModelAttributes, 0x03ABD9A4);
FunctionPointer(int, SetCPFlag, (task* a1), 0x46C110);
FunctionPointer(void, CreateWater, (NJS_POINT3* pos, NJS_POINT3* spd, float scl), 0x4B9540);
TaskFunc(SetFlagNoRespawn, 0x46C100);
FunctionPointer(void, SetLookingPoint, (unsigned __int8 player, NJS_POINT3* a2), 0x441000);

void ResetPlayerLook(uint8_t pnum);

bool IsPathExist(const std::string& s);

void SetSpriteParam();
void ResetSpriteParam();
void ScaleUI(uiscale::Align type);
void ResetScaleUI();