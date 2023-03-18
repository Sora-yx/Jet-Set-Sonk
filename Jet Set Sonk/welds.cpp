#include "pch.h"
#include <sstream>

std::vector<PL_JOIN_VERTEX> so_jvlist;
IniFile* file_so_jvlist = nullptr;

void SetIndices(std::string indices, std::vector<uint16_t>& points)
{
	std::stringstream ss(indices);
	std::string out;
	const char de = ', ';
	while (std::getline(ss, out, de))
	{
		points.push_back(stoi(out));
	}
}

PL_JOIN_VERTEX BuildJVListEntry(NJS_OBJECT* arr[], int base, int mdlA, int mdlB, int type, std::string indices)
{
	PL_JOIN_VERTEX jvEntry = {};

	jvEntry.objptr = (NJS_OBJECT*)arr[base];
	jvEntry.srcobj = (NJS_OBJECT*)arr[mdlA];
	jvEntry.inpmode = type;
	jvEntry.dstdepth = 0;
	jvEntry.org = 0;
	jvEntry.srcdepth = 0;

	if (mdlB == 0)
	{
		jvEntry.dstobj = 0;
		jvEntry.numVertex = 0;
		jvEntry.pnum = 0;
	}
	else
	{
		std::vector<uint16_t> points;
		SetIndices(indices, points);
		jvEntry.dstobj = (NJS_OBJECT*)arr[mdlB];
		jvEntry.numVertex = (points.size() / 2);
		uint16_t* ind_arr = new uint16_t[points.size()];
		for (int i = 0; i != points.size(); i++)
			ind_arr[i] = points.data()[i];
		jvEntry.pnum = ind_arr;
	}

	return jvEntry;
}

void CreateJVList(NJS_OBJECT* arr[], IniFile* ini, std::vector<PL_JOIN_VERTEX>& jvlist)
{
	int i = 0;
	while (ini->hasGroup(std::to_string(i)))
	{
		std::string s = std::to_string(i);
		int base = ini->getInt(s, "BaseModel");
		int mdlA = ini->getInt(s, "ModelA");
		int mdlB = ini->getInt(s, "ModelB");
		int type = ini->getInt(s, "WeldType");
		std::string indices = ini->getString(s, "VertIndexes", "");

		PL_JOIN_VERTEX jvEntry = BuildJVListEntry(arr, base, mdlA, mdlB, type, indices);
		jvlist.push_back(jvEntry);

		i++;
	}

	jvlist.push_back({ 0 });

	delete ini;
}

static void __cdecl InitNPCSonicWeldInfo_r()
{
	memcpy(NPCSonicWeldInfo, so_jvlist.data(), sizeof(WeldInfo) * 15);
	NPCSonicWeldInfo[15] = {};
}

void SonicJVList()
{
	file_so_jvlist = new IniFile(std::string(modpath) + "\\system\\welds\\so_jvlist.ini");

	if (file_so_jvlist)
	{
		CreateJVList(SONIC_OBJECTS, file_so_jvlist, so_jvlist);
		WriteData((PL_JOIN_VERTEX**)0x49AB7E, so_jvlist.data());
		WriteData((PL_JOIN_VERTEX**)0x49ABAC, so_jvlist.data());
		WriteData((PL_JOIN_VERTEX**)0x49AC3C, so_jvlist.data());
		WriteData((PL_JOIN_VERTEX**)0x49ACB6, so_jvlist.data());


		WriteJump(InitNPCSonicWeldInfo, InitNPCSonicWeldInfo_r);

		return;
		//npc welds
		WriteData((PL_JOIN_VERTEX**)0x7D27BA, so_jvlist.data());
		//WriteData((PL_JOIN_VERTEX**)0x7D30A0, so_jvlist.data());
		WriteData((PL_JOIN_VERTEX**)0x7D58B1, so_jvlist.data());
		WriteData((PL_JOIN_VERTEX**)0x7D5D21, so_jvlist.data());
	}
}