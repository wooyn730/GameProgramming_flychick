#include "GameFunc.h"
#include "GamePhase.h"

static SDL_Texture* g_tex_how2; // the SDL_Texture 
static SDL_Rect g_source_rect_how2; // the rectangle for source image
static SDL_Rect g_dest_rect_how2; // for destination

void Init_how2()
{
	SDL_Surface* temp_surface = IMG_Load("../Resources/how2play.png");
	g_tex_how2 = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_tex_how2, NULL, NULL, &g_source_rect_how2.w, &g_source_rect_how2.h);
	g_dest_rect_how2.x = g_source_rect_how2.x = 0;
	g_dest_rect_how2.y = g_source_rect_how2.y = 0;
	g_dest_rect_how2.w = 800;
	g_dest_rect_how2.h = 600;

}

void Update_how2()
{
}


void Render_how2()
{
	//SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_tex_how2, &g_source_rect_how2, &g_dest_rect_how2);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_how2()
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
				Clear_how2();
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


void Clear_how2()
{
	SDL_DestroyTexture(g_tex_how2);
}