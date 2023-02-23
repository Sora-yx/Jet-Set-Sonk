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

static void(__cdecl** NodeCallbackFuncPtr)(NJS_OBJECT* obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;


using ModelFuncPtr = void(__cdecl*)(NJS_OBJECT*);
DataPointer(ModelFuncPtr, ObjectDraw, 0x3AB9878);


using ModelFuncPtr2 = void(__cdecl*)(NJS_MODEL_SADX*, int, float);
DataPointer(ModelFuncPtr2, _DrawModel_func, 0x3ABD95C);

DataPointer(DWORD, CallbackModelAttributes, 0x03ABD9A4);
