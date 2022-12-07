#pragma once

#include "ChickIntro.h"
#include "ChickOpening.h"
#include "ChickHow2.h"
#include "ChickGameOver.h"
#include "ChickEnding.h"

#include "ChickInfinite.h"

#include "ChickStage1.h"
#include "ChickStage2.h"
#include "ChickStage3.h"
#include "ChickStage4.h"
#include "ChickStage5.h"

#include "ChickStage1Clear.h"
#include "ChickStage2Clear.h"
#include "ChickStage3Clear.h"
#include "ChickStage4Clear.h"

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_INFINITE = 1;
const int PHASE_GAMEOVER = 2;
const int PHASE_ENDING = 3;

const int PHASE_STAGE1 = 4;
const int PHASE_STAGE1CLEAR = 5;
const int PHASE_STAGE2 = 6;
const int PHASE_STAGE2CLEAR = 7;
const int PHASE_STAGE3 = 8;
const int PHASE_STAGE3CLEAR = 9;
const int PHASE_STAGE4 = 10;
const int PHASE_STAGE4CLEAR = 11;
const int PHASE_STAGE5 = 12;

const int PHASE_OPENING = 13;
const int PHASE_HOW2PLAY = 14;

extern Uint32 startTime;
extern Uint32 startTime_s1;
extern Uint32 startTime_s2;
extern Uint32 startTime_s3;
extern Uint32 startTime_s4;
extern Uint32 startTime_s5;

extern Mix_Music* g_intro_music;
extern Mix_Chunk* g_ending_music;
extern Mix_Chunk* g_stageclear_music;
extern Mix_Chunk* g_gameover_music;
extern Mix_Chunk* chick_sound;
