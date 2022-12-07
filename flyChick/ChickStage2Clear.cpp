#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_texture_stage2Clear; // the SDL_Texture 
static SDL_Rect g_source_rect_stage2Clear; // the rectangle for source image
static SDL_Rect g_dest_rect_stage2Clear; // for destination

static SDL_Texture* arrow_texture;
static SDL_Rect arrow_rect;
static SDL_Rect arrow_dest_rect;

void Init_Stage2Clear()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/stage2_clear.png");
	g_texture_stage2Clear = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_stage2Clear, NULL, NULL, &g_source_rect_stage2Clear.w, &g_source_rect_stage2Clear.h);
	g_dest_rect_stage2Clear.x = g_source_rect_stage2Clear.x = 0;
	g_dest_rect_stage2Clear.y = g_source_rect_stage2Clear.y = 0;
	g_dest_rect_stage2Clear.w = 800;
	g_dest_rect_stage2Clear.h = 600;

	SDL_Surface* arrow_surface = IMG_Load("../Resources/Arrow.png");
	arrow_texture = SDL_CreateTextureFromSurface(g_renderer, arrow_surface);
	SDL_FreeSurface(arrow_surface);

	SDL_QueryTexture(arrow_texture, NULL, NULL, &arrow_rect.w, &arrow_rect.h);
	arrow_dest_rect.x = 700;
	arrow_dest_rect.y = 500;
	arrow_dest_rect.w = arrow_rect.w / 20;
	arrow_dest_rect.h = arrow_rect.h / 20;

}

void Update_Stage2Clear()
{
}


void Render_Stage2Clear()
{
	//SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_stage2Clear, &g_source_rect_stage2Clear, &g_dest_rect_stage2Clear);

	SDL_RenderCopy(g_renderer, arrow_texture, &arrow_rect, &arrow_dest_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_Stage2Clear()
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
					Clear_Stage2Clear();
					Init_Stage3();
					startTime_s3 = SDL_GetTicks();
					g_current_game_phase = PHASE_STAGE3;
				}
			}
		}
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				Clear_Stage2Clear();
				Init_Stage3();
				startTime_s3 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE3;
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


void Clear_Stage2Clear()
{
	SDL_DestroyTexture(g_texture_stage2Clear);
	SDL_DestroyTexture(arrow_texture);
}