#include "pch.h"
#include "objects.h"
#include "tags.h"
#include "jingle.h"
#include "backring.h"

#define replaceSET(a, b) HelperFunctionsGlobal.ReplaceFile("system\\" a ".bin", "system\\" b ".bin")

extern std::vector<std::string>Subtitles;
extern std::vector<uint16_t>TimerSubtitles;
extern uint8_t actCount;
extern uint8_t copCount;
static bool cop = false;
static char actVisited = 0;
extern int16_t timerHM;
extern int16_t saveTimerHM;

static FunctionHook<void, int> RunLevelDestructor_t(RunLevelDestructor);

StartPosition SH1Pos = { LevelIDs_SpeedHighway, 1, {-220, 42, 0}, 0 };

enum
{
	init,
	countCheck,
	wait,
	copMsg1,
	copMsg2,
	copMsg3,
	done
};

const char* police_message0[] = {
	"",
	NULL,
};

const char* police_message1[] = {
	"",
	NULL,
};

const char* police_message2[] = {
	"",
	NULL,
};

const char* onishima_message0[] = {
	"",
	NULL,
};

const char* onishima_message1[] = {
	"",
	NULL,
};

const char* onishima_message2[] = {
	"",
	NULL,
};

void ConvertStringsToSADXFormat()
{
	police_message0[0] = Subtitles.at(0).data();
	police_message1[0] = Subtitles.at(1).data();
	police_message2[0] = Subtitles.at(2).data();

	onishima_message0[0] = Subtitles.at(3).data();
	onishima_message1[0] = Subtitles.at(4).data();
	onishima_message2[0] = Subtitles.at(5).data();
}

static void Messages(task* tp)
{
	auto twp = tp->twp;

	switch (twp->mode)
	{
	case init:
		ConvertStringsToSADXFormat();
		twp->mode++;
		break;
	case countCheck:
		if (tagCount >= copCount)
		{
			twp->mode++;
		}
		break;
	case wait:
		if (++twp->wtimer == 60)
		{
			twp->wtimer = 0;
			twp->mode++;
		}
		break;
	case copMsg1:
		PlayCustomSoundVolume(policeVoice01, 1);
		DisplayHintText(police_message0, TimerSubtitles[0]);
		twp->mode++;
		break;
	case copMsg2:
		if (++twp->wtimer >= TimerSubtitles[0] + 40)
		{
			twp->wtimer = 0;
			DisplayHintText(police_message1, TimerSubtitles[1]);
			twp->mode++;
		}
		break;
	case copMsg3:
		if (++twp->wtimer >= TimerSubtitles[1] + 20)
		{
			DisplayHintText(police_message2, TimerSubtitles[2]);
			twp->mode++;
		}
		break;
	case done:
		cop = true;
		FreeTask(tp);
		return;
	}
}

void Sh_Delete_r(task* tp)
{
	//tagsLeft[CurrentAct] = 0;
	resetSprayCount();
	restoreGraffitiTexs();

	if (hardMode)
		timerHM = saveTimerHM;

	isTagging = false;
}

void Sh_Disp_r(task* tp)
{
	if (MissedFrames)
		return;

	DrawHud();
}

static int backringTimer = 0;
void Sh_Exec_r(task* tp)
{
	auto twp = tp->twp;

	if (tagsLeft[CurrentAct] > 0)
	{
		if (!tp->ctp || tp->ctp->twp->mode < 2)
		{
			SetDebugFontSize(26);
			DisplayDebugStringFormatted(NJM_LOCATION(2, 2), "Tags Left: %d", tagsLeft[CurrentAct]);
		}

	}

	if (useBackRing)
	{
		++backringTimer;

		if (backringTimer >= 0 && backringTimer <= 60)
			camera_twp->pos = playertwp[0]->pos;

		if (backringTimer >= 100)
		{
			EnableControl();

			for (uint8_t i = 0; i < pMax; i++)
			{
				if (playertwp[i])
				{
					CharColliOn(playertwp[i]);
				}
			}
	
			backringTimer = 0;
			useBackRing = false;
		}
	}

	char count = 0;

	LoopTaskC(tp);

	switch (twp->mode)
	{
	case 0:
	case 1:
	case 2:

		if (TimeThing)
		{

			if (CurrentAct == twp->mode)
			{
				if (++twp->wtimer == 20)
				{
					twp->wtimer = 0;
					setNumberOfTagToDo();

					if (actVisited == twp->mode)
						actVisited++;

					twp->mode++;
				}
			}
		}
		break;
	case 9:
		if (++twp->wtimer == 60)
		{
			LoadLevelResults();
			FreeTask(tp);
			return;
		}
	}

	if (twp->mode != 9)
	{

		for (uint8_t i = 0; i < actMax; i++)
		{
			if (tagsLeft[i] == 0)
			{
				count++;
			}

			if (count == actMax && tagCount > 0 && actCount == actVisited)
			{
				twp->mode = 9;
			}
		}
	}

	if (tp->disp)
		tp->disp(tp);
}

void TimeOver(task* tp);

void Rd_Highway_r(task* tp)
{
	for (uint8_t i = 0; i < pMax; i++)
	{
		if (playertwp[i] && playertwp[i]->counter.b[1] == Characters_Sonic)
		{
			task* exec = CreateElementalTask(2, 2, Sh_Exec_r);

			if (exec)
			{
				exec->disp = Sh_Disp_r;
				exec->dest = Sh_Delete_r;

				if (hardMode)
					CreateChildTask(2, TimeOver, exec);
			}

			if (!Subtitles.empty() && !cop)
			{
				CreateElementalTask(3, 2, Messages);
			}

			break;
		}
	}

	tp->exec = (TaskFuncPtr)Obj_SpeedHighway;
}

void SH_ResetAllData()
{
	backringTimer = 0;
	useBackRing = false;
	resetSprayCount();
	memset(tagsLeft, 0, sizeof(uint8_t) * actMax);
	tagCount = 0;
	actVisited = 0;
}

void __cdecl RunLevelDestructor_r(int heap)
{
	if (heap == 0)
	{
		SH_ResetAllData();
	}

	RunLevelDestructor_t.Original(heap);
}

void init_SH()
{
	if (!tagLvl)
		return;

	RoundMasterList[LevelIDs_SpeedHighway] = Rd_Highway_r;
	HelperFunctionsGlobal.RegisterStartPosition(Characters_Sonic, SH1Pos);
	RunLevelDestructor_t.Hook(RunLevelDestructor_r);

	if (hardMode)
	{
		replaceSET("SET0400S", "SET0400S_HM");
		replaceSET("SET0401S", "SET0401S_HM");
		replaceSET("SET0402S", "SET0402S_HM");
		replaceSET("SET0400S_DC", "SET0400S_HM");
		replaceSET("SET0401S_DC", "SET0401S_HM");
		replaceSET("SET0402S_DC", "SET0402S_HM");
	}
	else
	{
		replaceSET("SET0400S", "SET0400S_NM");
		replaceSET("SET0401S", "SET0401S_NM");
		replaceSET("SET0402S", "SET0402S_NM");
		replaceSET("SET0400S_DC", "SET0400S_NM");
		replaceSET("SET0401S_DC", "SET0401S_NM");
		replaceSET("SET0402S_DC", "SET0402S_NM");
	}
}