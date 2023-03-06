#pragma once

#define Status_KillSound 0x4000

enum sound
{
	noSpraySnd,
	smallTagSnd,
	spray1Snd,
	spray2Snd,
	spray3Snd,
	spray4Snd,
	spray5Snd,
	sprayFinalSnd,
	sprayPaintSnd,
	sprayGrabSnd,
	policeVoice01 = 20,
	onishimaVoice01

};

void Sounds_Init();
void RunCustomSounds();
void PlayCustomSound(int ID);
void PlayCustomSoundVolume(int ID, float volume);




