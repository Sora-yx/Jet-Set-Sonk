#include "pch.h"
#include "jingle.h"

static NJS_TEXNAME timeOverTex[3];
NJS_TEXLIST timeOverTexlist = { arrayptrandlength(timeOverTex) };
extern int16_t timerHM;
extern int16_t saveTimerHM;
extern int16_t saveTimerHMReset;


void backupTime()
{
	savepointPrintLaptime();
	saveTimerHM = timerHM;
}

static const Float tX = 300.0f;
static const Float tY = 100.0f;
static NJS_TEXANIM timeoverTexAnim[] =
{
	{ 400.0f, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 0, 0x20},
	{ tX, 90.0f, 32, 32, 0, 0, 0x0FF, 0x0FF, 1, 0x20},
	{ tX, 90.0f, 32, 32, 0, 0, 0x0FF, 0x0FF, 2, 0x20},
};

static NJS_SPRITE timerOverSprite = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &timeOverTexlist, timeoverTexAnim };

static int cursor = 0;
static Float scl = 0.05f;
void TimeOverDisp(task* tp)
{
	auto twp = tp->twp;

	if (twp->mode < 2 || MissedFrames)
		return;

	SetSpriteParam();

	Float a4 = VerticalStretch * 480.0f;
	Float a3 = HorizontalStretch * 640.0f;

	DrawRect_Queue(0.0, 0.0, a3, a4, 24000.9f, ScreenFade_Alpha << 24, QueuedModelFlagsB_SomeTextureThing);

	ScaleUI(uiscale::Align_Automatic);

	timerOverSprite.p.x = HorizontalStretch * 640 / 2 - 100.0f;
	timerOverSprite.p.y = 64.0f;

	if (twp->mode < 5)
	{
		timerOverSprite.sx = scl;
		timerOverSprite.sy = scl;
	}
	else
	{
		timerOverSprite.sx = 1.0f;
		timerOverSprite.sy = 1.0f;
	}

	late_DrawSprite2D(&timerOverSprite, 0, 25499.0f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR | NJD_SPRITE_ANGLE, LATE_LIG);


	if (twp->mode >= 5)
	{

		if (!cursor)
		{
			timerOverSprite.sx = scl;
			timerOverSprite.sy = scl;
		}

		timerOverSprite.p.x = 32.0f;
		timerOverSprite.p.y = VerticalStretch * 480.0f - 150.0f;

		late_DrawSprite2D(&timerOverSprite, 1, 25499.0f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);


		timerOverSprite.sx = 1.0f;
		timerOverSprite.sy = 1.0f;

		if (cursor)
		{
			timerOverSprite.sx = scl;
			timerOverSprite.sy = scl;
		}

		timerOverSprite.p.x = HorizontalStretch * 640.0f - 213.4f;
		late_DrawSprite2D(&timerOverSprite, 2, 25499.0f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);

		timerOverSprite.sx = 1.0f;
		timerOverSprite.sy = 1.0f;
	}

	ResetSpriteParam();
	ResetScaleUI();
}

void SH_ResetAllData();
extern task* TimeOverPtr;
uint8_t backupGameMode = 9;
void ResetLevel()
{
	if (TimeOverPtr)
		FreeTask(TimeOverPtr);

	timerHM = saveTimerHMReset;
	Set0Rings();
	PauseEnabled = 0;
	ResetTime();
	DisableTimeThing();
	ResetBigStuff();
	ResetRestartData();
	ResetGravity();
	SH_ResetAllData();

	if (!CurrentAct)
	{
		GameState = 0xc;
	}		
	else
	{
		backupGameMode = (uint8_t)GameMode;
		GameMode = GameModes_Adventure_Field;
		GameState = 0xB;
	}
}

static void DeleteTimeOver(task* tp)
{
	TimeOverPtr = nullptr;
}


void TimeOver(task* tp)
{
	auto twp = tp->twp;

	switch (twp->mode)
	{
	case 0:

		tp->dest = DeleteTimeOver;
		tp->disp = TimeOverDisp;

		if ((uint8_t)GameMode == (uint8_t)GameModes_Adventure_Field)
			GameMode = (GameModes)backupGameMode;

		twp->mode++;
		break;
	case 1:
		if (TimeThing)
		{
			if (FrameCounterUnpaused % 60 == 0)
			{
				if (timerHM > 0)
					timerHM--;
			}
		}
		

		if (timerHM <= 0)
		{
			if (FrameCounterUnpaused % 70 == 0)
				twp->mode++;
		}

		break;
	case 2:
		for (uint8_t i = 0; i < pMax; i++)
		{
			if (playertwp[i])
			{
				playertwp[i]->smode = 20;
				playertwp[i]->flag |= Status_DoNextAction;
			}
		}

		DisableControl();
		ADX_Close();
		dsStop_all();
		TimeThing = 0;
		DisablePause();
		PlayFailJingle();
		___njSetBackColor(0xFF000000, 0xFF000000, 0xFF000000);
		ScreenFade_Timer = 0;
		ScreenFade_Alpha = 255;
		ScreenFade_Enabled = 0;
		twp->mode++;
		break;
	case 3:

		if (++twp->wtimer == 60)
		{
			twp->wtimer = 0;
			PlayVoice(1841);
			twp->mode++;
		}
		break;
	case 4:
		if (++twp->wtimer == 60)
		{
			if (GameMode == GameModes_Trial)
			{
				StartLevelCutscene(1);
				FreeTask(tp);
			}
			else
			{
				twp->mode++;
			}

		}
		break;
	case 5:
		if (!cursor)
		{
			if (PressedButtons[0] & Buttons_Right)
			{
				PlayMenuBipSound();
				cursor++;
			}
			else if (PressedButtons[0] & (Buttons_A | Buttons_Start))
			{
				PlayMenuEnterSound();
				ResetLevel();
				FreeTask(tp);
				return;
			}
		}
		else
		{
			if (PressedButtons[0] & Buttons_Left)
			{
				PlayMenuBipSound();
				cursor--;
			}
			else if (PressedButtons[0] & (Buttons_A | Buttons_Start))
			{
				PlayMenuBackSound();
				StartLevelCutscene(1);
				FreeTask(tp);
				return;
			}
		}

		break;
	}


	if (scl < 1.1f)
		scl += 0.005f;
	else
		scl = 1.0f;

	if (tp->disp)
		tp->disp(tp);
}

void init_HardMode()
{
	if (!hardMode)
		return;

	WriteCall((void*)0x44F649, backupTime);
}