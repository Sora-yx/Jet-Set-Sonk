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

void PlayClearJingle()
{
	ADXTaskInit();
	PlayJingle(jingleID[1]);
}

void init_jingle(HelperFunctions help)
{
	for (uint8_t i = 0; i < size; i++)
	{
		jingleID[i] = help.RegisterMusicFile(newJingle[i]);	
	}
}