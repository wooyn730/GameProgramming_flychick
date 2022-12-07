#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_tex_opening; // the SDL_Texture 
static SDL_Rect g_source_rect_opening; // the rectangle for source image
static SDL_Rect g_dest_rect_opening; // for destination

void Init_opening()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/opening.png");
	g_tex_opening = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_tex_opening, NULL, NULL, &g_source_rect_opening.w, &g_source_rect_opening.h);
	g_dest_rect_opening.x = g_source_rect_opening.x = 0;
	g_dest_rect_opening.y = g_source_rect_opening.y = 0;
	g_dest_rect_opening.w = 800;
	g_dest_rect_opening.h = 600;
}

void Update_opening()
{
}


void Render_opening()
{
	//SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_tex_opening, &g_source_rect_opening, &g_dest_rect_opening);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_opening()
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
				Clear_opening();
				g_current_game_phase = PHASE_HOW2PLAY;
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


void Clear_opening()
{
	SDL_DestroyTexture(g_tex_opening);
}