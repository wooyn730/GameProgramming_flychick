#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <time.h>


void InitGame();
void ClearGame();


extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern int g_current_game_phase;
extern SDL_Window* g_window;
