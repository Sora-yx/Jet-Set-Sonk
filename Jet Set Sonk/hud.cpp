#include "pch.h"
#include "tags.h"

void LoadLevelObj_r();
static FunctionHook<void> LoadLevelObj_t(LoadLevelObject, LoadLevelObj_r);

static const Float X = 40.0f;
static const Float Y = 48.0f;

static NJS_TEXANIM tagHudTexAnim = { X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 0, 0x20 };

static NJS_TEXANIM tagHudCount[] =
{
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 1, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 2, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 3, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 4, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 5, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 6, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 7, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 8, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 9, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 10, 0x20},
	{ X, Y, 32, 32, 0, 0, 0x0FF, 0x0FF, 11, 0x20},
};

static NJS_TEXNAME tagHudTex[12];
static NJS_TEXLIST tagHudTexlist = { arrayptrandlength(tagHudTex) };

static NJS_SPRITE tagSprite = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &tagHudTexlist, &tagHudTexAnim };

void DrawTagHud()
{
	ScaleUI(uiscale::Align_Automatic);

	SetSpriteParam();
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
