#include "pch.h"
#include "objects.h"

static NJS_TEXNAME graffitiTex[4]{ 0 };
NJS_TEXLIST graffitiTexlist = { arrayptrandlength(graffitiTex) };

PVMEntry SpeedHighwayObjectTextures[] = {
	{ "OBJ_HIGHWAY", (TexList*)0x26703F0 },
	{ "OBJ_HIGHWAY2", (TexList*)0x26706AC },
	{ "NISEPAT", (TexList*)0x970F8C },
	{ "MILESRACE", (TexList*)0x91BFC0 },
	{ "SUPI_SUPI", (TexList*)0x96F518 },
	{ "TUBA", (TexList*)0x92F2BC },
	{ "KOAR", (TexList*)0x9359B4 },
	{ "WARA", (TexList*)0x93852C },
	{ "USA", (TexList*)0x93CF74 },
	{ "BANB", (TexList*)0x93A8BC },
	{ "UNI_A_UNIBODY", (TexList*)0x96CB5C },
	{ "TOGEBALL_TOGEBALL", (TexList*)0x96BC54 },
	{ "graffitiTex", &graffitiTexlist},
	{ 0 }
};

ObjectListEntry SpeedHighwayObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 4, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 1, 2250000, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A9140, "O KN HINT" } /* "O KN HINT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79F860, "SPRINGH" } /* "SPRINGH" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61C740, "O EV   " } /* "O EV   " */,
	{ 10, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61BDC0, "O FOUNT" } /* "O FOUNT" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61B500, "O CRANE" } /* "O CRANE" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x61AE80, "O GLASS " } /* "O GLASS " */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x61ACA0, "O GLASS2" } /* "O GLASS2" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x614E40, "HIGH RAFT A" } /* "HIGH RAFT A" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x614E60, "HIGH RAFT C" } /* "HIGH RAFT C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x61A330, "O TANKA" } /* "O TANKA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x619960, "O SIGNB" } /* "O SIGNB" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x619340, "O TurnAsi" } /* "O TurnAsi" */,
	{ 2, 3, 1, 25000000, 0, (ObjectFuncPtr)0x618AB0, "O SLIGHT" } /* "O SLIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6188E0, "O ARCADE01" } /* "O ARCADE01" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6188F0, "O ARCADE02" } /* "O ARCADE02" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x618900, "O ARCADE03" } /* "O ARCADE03" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x6186D0, "O JAMER" } /* "O JAMER" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x617C70, "O STP4S" } /* "O STP4S" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x617F00, "O STP4T" } /* "O STP4T" */,
	{ 14, 3, 1, 2250000, 0, (ObjectFuncPtr)0x618030, "O FLYST" } /* "O FLYST" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x617AE0, "O Post1" } /* "O Post1" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x617B10, "O Post4" } /* "O Post4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6178F0, "O Nbox1" } /* "O Nbox1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x617940, "O Nbox2" } /* "O Nbox2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x617990, "O Nbox3" } /* "O Nbox3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6179E0, "O Nbox4" } /* "O Nbox4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6177C0, "O Bench" } /* "O Bench" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x617780, "O FENCE" } /* "O FENCE" */,
	{ 6, 3, 1, 6250000, 0, (ObjectFuncPtr)0x617680, "O NEON1" } /* "O NEON1" */,
	{ 6, 3, 1, 6250000, 0, (ObjectFuncPtr)0x6176C0, "O NEON2" } /* "O NEON2" */,
	{ 6, 3, 1, 6250000, 0, (ObjectFuncPtr)0x617700, "O NEON3" } /* "O NEON3" */,
	{ 6, 3, 1, 6250000, 0, (ObjectFuncPtr)0x617740, "O NEON4" } /* "O NEON4" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x617420, "O POSTER0" } /* "O POSTER0" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x617440, "O POSTER1" } /* "O POSTER1" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x617460, "O POSTER2" } /* "O POSTER2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6173D0, "O SIGN1" } /* "O SIGN1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x617290, "O KANBANA" } /* "O KANBANA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x617330, "O KANBANB" } /* "O KANBANB" */,
	{ 2, 3, 1, 40000, 0, (ObjectFuncPtr)0x617160, "O BAKETU" } /* "O BAKETU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x616C90, "O HYDBASS" } /* "O HYDBASS" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x615810, "O GREEN" } /* "O GREEN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615830, "O GREENA" } /* "O GREENA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615880, "O GREENB" } /* "O GREENB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6158D0, "O GREEND" } /* "O GREEND" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x616450, "O LAMP" } /* "O LAMP" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x616770, "O CLIGHT" } /* "O CLIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6163D0, "O LAMP01" } /* "O LAMP01" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x616410, "O LAMP02" } /* "O LAMP02" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x616210, "O PinPin" } /* "O PinPin" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x616150, "O Escalator1" } /* "O Escalator1" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x6161B0, "O Escalator2" } /* "O Escalator2" */,
	{ 2, 3, 1, 4000000, 0, (ObjectFuncPtr)0x615EB0, "O Antena" } /* "O Antena" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615C60, "O Cone1" } /* "O Cone1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615CB0, "O Cone2" } /* "O Cone2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615990, "O Curb" } /* "O Curb" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615940, "O Fence02" } /* "O Fence02" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615920, "O GREENE" } /* "O GREENE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615780, "O SIBA01" } /* "O SIBA01" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6157D0, "O SIBA02" } /* "O SIBA02" */,
	{ 6, 3, 1, 250000, 0, (ObjectFuncPtr)0x615740, "O Tokei" } /* "O Tokei" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6155A0, "O Lmpa" } /* "O Lmpa" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615410, "O GG" } /* "O GG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x615450, "O FF" } /* "O FF" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x6153C0, "O StPlant01" } /* "O StPlant01" */,
	{ 2, 5, 0, 0, 0, (ObjectFuncPtr)0x615310, "O StPlant02" } /* "O StPlant02" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x613E30, "O HeliA" } /* "O HeliA" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x613E80, "O HeliB" } /* "O HeliB" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x615200, "O HW BELL" } /* "O HW BELL" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614ED0, "O HELIP L" } /* "O HELIP L" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614E80, "O TUNAGI" } /* "O TUNAGI" */,
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)0x614D80, "O RING2" } /* "O RING2" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0DF0, "SPINA A" } /* "SPINA A" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B0F40, "SPINA B" } /* "SPINA B" */,
	{ 2, 3, 4, 0, 0, (ObjectFuncPtr)0x4B1090, "SPINA C" } /* "SPINA C" */,
	{ 2, 3, 5, 360000, 0, (ObjectFuncPtr)0x4B3210, "E POLICE" } /* "E POLICE" */,
	{ 2, 3, 5, 360000, 0, (ObjectFuncPtr)0x4AF190, "E UNI A" } /* "E UNI A" */,
	{ 2, 3, 5, 360000, 0, (ObjectFuncPtr)0x4AF500, "E UNI B" } /* "E UNI B" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINT" } /* "O HINT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x79B2F0, "O GRING" } /* "O GRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614B00, "O GFENCE" } /* "O GFENCE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614B30, "O GCURB" } /* "O GCURB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614B60, "O GFENCE02" } /* "O GFENCE02" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614B90, "O GPINPIN" } /* "O GPINPIN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614BC0, "O GFF" } /* "O GFF" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614BF0, "O GRAFTA" } /* "O GRAFTA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614C20, "O GRAFTC" } /* "O GRAFTC" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614C50, "O GGRENA" } /* "O GGRENA" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614C80, "O GGRENB" } /* "O GGRENB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614CB0, "O GGREND" } /* "O GGREND" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x614CE0, "O GCLIGHT" } /* "O GCLIGHT" */,
	{ 15, 3, 1, 2250000, 0, (ObjectFuncPtr)0x4C07D0, "O ItemBoxAir" } /* "O ItemBoxAir" */,
	{ 2, 3, 1, 3240000, 0, (ObjectFuncPtr)0x614380, "MISSILE" }, /* "MISSILE" */
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)sprayPaint_Exec, "sprayPaint"},
	{ 2, 3, 1, 2250000, 0, (ObjectFuncPtr)tag_Exec, "graffiti" },
};

ObjectList SpeedHighwayObjectList = { arraylengthandptrT(SpeedHighwayObjectList_list, int) };


void initSH_ObjList()
{
	for (uint8_t i = 0; i < 3; i++)
	{
		ObjLists[LevelIDs_SpeedHighway * 8 + i] = &SpeedHighwayObjectList;
	}

	TexLists_Obj[LevelIDs_SpeedHighway] = SpeedHighwayObjectTextures;
}

void Obj_SH_r(task* tp)
{

	setNumberOfTagToDo();
	tp->exec = (TaskFuncPtr)Obj_SpeedHighway;
}

void initSH_Objects()
{
	RoundMasterList[LevelIDs_SpeedHighway] = Obj_SH_r;
	initSprayMdl();
	initGraffitiMdl();
	initSH_ObjList();
}