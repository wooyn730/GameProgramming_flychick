#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_texture_ending; // the SDL_Texture 
static SDL_Rect g_source_rectangle_ending; // the rectangle for source image
static SDL_Rect g_destination_rectangle_ending; // for destination


void Init_Ending()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/ending3.png");
	g_texture_ending = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_ending, NULL, NULL, &g_source_rectangle_ending.w, &g_source_rectangle_ending.h);
	g_destination_rectangle_ending.x = g_source_rectangle_ending.x = 0;
	g_destination_rectangle_ending.y = g_source_rectangle_ending.y = 0;
	g_destination_rectangle_ending.w = 800;
	g_destination_rectangle_ending.h = 600;

}

void Update_Ending()
{
}


void Render_Ending()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_ending, &g_source_rectangle_ending, &g_destination_rectangle_ending);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_Ending()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;

			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (Mix_PlayingMusic() == 1) {
					Mix_PauseMusic();
				}
				Clear_Ending();
				Sleep(100);
				g_current_game_phase = PHASE_INTRO;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
			break;

		default:
			break;
		}
	}
}


void Clear_Ending()
{
	SDL_DestroyTexture(g_texture_ending);
}