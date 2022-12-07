#include "GameFunc.h"
#include "GamePhase.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
static Uint32 g_last_time_ms;

int g_current_game_phase;


int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Mix_OpenAudio " << Mix_GetError() << std::endl;
		exit(1);
	}

	g_window = SDL_CreateWindow("fly, chick!", 100, 100, 800, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();
	Init_Intro();
	//Init_Stage1();
	//Init_Stage2();
	//Init_Stage3();
	//Init_Stage4();
	//Init_Stage5();
	//Init_GameOver();
	//Init_Ending();
	//Init_Infinite();
	//Init_Stage1Clear();
	//Init_Stage2Clear();
	//Init_Stage3Clear();
	//Init_Stage4Clear();
	Init_opening();
	Init_how2();

	g_current_game_phase = PHASE_OPENING;

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running)
	{

		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		if (g_current_game_phase == PHASE_INTRO)
		{
			Mix_Pause(1);
			Mix_Pause(2);
			if (Mix_PlayingMusic() == 0) {
				Mix_FadeInMusic(g_intro_music, -1, 4000);
			}
			HandleEvents_Intro();
			Update_Intro();
			Render_Intro();
		}
		else if (g_current_game_phase == PHASE_STAGE1)
		{
			HandleEvents_Stage1();
			Update_Stage1();
			Render_Stage1();
		}
		else if (g_current_game_phase == PHASE_STAGE2)
		{
			HandleEvents_Stage2();
			Update_Stage2();
			Render_Stage2();
		}
		else if (g_current_game_phase == PHASE_STAGE3)
		{
			HandleEvents_Stage3();
			Update_Stage3();
			Render_Stage3();
		}
		else if (g_current_game_phase == PHASE_STAGE4)
		{
			HandleEvents_Stage4();
			Update_Stage4();
			Render_Stage4();
		}
		else if (g_current_game_phase == PHASE_STAGE5)
		{
			HandleEvents_Stage5();
			Update_Stage5();
			Render_Stage5();
		}
		else if (g_current_game_phase == PHASE_GAMEOVER)
		{
			if (Mix_PlayingMusic() == 1) {
				Mix_HaltMusic();
				Mix_PlayChannel(1, g_gameover_music, 0);
			}
			HandleEvents_GameOver();
			Update_GameOver();
			Render_GameOver();
		}
		else if (g_current_game_phase == PHASE_ENDING)
		{
			if (Mix_PlayingMusic() == 1) {
				Mix_HaltMusic();
				Mix_PlayChannel(2, g_ending_music, 0);
			}
			HandleEvents_Ending();
			Update_Ending();
			Render_Ending();
		}
		else if (g_current_game_phase == PHASE_INFINITE)
		{
			HandleEvents_Infinite();
			Update_Infinite();
			Render_Infinite();
		}
		else if (g_current_game_phase == PHASE_STAGE1CLEAR)
		{
			HandleEvents_Stage1Clear();
			Update_Stage1Clear();
			Render_Stage1Clear();
		}
		else if (g_current_game_phase == PHASE_STAGE2CLEAR)
		{
			HandleEvents_Stage2Clear();
			Update_Stage2Clear();
			Render_Stage2Clear();
		}
		else if (g_current_game_phase == PHASE_STAGE3CLEAR)
		{
			HandleEvents_Stage3Clear();
			Update_Stage3Clear();
			Render_Stage3Clear();
		}
		else if (g_current_game_phase == PHASE_STAGE4CLEAR)
		{
			HandleEvents_Stage4Clear();
			Update_Stage4Clear();
			Render_Stage4Clear();
		}
		else if (g_current_game_phase == PHASE_OPENING)
		{
			HandleEvents_opening();
			Update_opening();
			Render_opening();
		}
		else if (g_current_game_phase == PHASE_HOW2PLAY)
		{
			HandleEvents_how2();
			Update_how2();
			Render_how2();
		}

		g_last_time_ms = cur_time_ms;

	}

	Clear_Intro();
	Clear_Stage1();
	Clear_Stage2();
	Clear_Stage3();
	Clear_Stage4();
	Clear_Stage5();
	Clear_GameOver();
	Clear_Ending();
	Clear_Infinite();
	Clear_Stage1Clear();
	Clear_Stage2Clear();
	Clear_Stage3Clear();
	Clear_Stage4Clear();
	Clear_opening();
	Clear_how2();
	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	TTF_Quit();
	SDL_Quit();

	return 0;
}