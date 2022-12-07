#include "GameFunc.h"
#include "GamePhase.h"
#define FENCE_NUM 50


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

//선인장
static SDL_Texture* fence_sheet_texture;
static SDL_Rect fence_rect[3];
static SDL_Rect fence_destination_rect[FENCE_NUM];

static int fence_x[FENCE_NUM];
static int fence_y[FENCE_NUM];

//모래바람
static SDL_Texture* obstacle_sheet_tex;
static SDL_Rect obstacle_rect;
static SDL_Rect obstacle_des_rect;

static int obstacle_x;
static int obstacle_y;

// title
static SDL_Texture* g_stage2_title;
static SDL_Rect g_stage2_title_rect;
static SDL_Rect g_stage2_title_des_rect;

// Timer
SDL_Texture* timer_texture_s2;
SDL_Rect timer_texture_rect_s2;
SDL_Rect timer_destination_rect_s2;
int time_ms_s2;
Uint32 startTime_s2;


void Init_Stage2()
{
	srand((unsigned int)time(NULL));

	SDL_Surface* bg_surface = IMG_Load("../Resources/stage2_bg.png");
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


	//펜스
	fence_x[0] = 250;
	fence_y[0] = 370;

	SDL_Surface* fence_surface = IMG_Load("../Resources/ob.png");
	fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
	SDL_FreeSurface(fence_surface);

	fence_rect[0] = { 12, 321, 57, 270 };
	fence_rect[1] = { 94, 321, 93, 270 };
	fence_rect[2] = { 207, 321, 132, 270 };

	fence_destination_rect[0].x = (int)fence_x[0];
	fence_destination_rect[0].y = (int)fence_y[0];
	fence_destination_rect[0].w = 57;
	fence_destination_rect[0].h = 270;

	for (int i = 1; i < FENCE_NUM; i++) {
		int j = i % 3;

		fence_x[i] = fence_x[i - 1] + (fence_rect[2].w + rand() % 50 + 50);
		fence_y[i] = fence_y[i - 1] + rand() % 120 - 60;

		if (fence_y[i] > 450 || fence_y[i] < 350) //지정 범위를 벗어나면
		{
			i--; //i 하나 빼줘서 for문 다시 실행
		}
		else //지정범위 벗어나지 않으면 surface 만들어줌
		{
			SDL_Surface* fence_surface = IMG_Load("../Resources/ob.png");
			fence_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, fence_surface);
			SDL_FreeSurface(fence_surface);

			fence_destination_rect[i].x = fence_x[i];
			fence_destination_rect[i].y = fence_y[i];
			if (j == 0) {
				fence_destination_rect[i].w = 57;
				fence_destination_rect[i].h = 270;
			}
			else if (j == 1) {
				fence_destination_rect[i].w = 93;
				fence_destination_rect[i].h = 270;
			}
			else if (j == 2) {
				fence_destination_rect[i].w = 132;
				fence_destination_rect[i].h = 270;
			}
		}
	}

	//상단 장애물

	obstacle_x = 800;
	obstacle_y = 130;

	SDL_Surface* ob_surface = IMG_Load("../Resources/ob.png");
	obstacle_sheet_tex = SDL_CreateTextureFromSurface(g_renderer, ob_surface);
	SDL_FreeSurface(ob_surface);

	obstacle_rect = { 366, 390, 155, 90 };
	obstacle_des_rect.x = (int)obstacle_x;
	obstacle_des_rect.y = (int)obstacle_y;
	obstacle_des_rect.w = 93;
	obstacle_des_rect.h = 54; //(0.6배)


	// 스테이지 타이틀
	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* stage2_title_surface = TTF_RenderText_Blended(font1, "STAGE 2", black);
	g_stage2_title = SDL_CreateTextureFromSurface(g_renderer, stage2_title_surface);


	g_stage2_title_rect.x = 0;
	g_stage2_title_rect.y = 0;
	g_stage2_title_rect.w = stage2_title_surface->w;
	g_stage2_title_rect.h = stage2_title_surface->h;

	g_stage2_title_des_rect.x = 350;
	g_stage2_title_des_rect.y = 20;
	g_stage2_title_des_rect.w = g_stage2_title_rect.w;
	g_stage2_title_des_rect.h = g_stage2_title_rect.h;


	time_ms_s2 = 0;
	timer_texture_s2 = 0;
	startTime_s2 = 0;

	//해제
	SDL_FreeSurface(stage2_title_surface);
	TTF_CloseFont(font1);
}

void HandleEvents_Stage2()
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
				Clear_Stage2();
				Init_Stage2Clear();
				Sleep(100);
				g_current_game_phase = PHASE_STAGE2CLEAR;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
		}
	}
}

// 시간을 texture로 변환시키는 함수
//void UpdateTimeTexture_s2(int ms)
//{
//	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
//	SDL_Color skyblue = { 53, 183, 232, 0 };
//
//	if (timer_texture_s2 != 0)
//	{
//		SDL_DestroyTexture(timer_texture_s2);
//		timer_texture_s2 = 0;
//	}
//	SDL_Surface* timer_surface = TTF_RenderText_Blended(font1, std::to_string(ms / 1000).c_str(), skyblue);
//
//	timer_texture_rect_s2.x = 800;
//	timer_texture_rect_s2.y = 20;
//	timer_texture_rect_s2.w = timer_surface->w;
//	timer_texture_rect_s2.h = timer_surface->h;
//
//	timer_texture_s2 = SDL_CreateTextureFromSurface(g_renderer, timer_surface);
//
//	SDL_FreeSurface(timer_surface);
//}

void Update_Stage2()
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
		time_ms_s2 = current_ticks - startTime_s2;
		//UpdateTimeTexture_s2(time_ms_s2);
	}

	timer_destination_rect_s2.x = 750;
	timer_destination_rect_s2.y = 20;
	timer_destination_rect_s2.w = timer_texture_rect_s2.w;
	timer_destination_rect_s2.h = timer_texture_rect_s2.h;

	//펜스 움직임과 충돌
	for (int i = 0; i < FENCE_NUM; i++) {
		fence_x[i] -= 5;
		fence_destination_rect[i].x = (int)fence_x[i];

		if (chick_x - 40 < fence_x[i] && chick_x + 40 > fence_x[i])
		{
			if (chick_y >= fence_y[i] - 55.0) // 68 72
			{
				Clear_Stage2();
				Init_GameOver();
				Sleep(100);
				g_current_game_phase = PHASE_GAMEOVER;
			}
		}
	}

	//상단 장애물 (모래바람) 움직임
	if (((int)time_ms_s2 / 100) % 50 == 0) {
		obstacle_x = 800;
	}
	else {
		obstacle_x -= 10;
		obstacle_des_rect.x = (int)obstacle_x;
	}

	//모래바람 충돌
	if (chick_x + 60 > obstacle_x && chick_x - 50 < obstacle_x)
	{
		if (chick_y - 40 < obstacle_y && chick_y + 50 > obstacle_y) // 68 72
		{
			Clear_Stage2();
			Init_GameOver();
			Sleep(100);
			g_current_game_phase = PHASE_GAMEOVER;
		}
	}

	// 위아래로 사라지면 게임오버
	if (chick_y > 600 || chick_y < 0)
	{
		Clear_Stage2();
		Init_GameOver();
		Sleep(100);
		g_current_game_phase = PHASE_GAMEOVER;
	}

	//clear 판정
	if ((int)time_ms_s2 / 1000 >= 30)
	{
		Clear_Stage2();
		Init_Stage2Clear();
		Sleep(100);
		g_current_game_phase = PHASE_STAGE2CLEAR;
	}

}

void Render_Stage2()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	SDL_RenderCopy(g_renderer, g_texture, &g_source_rectangle, &g_destination_rectangle);

	for (int i = 0; i < FENCE_NUM; i++)
	{
		int j = i % 3;
		SDL_RenderCopy(g_renderer, fence_sheet_texture, &fence_rect[j], &fence_destination_rect[i]);
	}


	SDL_RenderCopy(g_renderer, obstacle_sheet_tex, &obstacle_rect, &obstacle_des_rect);


	SDL_RenderCopy(g_renderer, chick_sheet_texture,
		&chick_rect[chick_current_fly_index],
		&chick_destination_rect);

	SDL_RenderCopy(g_renderer, g_stage2_title, &g_stage2_title_rect, &g_stage2_title_des_rect);

	SDL_RenderCopy(g_renderer, timer_texture_s2, 0, &timer_destination_rect_s2);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Clear_Stage2()
{
	SDL_DestroyTexture(g_texture);
	SDL_DestroyTexture(chick_sheet_texture);
	SDL_DestroyTexture(fence_sheet_texture);
	SDL_DestroyTexture(obstacle_sheet_tex);
	SDL_DestroyTexture(g_stage2_title);
	SDL_DestroyTexture(timer_texture_s2);
}