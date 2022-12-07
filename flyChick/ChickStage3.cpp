#include "GameFunc.h"
#include "GamePhase.h"
#define FENCE_NUM 30

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
static SDL_Rect fence_rect[FENCE_NUM];
static SDL_Rect fence_destination_rect[FENCE_NUM];

static int fence_x[FENCE_NUM];
static int fence_y[FENCE_NUM];

//해파리
static SDL_Texture* obstacle_sheet_tex;
static SDL_Rect obstacle_rect[2];
static SDL_Rect obstacle_des_rect[2];

static int obstacle_x[2];
static int obstacle_y[2];

// title
static SDL_Texture* g_stage3_title;
static SDL_Rect g_stage3_title_rect;
static SDL_Rect g_stage3_title_des_rect;

// Timer
SDL_Texture* timer_texture_s3;
SDL_Rect timer_texture_rect_s3;
SDL_Rect timer_destination_rect_s3;
int time_ms_s3;
Uint32 startTime_s3;

void Init_Stage3()
{
	srand((unsigned int)time(NULL));

	SDL_Surface* bg_surface = IMG_Load("../Resources/stage3_bg.png");
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

	chick_fly_sprite_num = 3;
	chick_current_fly_index = 0;

	SDL_Surface* chick_sheet_surface = IMG_Load("../Resources/water_ari.png");
	SDL_SetColorKey(chick_sheet_surface, SDL_TRUE, SDL_MapRGB(chick_sheet_surface->format, 255, 255, 255));
	chick_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, chick_sheet_surface);
	SDL_FreeSurface(chick_sheet_surface);

	// chick sheet  x, y, w, h
	chick_rect[0] = { 109,56,440,466 };
	chick_rect[1] = { 630,53,445,469 };
	chick_rect[2] = { 1148,52,445,469 };

	chick_destination_rect.x = (int)chick_x;
	chick_destination_rect.y = (int)chick_y;
	chick_destination_rect.w = chick_rect[0].w / 6.5;
	chick_destination_rect.h = chick_rect[0].h / 6.5;


	//미역
	fence_x[0] = 250;
	fence_y[0] = 370;

	SDL_Surface* fence_surface = IMG_Load("../Resources/seaweed.png");
	SDL_SetColorKey(fence_surface, SDL_TRUE, SDL_MapRGB(fence_surface->format, 255, 255, 255));
	fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
	SDL_FreeSurface(fence_surface);

	SDL_QueryTexture(fence_sheet_texture, NULL, NULL, &fence_rect[0].w, &fence_rect[0].h);

	fence_destination_rect[0].x = (int)fence_x[0];
	fence_destination_rect[0].y = (int)fence_y[0];
	fence_destination_rect[0].w = fence_rect[0].w;
	fence_destination_rect[0].h = fence_rect[0].h;

	for (int i = 1; i < FENCE_NUM; i++) {
		fence_x[i] = 250 + (i * 2 * fence_rect[0].w);
		fence_y[i] = fence_y[i - 1] + rand() % 100 - 50;
		if (fence_y[i] > 400 || fence_y[i] < 270)
		{
			i--;
		}
		else
		{
			SDL_Surface* fence_surface = IMG_Load("../Resources/seaweed.png");
			fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
			SDL_FreeSurface(fence_surface);

			SDL_QueryTexture(fence_sheet_texture, NULL, NULL, &fence_rect[i].w, &fence_rect[i].h);
			fence_destination_rect[i].x = (int)fence_x[i];
			fence_destination_rect[i].y = fence_y[i];
			fence_destination_rect[i].w = fence_rect[i].w;
			fence_destination_rect[i].h = fence_rect[i].h;
		}
	}

	//상단 장애물

	obstacle_x[0] = 800;
	obstacle_y[0] = 230;

	obstacle_x[1] = 800;
	obstacle_y[1] = 70;

	SDL_Surface* ob_surface = IMG_Load("../Resources/ob.png");
	obstacle_sheet_tex = SDL_CreateTextureFromSurface(g_renderer, ob_surface);
	SDL_FreeSurface(ob_surface);

	obstacle_rect[0] = { 255, 34, 64, 77 };
	obstacle_rect[1] = { 257, 137, 65, 78 };
	obstacle_des_rect[0].x = (int)obstacle_x[0];
	obstacle_des_rect[0].y = (int)obstacle_y[0];
	obstacle_des_rect[0].w = 64;
	obstacle_des_rect[0].h = 77;

	obstacle_des_rect[1].x = (int)obstacle_x[1];
	obstacle_des_rect[1].y = (int)obstacle_y[1];
	obstacle_des_rect[1].w = 65;
	obstacle_des_rect[1].h = 78;


	// 스테이지 타이틀
	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* stage3_title_surface = TTF_RenderText_Blended(font1, "STAGE 3", black);
	g_stage3_title = SDL_CreateTextureFromSurface(g_renderer, stage3_title_surface);


	g_stage3_title_rect.x = 0;
	g_stage3_title_rect.y = 0;
	g_stage3_title_rect.w = stage3_title_surface->w;
	g_stage3_title_rect.h = stage3_title_surface->h;

	g_stage3_title_des_rect.x = 350;
	g_stage3_title_des_rect.y = 20;
	g_stage3_title_des_rect.w = g_stage3_title_rect.w;
	g_stage3_title_des_rect.h = g_stage3_title_rect.h;


	time_ms_s3 = 0;
	timer_texture_s3 = 0;
	startTime_s3 = 0;

	//해제
	SDL_FreeSurface(stage3_title_surface);
	TTF_CloseFont(font1);
}

void HandleEvents_Stage3()
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
				Clear_Stage3();
				Init_Stage3Clear();
				Sleep(100);
				g_current_game_phase = PHASE_STAGE3CLEAR;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
		}
	}
}

// 시간을 texture로 변환시키는 함수
//void UpdateTimeTexture_s3(int ms)
//{
//	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
//	SDL_Color skyblue = { 53, 183, 232, 0 };
//
//	if (timer_texture_s3 != 0)
//	{
//		SDL_DestroyTexture(timer_texture_s3);
//		timer_texture_s3 = 0;
//	}
//	SDL_Surface* timer_surface = TTF_RenderText_Blended(font1, std::to_string(ms / 1000).c_str(), skyblue);
//
//	timer_texture_rect_s3.x = 700;
//	timer_texture_rect_s3.y = 20;
//	timer_texture_rect_s3.w = timer_surface->w;
//	timer_texture_rect_s3.h = timer_surface->h;
//
//	timer_texture_s3 = SDL_CreateTextureFromSurface(g_renderer, timer_surface);
//
//	SDL_FreeSurface(timer_surface);
//}

void Update_Stage3()
{
	//아리 날갯짓
	if (chick_go_up == true)
	{
		chick_y -= 10;
		chick_destination_rect.y = (int)chick_y;

		chick_current_fly_index++;

		if (chick_current_fly_index >= chick_fly_sprite_num - 1)
		{
			chick_current_fly_index = 0;
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
		time_ms_s3 = current_ticks - startTime_s3;
		//UpdateTimeTexture_s3(time_ms_s3);
	}

	timer_destination_rect_s3.x = 750;
	timer_destination_rect_s3.y = 20;
	timer_destination_rect_s3.w = timer_texture_rect_s3.w;
	timer_destination_rect_s3.h = timer_texture_rect_s3.h;

	//펜스 움직임과 충돌
	for (int i = 0; i < FENCE_NUM; i++) {
		fence_x[i] -= 5;
		fence_destination_rect[i].x = (int)fence_x[i];

		if (chick_x - 40 < fence_x[i] && chick_x + 40 > fence_x[i])
		{
			if (chick_y >= fence_y[i] - 5.0) // 68 72
			{
				Clear_Stage3();
				Init_GameOver();
				Sleep(100);
				g_current_game_phase = PHASE_GAMEOVER;
			}
		}
	}

	//상단 장애물 (해파리1
	if (((int)time_ms_s3 / 100) % 100 == 0) {
		obstacle_x[0] = 800;
	}
	else {
		obstacle_x[0] -= 3;
		obstacle_des_rect[0].x = (int)obstacle_x[0];
	}
	//2
	if (((int)time_ms_s3 / 100) % 70 == 0) {
		obstacle_x[1] = 800;
	}
	else {
		obstacle_x[1] -= 8;
		obstacle_des_rect[1].x = (int)obstacle_x[1];
	}
	//해파리 충돌
	for (int i = 0; i < 2; i++) {
		if (chick_x + 60 > obstacle_x[i] && chick_x - 55 < obstacle_x[i])
		{
			if (chick_y - 64 < obstacle_y[i] && chick_y + 67 > obstacle_y[i]) // 68 72
			{
				Clear_Stage3();
				Init_GameOver();
				Sleep(100);
				g_current_game_phase = PHASE_GAMEOVER;
			}
		}
	}

	// 위아래로 사라지면 게임오버
	if (chick_y > 600 || chick_y < 0)
	{
		Clear_Stage3();
		Init_GameOver();
		Sleep(100);
		g_current_game_phase = PHASE_GAMEOVER;
	}

	//clear 판정
	if ((int)time_ms_s3 / 1000 >= 35)
	{
		Clear_Stage3();
		Init_Stage3Clear();
		Sleep(100);
		g_current_game_phase = PHASE_STAGE3CLEAR;
	}

}

void Render_Stage3()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture, &g_source_rectangle, &g_destination_rectangle);

	for (int i = 0; i < FENCE_NUM; i++)
	{
		SDL_RenderCopyEx(g_renderer, fence_sheet_texture, &fence_rect[i], &fence_destination_rect[i], 0, 0, SDL_FLIP_HORIZONTAL);
	}

	SDL_RenderCopy(g_renderer, obstacle_sheet_tex, &obstacle_rect[0], &obstacle_des_rect[0]);
	SDL_RenderCopy(g_renderer, obstacle_sheet_tex, &obstacle_rect[1], &obstacle_des_rect[1]);

	SDL_RenderCopy(g_renderer, chick_sheet_texture,
		&chick_rect[chick_current_fly_index],
		&chick_destination_rect);

	SDL_RenderCopy(g_renderer, g_stage3_title, &g_stage3_title_rect, &g_stage3_title_des_rect);

	SDL_RenderCopy(g_renderer, timer_texture_s3, 0, &timer_destination_rect_s3);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Clear_Stage3()
{
	SDL_DestroyTexture(g_texture);
	SDL_DestroyTexture(chick_sheet_texture);
	SDL_DestroyTexture(fence_sheet_texture);
	SDL_DestroyTexture(obstacle_sheet_tex);
	SDL_DestroyTexture(g_stage3_title);
	SDL_DestroyTexture(timer_texture_s3);
}