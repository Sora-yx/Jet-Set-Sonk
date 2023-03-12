#pragma once

void sprayPaint_Exec(task* tp);
void initSprayMdl();
void initGraffitiMdl();

void initSH_Objects();
void drawSprayPaintHand(taskwk* twp, playerwk* pwp);
void DrawSkatingEffects(playerwk* pwp);

extern ModelInfo* headPhone;
extern ModelInfo* goggles;