#include "pch.h"
#include "objects.h"
#include "tags.h"

extern std::vector<std::string>Subtitles;
extern std::vector<uint16_t>TimerSubtitles;
extern uint8_t actCount;
extern uint8_t copCount;
static bool cop = false;
static char actVisited = 0;

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
	restoreGraffitiTexs();
	isTagging = false;
}

void Sh_Disp_r(task* tp)
{
	if (MissedFrames)
		return;

	DrawTagHud();
}

void Sh_Exec_r(task* tp)
{
	auto twp = tp->twp;

	if (!TimeThing)
		return;

	if (tagsLeft[CurrentAct] > 0)
	{
		SetDebugFontSize(26);
		DisplayDebugStringFormatted(NJM_LOCATION(2, 2), "Tags Left: %d", tagsLeft[CurrentAct]);
	}

	char count = 0;

	switch (twp->mode)
	{
	case 0:
	case 1:
	case 2:
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

	tp->disp(tp);
}

void Rd_Highway_r(task* tp)
{
	task* exec = CreateElementalTask(2, 2, Sh_Exec_r);

	if (exec)
	{
		exec->disp = Sh_Disp_r;
		exec->dest = Sh_Delete_r;
	}

	if (!Subtitles.empty() && !cop)
	{
		CreateElementalTask(3, 2, Messages);
	}

	tp->exec = (TaskFuncPtr)Obj_SpeedHighway;
}

void init_SH()
{
	if (!tagLvl)
		return;

	RoundMasterList[LevelIDs_SpeedHighway] = Rd_Highway_r;
}