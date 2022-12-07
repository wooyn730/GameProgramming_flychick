#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_texture_stage1Clear; // the SDL_Texture 
static SDL_Rect g_source_rect_stage1Clear; // the rectangle for source image
static SDL_Rect g_dest_rect_stage1Clear; // for destination

static SDL_Texture* arrow_texture;
static SDL_Rect arrow_rect;
static SDL_Rect arrow_dest_rect;

Mix_Chunk* g_stageclear_music;


void Init_Stage1Clear()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/stage1_clear.png");
	g_texture_stage1Clear = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_stage1Clear, NULL, NULL, &g_source_rect_stage1Clear.w, &g_source_rect_stage1Clear.h);
	g_dest_rect_stage1Clear.x = g_source_rect_stage1Clear.x = 0;
	g_dest_rect_stage1Clear.y = g_source_rect_stage1Clear.y = 0;
	g_dest_rect_stage1Clear.w = 800;
	g_dest_rect_stage1Clear.h = 600;

	SDL_Surface* arrow_surface = IMG_Load("../Resources/Arrow.png");
	arrow_texture = SDL_CreateTextureFromSurface(g_renderer, arrow_surface);
	SDL_FreeSurface(arrow_surface);

	SDL_QueryTexture(arrow_texture, NULL, NULL, &arrow_rect.w, &arrow_rect.h);
	arrow_dest_rect.x = 700;
	arrow_dest_rect.y = 500;
	arrow_dest_rect.w = arrow_rect.w / 20;
	arrow_dest_rect.h = arrow_rect.h/20;

	// stage clear sound
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	g_stageclear_music = Mix_LoadWAV("../Resources/stageclear.wav");
	Mix_VolumeChunk(g_stageclear_music, MIX_MAX_VOLUME); //스테이지 클리어 소리 최대로

}

void Update_Stage1Clear()
{
}


void Render_Stage1Clear()
{
	//SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_stage1Clear, &g_source_rect_stage1Clear, &g_dest_rect_stage1Clear);

	SDL_RenderCopy(g_renderer, arrow_texture, &arrow_rect, &arrow_dest_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_Stage1Clear()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;

			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > arrow_dest_rect.x &&
					mouse_y > arrow_dest_rect.y &&
					mouse_x < arrow_dest_rect.x + arrow_dest_rect.w &&
					mouse_y < arrow_dest_rect.y + arrow_dest_rect.h)
				{
					Clear_Stage1Clear();
					Init_Stage2();
					startTime_s2 = SDL_GetTicks();
					g_current_game_phase = PHASE_STAGE2;
				}
			}
		}
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				Clear_Stage1Clear();
				Init_Stage2();
				startTime_s2 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE2;
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


void Clear_Stage1Clear()
{
	SDL_DestroyTexture(g_texture_stage1Clear);
	SDL_DestroyTexture(arrow_texture);
	Mix_FreeChunk(g_stageclear_music);
	Mix_CloseAudio();
}