#include "pch.h"

static constexpr char size = 2;

MusicInfo failMusic = { "fail", 0 };
MusicInfo clearMusic = { "clear", 0 };

MusicInfo newJingle[size] =
{
	failMusic, clearMusic
};

uint16_t jingleID[size] = { NULL };

void PlayFailJingle()
{
	ADXTaskInit();
	PlayJingle(jingleID[0]);
}


task* LoadMusicResult(LoadObj flags, int index, void(__cdecl* loadSub)(task*))
{
	if (isTagLevel() && CurrentCharacter == Characters_Sonic)
	{
		Load_DelayedSound_BGM(jingleID[1]);
		return nullptr;
	}

	return CreateElementalTask(flags, index, loadSub);
}


void init_jingle(HelperFunctions help)
{
	for (uint8_t i = 0; i < size; i++)
	{
		jingleID[i] = help.RegisterMusicFile(newJingle[i]);	
	}


	WriteCall((void*)0x41436F, LoadMusicResult);
}