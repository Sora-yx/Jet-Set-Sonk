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
