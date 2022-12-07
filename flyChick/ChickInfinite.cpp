#include "GameFunc.h"
#include "GamePhase.h"
#define FENCE_NUM 180

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
static SDL_Rect fence_rect;
static SDL_Rect fence_destination_rect[FENCE_NUM];

static int fence_x[FENCE_NUM];
static int fence_y[FENCE_NUM];

//점수구현
int time_score;
char score_buffer[20];
Uint32 startTime;

SDL_Texture* g_score_tex;
SDL_Rect g_score_rect;

// clear 폰트
SDL_Texture* g_clear_font;
SDL_Rect g_clear_font_rect;

void Init_Infinite()
{

	SDL_Surface* bg_surface = IMG_Load("../Resources/intro_bg.png");
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
	SDL_SetColorKey(chick_sheet_surface, SDL_TRUE, SDL_MapRGB(chick_sheet_surface->format, 255, 255, 255));
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

	////////
	//펜스
	fence_x[0] = 250;
	fence_y[0] = 370;

	SDL_Surface* fence_surface = IMG_Load("../Resources/fence2.png");
	fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
	SDL_FreeSurface(fence_surface);

	SDL_QueryTexture(fence_sheet_texture, NULL, NULL, &fence_rect.w, &fence_rect.h);

	fence_destination_rect[0].x = (int)fence_x[0];
	fence_destination_rect[0].y = (int)fence_y[0];
	fence_destination_rect[0].w = fence_rect.w;
	fence_destination_rect[0].h = fence_rect.h;

	for (int i = 1; i < FENCE_NUM; i++) {
		fence_x[i] = fence_x[i - 1] + fence_rect.w + 20;
		fence_y[i] = fence_y[i - 1] + rand() % 180 - 90;

		if (fence_y[i] > 300 || fence_y[i] < 150) //지정 범위를 벗어나면
		{
			i--; //i 하나 빼줘서 for문 다시 실행
		}
		else //지정범위 벗어나지 않으면 surface 만들어줌
		{
			SDL_Surface* fence_surface = IMG_Load("../Resources/fence2.png");
			fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
			SDL_FreeSurface(fence_surface);

			SDL_QueryTexture(fence_sheet_texture, NULL, NULL, &fence_rect.w, &fence_rect.h);
			fence_destination_rect[i].x = (int)fence_x[i];
			fence_destination_rect[i].y = fence_y[i];
			fence_destination_rect[i].w = fence_rect.w;
			fence_destination_rect[i].h = fence_rect.h;
		}
	}

	//
	time_score = 0;
	startTime = 0;

	// 시간 판정 (clear 문구 추가)
	TTF_Font* font = TTF_OpenFont("../Resources/DungGeunMo.ttf", 80);
	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Surface* time_surface = TTF_RenderText_Blended(font, "CLEAR!", black);

	g_clear_font_rect.x = 0;
	g_clear_font_rect.y = 0;
	g_clear_font_rect.w = time_surface->w;
	g_clear_font_rect.h = time_surface->h;

	g_clear_font = SDL_CreateTextureFromSurface(g_renderer, time_surface);
	SDL_FreeSurface(time_surface);
	TTF_CloseFont(font);

}

void HandleEvents_Infinite()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {

		switch (event.type)
		{
		case SDL_QUIT:
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT) {
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
				Clear_Infinite();
				Sleep(100);
				g_current_game_phase = PHASE_INTRO;
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
		}
	}
}

void Update_Infinite()
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

	//펜스 움직임과 충돌
	for (int i = 0; i < FENCE_NUM; i++) {
		fence_x[i] -= 9;
		fence_destination_rect[i].x = (int)fence_x[i];

		if (chick_x - 40 < fence_x[i] && chick_x + 40 > fence_x[i])
		{
			if (chick_y >= fence_y[i] - 55.0) // 68 72
			{
				Clear_Infinite();
				Init_GameOver();
				Sleep(100);
				g_current_game_phase = PHASE_GAMEOVER;
			}
		}
	}

	// 위아래로 사라지면 게임오버
	if (chick_y > 600 || chick_y < 0)
	{
		Clear_Infinite();
		Init_GameOver();
		Sleep(100);
		g_current_game_phase = PHASE_GAMEOVER;
	}


	// 점수 구현
	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 45);
	SDL_Color black = { 0, 0, 0, 0 };

	Uint32 current_ticks = SDL_GetTicks();

	time_score = (current_ticks - startTime) / 1000;

	sprintf_s(score_buffer, sizeof(score_buffer), "%03d", time_score);
	SDL_Surface* score_surface = TTF_RenderText_Blended(font1, score_buffer, black);

	g_score_rect.x = 0;
	g_score_rect.y = 0;
	g_score_rect.w = score_surface->w;
	g_score_rect.h = score_surface->h;

	g_score_tex = SDL_CreateTextureFromSurface(g_renderer, score_surface);

	// 해제
	SDL_FreeSurface(score_surface);
	TTF_CloseFont(font1);

}

void Render_Infinite()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture, &g_source_rectangle, &g_destination_rectangle);

	for (int i = 0; i < FENCE_NUM; i++)
	{
		SDL_RenderCopy(g_renderer, fence_sheet_texture, &fence_rect, &fence_destination_rect[i]);
	}

	SDL_RenderCopy(g_renderer, chick_sheet_texture,
		&chick_rect[chick_current_fly_index],
		&chick_destination_rect);

	{	//폰트
		SDL_Rect score_des;	//새로 위치 지정
		score_des.x = 700;
		score_des.y = 20;
		score_des.w = g_score_rect.w;
		score_des.h = g_score_rect.h;
		SDL_RenderCopy(g_renderer, g_score_tex, &g_score_rect, &score_des);
	}

	if (time_score >= 999) {
		// clear 폰트
		SDL_Rect g_clear_font_r;
		g_clear_font_r.x = 300;
		g_clear_font_r.y = 200;
		g_clear_font_r.w = g_clear_font_rect.w;
		g_clear_font_r.h = g_clear_font_rect.h;
		SDL_RenderCopy(g_renderer, g_clear_font, &g_clear_font_rect, &g_clear_font_r);
	}

	SDL_RenderPresent(g_renderer); // draw to the screen

}

void Clear_Infinite()
{
	SDL_DestroyTexture(g_texture);
	SDL_DestroyTexture(chick_sheet_texture);
	SDL_DestroyTexture(fence_sheet_texture);
	SDL_DestroyTexture(g_score_tex);
}