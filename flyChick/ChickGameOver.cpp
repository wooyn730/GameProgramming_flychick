#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_texture_gameover; // the SDL_Texture 
static SDL_Rect g_source_rectangle_gameover; // the rectangle for source image
static SDL_Rect g_destination_rectangle_gameover; // for destination

static SDL_Texture* gameover_subtitle_texture; 
static SDL_Rect gameover_rect;
static SDL_Rect gameover_destination_rect;

Mix_Chunk* g_gameover_music;

void Init_GameOver()
{
	//배경
	SDL_Surface* temp_surface = IMG_Load("../Resources/intro_bg.png"); 
	g_texture_gameover = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_gameover, NULL, NULL, &g_source_rectangle_gameover.w, &g_source_rectangle_gameover.h);
	g_destination_rectangle_gameover.x = g_source_rectangle_gameover.x = 0;
	g_destination_rectangle_gameover.y = g_source_rectangle_gameover.y = 0;
	g_destination_rectangle_gameover.w = 800;
	g_destination_rectangle_gameover.h = 600;

	//게임 오버 글씨
	SDL_Surface* gameover_subtitle_surface = IMG_Load("../Resources/gameover_subtitle.png");
	SDL_SetColorKey(gameover_subtitle_surface, SDL_TRUE, SDL_MapRGB(gameover_subtitle_surface->format, 255, 255, 255));
	gameover_subtitle_texture = SDL_CreateTextureFromSurface(g_renderer, gameover_subtitle_surface);
	SDL_FreeSurface(gameover_subtitle_surface);

	SDL_QueryTexture(gameover_subtitle_texture, NULL, NULL, &gameover_rect.w, &gameover_rect.h);
	gameover_destination_rect.x = 55;
	gameover_destination_rect.y = 200;
	gameover_destination_rect.w = gameover_rect.w / 1.5;
	gameover_destination_rect.h = gameover_rect.h / 1.5;

	// game over sound
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	g_gameover_music = Mix_LoadWAV("../Resources/gameover.wav");

}

void Update_GameOver()
{
}


void Render_GameOver()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_gameover, &g_source_rectangle_gameover, &g_destination_rectangle_gameover);

	SDL_RenderCopy(g_renderer, gameover_subtitle_texture, &gameover_rect, &gameover_destination_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen

}



void HandleEvents_GameOver()
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
				g_current_game_phase = PHASE_INTRO;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				Clear_GameOver();
				g_flag_running = false;
			}
			break;

		default:
			break;
		}
	}
}


void Clear_GameOver()
{
	SDL_DestroyTexture(g_texture_gameover);
	SDL_DestroyTexture(gameover_subtitle_texture);
	Mix_FreeChunk(g_gameover_music);
	Mix_CloseAudio();
}