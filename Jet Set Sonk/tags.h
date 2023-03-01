#pragma once

extern bool isTagging;

extern NJS_TEXLIST graffitiTexlist;
extern uint8_t tagsLeft[];
extern uint8_t tagCount;

void setNumberOfTagToDo();
void tag_Exec(task* tp);

