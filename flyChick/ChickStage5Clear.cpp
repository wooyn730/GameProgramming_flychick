#include "GameFunc.h"
#include "ChickStage5Clear.h"

static SDL_Texture* g_texture_stage5Clear; // the SDL_Texture 
static SDL_Rect g_source_rect_stage5Clear; // the rectangle for source image
static SDL_Rect g_dest_rect_stage5Clear; // for destination

//Mix_Music* g_stage5clear_music;


void Init_Stage5Clear()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/stage5_clear.png");
	g_texture_stage5Clear = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_stage5Clear, NULL, NULL, &g_source_rect_stage5Clear.w, &g_source_rect_stage5Clear.h);
	g_dest_rect_stage5Clear.x = g_source_rect_stage5Clear.x = 0;
	g_dest_rect_stage5Clear.y = g_source_rect_stage5Clear.y = 0;
	g_dest_rect_stage5Clear.w = 800;
	g_dest_rect_stage5Clear.h = 600;

	// stage clear sound
	/*Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	g_stage5clear_music = Mix_LoadMUS("../Resources/stageclear.mp3");
	Mix_FadeInMusic(g_stage5clear_music, -1, 1000);*/

}

void Update_Stage5Clear()
{
}


void Render_Stage5Clear()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_stage5Clear, &g_source_rect_stage5Clear, &g_dest_rect_stage5Clear);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_Stage5Clear()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			//Mix_FadeOutMusic(2000);

			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				//chick_position_return = true;
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


void Clear_Stage5Clear()
{
	SDL_DestroyTexture(g_texture_stage5Clear);
	/*Mix_FreeMusic(g_stage5clear_music);
	Mix_CloseAudio();*/
}