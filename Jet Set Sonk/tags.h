#pragma once

extern bool isTagging;
static const uint8_t sprayPaintMax = 20;

extern NJS_TEXLIST graffitiTexlist;
extern uint8_t tagsLeft[];
extern uint8_t sprayPaintCount[];
extern uint8_t tagCount;

void setNumberOfTagToDo();
void tag_Exec(task* tp);

void restoreGraffitiTexs();
void DrawHud();
void resetSprayCount();