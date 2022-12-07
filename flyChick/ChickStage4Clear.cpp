#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_texture_stage4Clear; // the SDL_Texture 
static SDL_Rect g_source_rect_stage4Clear; // the rectangle for source image
static SDL_Rect g_dest_rect_stage4Clear; // for destination

static SDL_Texture* arrow_texture;
static SDL_Rect arrow_rect;
static SDL_Rect arrow_dest_rect;


void Init_Stage4Clear()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/stage4_clear.png");
	g_texture_stage4Clear = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_stage4Clear, NULL, NULL, &g_source_rect_stage4Clear.w, &g_source_rect_stage4Clear.h);
	g_dest_rect_stage4Clear.x = g_source_rect_stage4Clear.x = 0;
	g_dest_rect_stage4Clear.y = g_source_rect_stage4Clear.y = 0;
	g_dest_rect_stage4Clear.w = 800;
	g_dest_rect_stage4Clear.h = 600;

	SDL_Surface* arrow_surface = IMG_Load("../Resources/Arrow.png");
	arrow_texture = SDL_CreateTextureFromSurface(g_renderer, arrow_surface);
	SDL_FreeSurface(arrow_surface);

	SDL_QueryTexture(arrow_texture, NULL, NULL, &arrow_rect.w, &arrow_rect.h);
	arrow_dest_rect.x = 700;
	arrow_dest_rect.y = 500;
	arrow_dest_rect.w = arrow_rect.w / 20;
	arrow_dest_rect.h = arrow_rect.h / 20;

}

void Update_Stage4Clear()
{
}


void Render_Stage4Clear()
{
	//SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_stage4Clear, &g_source_rect_stage4Clear, &g_dest_rect_stage4Clear);

	SDL_RenderCopy(g_renderer, arrow_texture, &arrow_rect, &arrow_dest_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_Stage4Clear()
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
					Clear_Stage4Clear();
					Init_Stage5();
					startTime_s5 = SDL_GetTicks();
					g_current_game_phase = PHASE_STAGE5;
				}
			}
		}
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				Clear_Stage4Clear();
				Init_Stage5();
				startTime_s5 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE5;
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


void Clear_Stage4Clear()
{
	SDL_DestroyTexture(g_texture_stage4Clear);
	SDL_DestroyTexture(arrow_texture);
}