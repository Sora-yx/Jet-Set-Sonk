#include "pch.h"
#include "tags.h"

void LoadLevelObj_r();
static FunctionHook<void> LoadLevelObj_t(LoadLevelObject, LoadLevelObj_r);

static NJS_TEXANIM tagHudTexAnim = { 40.0f, 48.0f, 32, 32, 0, 0, 0x0FF, 0x0FF, 0, 0x20 };

static const Float tX = 40.0f;
static const Float tY = 40.0f;
static NJS_TEXANIM tagHudTimer[] =
{
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 0, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 1, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 2, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 3, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 4, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 5, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 6, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 7, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 8, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 9, 0x20},
	{ tX, tY, 32, 32, 0, 0, 0x0FF, 0x0FF, 10, 0x20},
};

static NJS_SPRITE tagTimer = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &CON_REGULAR_TEXLIST, tagHudTimer };

static NJS_TEXNAME tagHudTex[12];
static NJS_TEXLIST tagHudTexlist = { arrayptrandlength(tagHudTex) };

static NJS_SPRITE tagSprite = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &tagHudTexlist, &tagHudTexAnim };

extern int16_t timerHM;
void DrawTimerHud()
{
	if (!hardMode || timerHM <= 0 || !TimeThing)
		return;

	tagTimer.p.x = HorizontalStretch * 640.0f / 1.3f;
	tagTimer.p.y = 64.0f;

	if (timerHM < 100)
		SetMaterial(1.0f, 1.0f, 0.156f, 0.172f);
	else
		SetMaterial(1.0f, 1.0f, 0.505, 0.023);

	int firstDigit = timerHM;

	if (timerHM > 99)
	{
		while (firstDigit >= 10)
		{
			firstDigit /= 10;
		}

		late_DrawSprite2D(&tagTimer, firstDigit, 22046.496f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);
	}

	float diff = 36.0f;
	tagTimer.p.x += diff;
	late_DrawSprite2D(&tagTimer, timerHM % 100 / 10, 22046.496f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);
	tagTimer.p.x += diff;
	late_DrawSprite2D(&tagTimer, timerHM % 10, 22046.496f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);
}

void DrawSprayHud()
{
	tagSprite.p.x = 46.0f;
	tagSprite.p.y = VerticalStretch * 480.0f - 64.0f - 32.0f;
	late_DrawSprite2D(&tagSprite, 0, 22046.498f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);

	auto backup = Hud_RingTimeLife.p;
	auto count = sprayPaintCount[0];

	if (!count || count >= sprayPaintMax)
		SetMaterial(1.0f, 1.0f, 0.356f, 0.372f);

	Hud_RingTimeLife.p.x = 49.0f;
	Hud_RingTimeLife.p.y = tagSprite.p.y - 5.0f;
	late_DrawSprite2D(&Hud_RingTimeLife, sprayPaintCount[0] % 100 / 10, 22046.496f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);
	Hud_RingTimeLife.p.x += 16.0;
	late_DrawSprite2D(&Hud_RingTimeLife, sprayPaintCount[0] % 10, 22046.496f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR, LATE_LIG);
	Hud_RingTimeLife.p = backup;
}

void DrawHud()
{
	ScaleUI(uiscale::Align_Automatic);

	SetSpriteParam();

	DrawSprayHud();
	DrawTimerHud();

	ResetSpriteParam();
	ResetScaleUI();
}

void initHud()
{
	LoadPVM("tagHud", &tagHudTexlist);
}

void LoadLevelObj_r() 
{
	LoadLevelObj_t.Original();
	initHud();
}
