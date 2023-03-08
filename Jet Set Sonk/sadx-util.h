#pragma once

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
VoidFunc(savepointPrintLaptime, 0x44F2D0);
VoidFunc(PlayMenuBipSound, 0x6FC8A0);
VoidFunc(PlayMenuEnterSound, 0x505810);
VoidFunc(PlayMenuBackSound, 0x505830);
DataPointer(char, SoftResetByte, 0x3B0EAA0);
FunctionPointer(Sint32, DeleteLandAndObj, (), 0x414090);

DataPointer(particle_info, particleWater, 0x97E27C);


DataPointer(NJS_TEXANIM, MissionSpriteAnim, 0x917784);