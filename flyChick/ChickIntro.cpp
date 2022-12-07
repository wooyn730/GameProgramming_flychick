#include "GameFunc.h"
#include "GamePhase.h"
#include "SDL_mixer.h"

static SDL_Texture* g_texture_intro; // the SDL_Texture 
static SDL_Rect g_source_rectangle_intro; // the rectangle for source image
static SDL_Rect g_destination_rectangle_intro; // for destination

static SDL_Texture* title_texture_intro;
static SDL_Rect title_rect;
static SDL_Rect title_destination_rect;

static SDL_Texture* story_texture_intro;
static SDL_Rect story_rect;
static SDL_Rect story_destination_rect;

static SDL_Texture* infinity_texture_intro;
static SDL_Rect infinity_rect;
static SDL_Rect infinity_destination_rect;

Mix_Music* g_intro_music;

POINT ptMouse;



void Init_Intro()
{
	SDL_Surface* intro_bg_surface = IMG_Load("../Resources/intro_bg.png");
	g_texture_intro = SDL_CreateTextureFromSurface(g_renderer, intro_bg_surface);
	SDL_FreeSurface(intro_bg_surface);

	SDL_QueryTexture(g_texture_intro, NULL, NULL, &g_source_rectangle_intro.w, &g_source_rectangle_intro.h);
	g_destination_rectangle_intro.x = g_source_rectangle_intro.x = 0;
	g_destination_rectangle_intro.y = g_source_rectangle_intro.y = 0;
	g_destination_rectangle_intro.w = 800;
	g_destination_rectangle_intro.h = 600;

	SDL_Surface* title_surface = IMG_Load("../Resources/title.png");
	title_texture_intro = SDL_CreateTextureFromSurface(g_renderer, title_surface);
	SDL_FreeSurface(title_surface);

	SDL_QueryTexture(title_texture_intro, NULL, NULL, &title_rect.w, &title_rect.h);
	title_destination_rect.x = 30;
	title_destination_rect.y = 100;
	title_destination_rect.w = title_rect.w / 1.2;
	title_destination_rect.h = title_rect.h / 1.2;

	SDL_Surface* infinity_surface = IMG_Load("../Resources/infinitymode_button.png");
	infinity_texture_intro = SDL_CreateTextureFromSurface(g_renderer, infinity_surface);
	SDL_FreeSurface(infinity_surface);

	SDL_QueryTexture(infinity_texture_intro, NULL, NULL, &infinity_rect.w, &infinity_rect.h);
	infinity_destination_rect.x = 150;
	infinity_destination_rect.y = 400;
	infinity_destination_rect.w = infinity_rect.w / 8;
	infinity_destination_rect.h = infinity_rect.h / 8;

	SDL_Surface* story_surface = IMG_Load("../Resources/storymode_button.png");
	story_texture_intro = SDL_CreateTextureFromSurface(g_renderer, story_surface);
	SDL_FreeSurface(story_surface);

	SDL_QueryTexture(story_texture_intro, NULL, NULL, &story_rect.w, &story_rect.h);
	story_destination_rect.x = 490;
	story_destination_rect.y = 400;
	story_destination_rect.w = story_rect.w / 8;
	story_destination_rect.h = story_rect.h / 8;

	
	//background music
	// intro music
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	g_intro_music = Mix_LoadMUS("../Resources/intro_bg.mp3");
	Mix_FadeInMusic(g_intro_music, -1, 1000);

}

void Update_Intro()
{
}


void Render_Intro()
{
	//(g_renderer, 255, 255, 255, 255);
	//SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture_intro, &g_source_rectangle_intro, &g_destination_rectangle_intro);

	SDL_RenderCopy(g_renderer, title_texture_intro, &title_rect, &title_destination_rect);

	SDL_RenderCopy(g_renderer, infinity_texture_intro, &infinity_rect, &infinity_destination_rect);

	SDL_RenderCopy(g_renderer, story_texture_intro, &story_rect, &story_destination_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}



void HandleEvents_Intro()
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

				if (mouse_x > story_destination_rect.x &&
					mouse_y > story_destination_rect.y &&
					mouse_x < story_destination_rect.x + story_destination_rect.w &&
					mouse_y < story_destination_rect.y + story_destination_rect.h)
				{
					Init_Stage1();
					startTime_s1 = SDL_GetTicks();
					g_current_game_phase = PHASE_STAGE1;
				}

				else if (mouse_x > infinity_destination_rect.x &&
					mouse_y > infinity_destination_rect.y &&
					mouse_x < infinity_destination_rect.x + infinity_destination_rect.w &&
					mouse_y < infinity_destination_rect.y + infinity_destination_rect.h)
				{
					Init_Infinite();
					startTime = SDL_GetTicks();
					g_current_game_phase = PHASE_INFINITE;
				}
			}

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
			else if (event.key.keysym.sym == SDLK_0) //0 누르면 무한
			{
				Init_Infinite();
				startTime = SDL_GetTicks();
				g_current_game_phase = PHASE_INFINITE;
			}
			else if (event.key.keysym.sym == SDLK_1) //1 누르면 스테이지1
			{
				Init_Stage1();
				startTime_s1 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE1;
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				Init_Stage2();
				startTime_s2 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE2;
			}
			else if (event.key.keysym.sym == SDLK_3)
			{
				Init_Stage3();
				startTime_s3 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE3;
			}
			else if (event.key.keysym.sym == SDLK_4)
			{
				Init_Stage4();
				startTime_s4 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE4;
			}
			else if (event.key.keysym.sym == SDLK_5)
			{
				Init_Stage5();
				startTime_s5 = SDL_GetTicks();
				g_current_game_phase = PHASE_STAGE5;
			}

		default:
			break;
		}
		}
	}
}


void Clear_Intro()
{
	SDL_DestroyTexture(g_texture_intro);
	SDL_DestroyTexture(title_texture_intro);
	SDL_DestroyTexture(infinity_texture_intro);
	SDL_DestroyTexture(story_texture_intro);

	Mix_FreeMusic(g_intro_music);
	Mix_CloseAudio();
}