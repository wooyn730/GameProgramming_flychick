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

Mix_Chunk* chick_sound;

//펜스
static SDL_Texture* fence_sheet_texture;
static SDL_Rect fence_rect;
static SDL_Rect fence_destination_rect[FENCE_NUM];

static int fence_x[FENCE_NUM];
static int fence_y[FENCE_NUM];

// title
static SDL_Texture* g_stage1_title;
static SDL_Rect g_stage1_title_rect;
static SDL_Rect g_stage1_title_des_rect;

// Timer
SDL_Texture* timer_texture;
SDL_Rect timer_texture_rect;
SDL_Rect timer_destination_rect;
int time_ms;
Uint32 startTime_s1;


void Init_Stage1()
{
	srand((unsigned int)time(NULL));

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
	chick_destination_rect.w = 68;
	chick_destination_rect.h = 72;

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
		fence_x[i] = 250 + (i * (fence_rect.w + 12));
		fence_y[i] = fence_y[i-1] + rand() % 70 - 35; //펜스i의 y값은 전 펜스 +-30된 값

		if (fence_y[i] > 450 || fence_y[i] < 250) //지정 범위를 벗어나면
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

		chick_sound = Mix_LoadWAV("../Resources/ari_moving.wav");
		if (chick_sound == NULL) { 
			std::cout << "Mix_LoadWAV(\Chick_sound.wav\"): " << Mix_GetError() << std::endl;
			exit(2);
		}

		Mix_VolumeChunk(chick_sound, 30);
	}

	
	// 스테이지 타이틀
	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* stage1_title_surface = TTF_RenderText_Blended(font1, "STAGE 1", black);
	g_stage1_title = SDL_CreateTextureFromSurface(g_renderer, stage1_title_surface);


	g_stage1_title_rect.x = 0;
	g_stage1_title_rect.y = 0;
	g_stage1_title_rect.w = stage1_title_surface->w;
	g_stage1_title_rect.h = stage1_title_surface->h;

	g_stage1_title_des_rect.x = 350;
	g_stage1_title_des_rect.y = 20;
	g_stage1_title_des_rect.w = g_stage1_title_rect.w;
	g_stage1_title_des_rect.h = g_stage1_title_rect.h;

	
	time_ms = 0;
	timer_texture = 0;
	startTime_s1 = 0;

	//해제
	SDL_FreeSurface(stage1_title_surface);
	TTF_CloseFont(font1);
}

void HandleEvents_Stage1()
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
				Clear_Stage1();
				Init_Stage1Clear();
				Sleep(100);
				g_current_game_phase = PHASE_STAGE1CLEAR;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_flag_running = false;
			}
		}
	}
}

// 시간을 texture로 변환시키는 함수
//void UpdateTimeTexture(int ms)
//{
//	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 35);
//	SDL_Color skyblue = { 53, 183, 232, 0 };
//
//	if (timer_texture != 0)
//	{
//		SDL_DestroyTexture(timer_texture);
//		timer_texture = 0;
//	}
//	SDL_Surface* timer_surface = TTF_RenderText_Blended(font1, std::to_string(ms/1000).c_str(), skyblue);
//
//	timer_texture_rect.x = 700;
//	timer_texture_rect.y = 20;
//	timer_texture_rect.w = timer_surface->w;
//	timer_texture_rect.h = timer_surface->h;
//
//	timer_texture = SDL_CreateTextureFromSurface(g_renderer, timer_surface);
//
//	SDL_FreeSurface(timer_surface);
//}

void Update_Stage1()
{
	//아리 날갯짓
	if (chick_go_up == true)
	{
		chick_y -= 10;
		chick_destination_rect.y = (int)chick_y;

		chick_current_fly_index++;

		if (chick_current_fly_index >= chick_fly_sprite_num-1)
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
		time_ms = current_ticks - startTime_s1;
		//UpdateTimeTexture(time_ms);
	}

	timer_destination_rect.x = 750;
	timer_destination_rect.y = 20;
	timer_destination_rect.w = timer_texture_rect.w;
	timer_destination_rect.h = timer_texture_rect.h;


	//펜스 움직임과 충돌
	for (int i = 0; i < FENCE_NUM; i++) {
		fence_x[i] -= 5;
		fence_destination_rect[i].x = (int)fence_x[i];

		if (chick_x - 40 < fence_x[i] && chick_x + 40 > fence_x[i])
		{
			if (chick_y >= fence_y[i] - 55.0) // 68 72
			{
				Clear_Stage1();
				Init_GameOver();
				Sleep(100);
				g_current_game_phase = PHASE_GAMEOVER;
			}
		}
	}

	// 위아래로 사라지면 게임오버
	if (chick_y > 600 || chick_y < 0)
	{
		Clear_Stage1();
		Init_GameOver();
		Sleep(100);
		g_current_game_phase = PHASE_GAMEOVER;
	}

	//clear 판정
	if ((int)time_ms / 1000 >= 25)
	{
		Clear_Stage1();
		Init_Stage1Clear();
		Sleep(100);
		g_current_game_phase = PHASE_STAGE1CLEAR;
	}
	
}

void Render_Stage1()
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

	SDL_RenderCopy(g_renderer, g_stage1_title, &g_stage1_title_rect, &g_stage1_title_des_rect);

	SDL_RenderCopy(g_renderer, timer_texture, 0, &timer_destination_rect);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Clear_Stage1()
{
	SDL_DestroyTexture(g_texture);
	SDL_DestroyTexture(chick_sheet_texture);
	SDL_DestroyTexture(fence_sheet_texture);
	SDL_DestroyTexture(g_stage1_title);
	SDL_DestroyTexture(timer_texture);
}