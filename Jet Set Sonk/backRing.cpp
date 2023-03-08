#include "pch.h"
#include "tags.h"

extern NJS_OBJECT object_GoalRing;
extern NJS_TEXLIST GoalRingTextures;

void ResetLevel();
bool isBackRing = false;
char timeMin = 0;
char timeSec = 0;
char timeFrame = 0;
uint8_t sprayBackup[pMax]{ 0 };
uint16_t ringBackup = 0;
uint8_t backupTagCount = 0;
int backupScore = 0;
int backupTimerHM = 0;
int backupSaveTimerHM = 0;

extern int16_t timerHM;
extern int16_t saveTimerHM;


void backRingSaveData()
{
	timeMin = TimeMinutes;
	timeSec = TimeSeconds;
	timeFrame = TimeFrames;
	ringBackup = Rings;
	isTagging = false;
	backupTagCount = tagCount;
	backupScore = Score;
	backupTimerHM = timerHM;
	backupSaveTimerHM = backupSaveTimerHM;


	for (uint8_t i = 0; i < pMax; i++)
	{
		sprayBackup[i] = sprayPaintCount[pMax];
	}

	isBackRing = true;
}

void backRingRestoreData()
{
	if (!isBackRing)
		return;

	TimeMinutes = timeMin;
	TimeSeconds = timeSec;
	TimeFrames = timeFrame;
	Rings = ringBackup;
	isTagging = false;
	tagCount = backupTagCount;

	for (uint8_t i = 0; i < pMax; i++)
	{
		sprayPaintCount[pMax] = sprayBackup[i];
	}

	timerHM = backupTimerHM;
	saveTimerHM = backupSaveTimerHM;
	isBackRing = false;
}

void BackRingDisp(task* tp)
{
	auto twp = tp->twp;

	if (!MissedFrames) {
		njSetTexture(&GoalRingTextures);
		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		njRotateY(0, twp->ang.y);
		DrawObject(&object_GoalRing);
		njPopMatrix(1);
	}
}


void BackRing(task* tp)
{
	if (CheckRangeOut(tp))
		return;

	auto twp = tp->twp;

	switch (twp->mode)
	{
	case 0:
		twp->pos.y += 35.0f;
		tp->disp = BackRingDisp;
		twp->mode++;
		break;
	case 1:

		twp->ang.y += 300;

		if (CheckCollisionP(&twp->pos, 40.0f))
		{
			for (uint8_t i = 0; i < pMax; i++)
			{
				if (playertwp[i])
				{
					playertwp[i]->smode = 20;
					playertwp[i]->flag |= Status_DoNextAction;
				}
			}

			backRingSaveData();
			twp->mode++;
		}
		break;
	case 2:
		ResetLevel();
		FreeTask(tp);
		return;
	}


	if (tp->disp)
		tp->disp(tp);
}
