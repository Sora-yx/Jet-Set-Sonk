#pragma once

void sprayPaint_Exec(task* tp);
void initSprayMdl();
void initGraffitiMdl();
void tag_Exec(task* tp);

extern NJS_TEXLIST graffitiTexlist;

void initSH_Objects();
bool isTag();
void drawSprayPaintHand(taskwk* twp, playerwk* pwp);
void DrawSkatingEffects(playerwk* pwp);
