#include "GameFunc.h"
#include "GamePhase.h"
#define FENCE_NUM 65

// Background
static SDL_Texture* g_texture; // the SDL_Texture 
static SDL_Rect g_source_rectangle; // the rectangle for source image
static SDL_Rect g_destination_rectangle; // for destination

// Chick
static SDL_Texture* chick_sheet_texture;
static SDL_Rect chick_rect[4];
static SDL_Rect chick_destination_rect;

static bool chick_go_up;
static double chick_x;
static double chick_y;

static int chick_fly_sprite_num;
static int chick_current_fly_index;

//펜스
static SDL_Texture* fence_sheet_texture;
static SDL_Texture* fence_sheet_texture2;
static SDL_Rect fence_rect[FENCE_NUM];
static SDL_Rect fence_destination_rect[FENCE_NUM];

static int fence_x[FENCE_NUM];
static int fence_y[FENCE_NUM];

// title
static SDL_Texture* g_stage4_title;
static SDL_Rect g_stage4_title_rect;
static SDL_Rect g_stage4_title_des_rect;

// Timer
SDL_Texture* timer_texture_s4;
SDL_Rect timer_texture_rect_s4;
SDL_Rect timer_destination_rect_s4;
int time_ms_s4;
Uint32 startTime_s4;

void Init_Stage4()
{
	srand((unsigned int)time(NULL));

	SDL_Surface* bg_surface = IMG_Load("../Resources/stage4_bg.png");
	g_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);

	SDL_QueryTexture(g_texture, NULL, NULL, &g_source_rectangle.w, &g_source_rectangle.h);
	g_destination_rectangle.x = g_source_rectangle.x = 0;
	g_destination_rectangle.y = g_source_rectangle.y = 0;
	g_destination_rectangle.w = 800;
	g_destination_rectangle.h = 600;


	// For Chick
	chick_go_up = false;
	chick_x = 150;
	chick_y = 150;

	chick_fly_sprite_num = 4;
	chick_current_fly_index = 0;

	SDL_Surface* chick_sheet_surface = IMG_Load("../Resources/ari_sheet.png");
	chick_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, chick_sheet_surface);
	SDL_FreeSurface(chick_sheet_surface);

	// chick sheet  x, y, w, h
	chick_rect[0] = { 27, 1532, 340, 359 };
	chick_rect[1] = { 447, 1540, 342, 361 };
	chick_rect[2] = { 867, 1536, 348, 370 };
	chick_rect[3] = { 1285, 1514, 330, 395 };

	chick_destination_rect.x = (int)chick_x;
	chick_destination_rect.y = (int)chick_y;
	chick_destination_rect.w = chick_rect[0].w / 5;
	chick_destination_rect.h = chick_rect[0].h / 5;

	//펜스
	fence_x[0] = 250;
	fence_y[0] = 370;

	SDL_Surface* fence_surface = IMG_Load("../Resources/icicle.png");
	SDL_SetColorKey(fence_surface, SDL_TRUE, SDL_MapRGB(fence_surface->format, 255, 255, 255));
	fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
	SDL_FreeSurface(fence_surface);

	SDL_QueryTexture(fence_sheet_texture, NULL, NULL, &fence_rect[0].w, &fence_rect[0].h);

	fence_destination_rect[0].x = (int)fence_x[0];
	fence_destination_rect[0].y = (int)fence_y[0];
	fence_destination_rect[0].w = fence_rect[0].w;
	fence_destination_rect[0].h = fence_rect[0].h;

	for (int i = 1; i < FENCE_NUM; i++) {
		fence_x[i] = 250 + (i * fence_rect[0].w);

			if ((i % 10) >= 0 && (i % 10) <= 4)
			{
				fence_y[i] = fence_y[0] + rand() % 150 - 75;

				SDL_Surface* fence_surface = IMG_Load("../Resources/icicle.png");
				fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
				SDL_FreeSurface(fence_surface);

				SDL_QueryTexture(fence_sheet_texture, NULL, NULL, &fence_rect[i].w, &fence_rect[i].h);
				fence_destination_rect[i].x = (int)fence_x[i];
				fence_destination_rect[i].y = fence_y[i];
				fence_destination_rect[i].w = fence_rect[i].w;
				fence_destination_rect[i].h = fence_rect[i].h;
			}
			else
			{
				fence_y[i] = -200 + rand() % 150 - 55;

				SDL_Surface* fence_surface2 = IMG_Load("../Resources/icicle2.png");
				fence_sheet_texture2 = SDL_CreateTextureFromSurface(g_renderer, fence_surface2);
				SDL_FreeSurface(fence_surface2);

				SDL_QueryTexture(fence_sheet_texture2, NULL, NULL, &fence_rect[i].w, &fence_rect[i].h);
				fence_destination_rect[i].x = (int)fence_x[i];
				fence_destination_rect[i].y = fence_y[i];
				fence_destination_rect[i].w = fence_rect[i].w;
				fence_destination_rect[i].h = fence_rect[i].h;
			}

	}


	// 스테이지 타이틀
	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* stage4_title_surface = TTF_RenderText_Blended(font1, "STAGE 4", black);
	g_stage4_title = SDL_CreateTextureFromSurface(g_renderer, stage4_title_surface);


	g_stage4_title_rect.x = 0;
	g_stage4_title_rect.y = 0;
	g_stage4_title_rect.w = stage4_title_surface->w;
	g_stage4_title_rect.h = stage4_title_surface->h;

	g_stage4_title_des_rect.x = 350;
	g_stage4_title_des_rect.y = 20;
	g_stage4_title_des_rect.w = g_stage4_title_rect.w;
	g_stage4_title_des_rect.h = g_stage4_title_rect.h;


	time_ms_s4 = 0;
	timer_texture_s4 = 0;
	startTime_s4 = 0;

	//해제
	SDL_FreeSurface(stage4_title_surface);
	TTF_CloseFont(font1);
}

void HandleEvents_Stage4()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {

		switch (event.type)
		{
		case SDL_QUIT:
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				chick_go_up = true;
				Mix_PlayChannel(-1, chick_sound, 0);
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				chick_go_up = false;
			}

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				Clear_Stage4();
				Init_Stage4Clear();
				Sleep(100);
				g_current_game_phase = PHASE_STAGE4CLEAR;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
		}
	}
}

// 시간을 texture로 변환시키는 함수
//void UpdateTimeTexture_s4(int ms)
//{
//	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
//	SDL_Color skyblue = { 53, 183, 232, 0 };
//
//	if (timer_texture_s4 != 0)
//	{
//		SDL_DestroyTexture(timer_texture_s4);
//		timer_texture_s4 = 0;
//	}
//	SDL_Surface* timer_surface = TTF_RenderText_Blended(font1, std::to_string(ms / 1000).c_str(), skyblue);
//
//	timer_texture_rect_s4.x = 700;
//	timer_texture_rect_s4.y = 20;
//	timer_texture_rect_s4.w = timer_surface->w;
//	timer_texture_rect_s4.h = timer_surface->h;
//
//	timer_texture_s4 = SDL_CreateTextureFromSurface(g_renderer, timer_surface);
//
//	SDL_FreeSurface(timer_surface);
//}

void Update_Stage4()
{

	//아리 날갯짓
	if (chick_go_up == true)
	{
		chick_y -= 10;
		chick_destination_rect.y = (int)chick_y;

		chick_current_fly_index++;

		if (chick_current_fly_index >= chick_fly_sprite_num - 1)
		{
			chick_current_fly_index = 1;
		}
	}
	if (chick_go_up == false)
	{
		chick_y += 5;
		chick_destination_rect.y = (int)chick_y;
	}

	// Timer
	Uint32 current_ticks = SDL_GetTicks();

	if (g_flag_running == TRUE)
	{
		time_ms_s4 = current_ticks - startTime_s4;
		//UpdateTimeTexture_s4(time_ms_s4);
	}

	timer_destination_rect_s4.x = 750;
	timer_destination_rect_s4.y = 20;
	timer_destination_rect_s4.w = timer_texture_rect_s4.w;
	timer_destination_rect_s4.h = timer_texture_rect_s4.h;

	//펜스 움직임
	for (int i = 0; i < FENCE_NUM; i++) {
		fence_x[i] -= 5;
		fence_destination_rect[i].x = (int)fence_x[i];

		if ((i % 10) >= 0 && (i % 10) <= 4) //아래 고드름
		{
			if (chick_x - 20 < fence_x[i] && chick_x + 20 > fence_x[i])
			{
				if (chick_y >= fence_y[i] - 30.0) // 68 72
				{
					Clear_Stage4();
					Init_GameOver();
					Sleep(100);
					g_current_game_phase = PHASE_GAMEOVER;
				}
			}
		}
		else //위 고드름
		{
			if (chick_x - 20 < fence_x[i] && chick_x + 20 > fence_x[i])
			{
				if (chick_y < fence_y[i] + 375.0) // 68 72
				{
					Clear_Stage4();
					Init_GameOver();
					Sleep(100);
					g_current_game_phase = PHASE_GAMEOVER;
				}
			}
		}
	}

	// 위아래로 사라지면 게임오버
	if (chick_y > 600 || chick_y < 0)
	{
		Clear_Stage4();
		Init_GameOver();
		Sleep(100);
		g_current_game_phase = PHASE_GAMEOVER;
	}

	//clear 판정
	if ((int)time_ms_s4 / 1000 >= 40)
	{
		Clear_Stage4();
		Init_Stage4Clear();
		Sleep(100);
		g_current_game_phase = PHASE_STAGE4CLEAR;
	}

}

void Render_Stage4()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture, &g_source_rectangle, &g_destination_rectangle);

	for (int i = 0; i < FENCE_NUM; i++)
	{
		if ((i % 10) >= 0 && (i % 10) <= 4)
			SDL_RenderCopy(g_renderer, fence_sheet_texture, &fence_rect[i], &fence_destination_rect[i]);
		else
			SDL_RenderCopy(g_renderer, fence_sheet_texture2, &fence_rect[i], &fence_destination_rect[i]);
	}

	SDL_RenderCopy(g_renderer, chick_sheet_texture,
		&chick_rect[chick_current_fly_index],
		&chick_destination_rect);

	SDL_RenderCopy(g_renderer, g_stage4_title, &g_stage4_title_rect, &g_stage4_title_des_rect);

	SDL_RenderCopy(g_renderer, timer_texture_s4, 0, &timer_destination_rect_s4);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Clear_Stage4()
{
	SDL_DestroyTexture(g_texture);
	SDL_DestroyTexture(chick_sheet_texture);
	SDL_DestroyTexture(fence_sheet_texture);
	SDL_DestroyTexture(g_stage4_title);
	SDL_DestroyTexture(timer_texture_s4);
}