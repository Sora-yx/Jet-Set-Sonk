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


void ResetPlayerLook(uint8_t pnum);

bool IsPathExist(const std::string& s);

void SetSpriteParam();
void ResetSpriteParam();
void ScaleUI(uiscale::Align type);
void ResetScaleUI();
Float randomFloat();
bool isTailsAI(uint8_t pnum);
bool isTagLevel();