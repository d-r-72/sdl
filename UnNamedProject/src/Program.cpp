#include "Program.h"



Program::Program()
{
}

Program::~Program()
{}

void Program::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	r = 255, g = 255, b = 255, a=255;
	window = NULL;
	renderer = NULL;

	if (!CreateWindow(cons::WIDTH, cons::HEIGHT))
	{
		std::cout << "Error Creating Window!\n";
		system("PAUSE");
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Error creating renderer!\n";
		std::cout << SDL_GetError() << std::endl;
		system("PAUSE");
		exit(1);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	int imgFlags = IMG_INIT_PNG;
	if (IMG_Init(imgFlags) != imgFlags)
	{
		std::cout << "Error initializing PNG files!\n";
		std::cout << IMG_GetError() << std::endl;
		system("PAUSE");
		exit(1);
	}
	
	if (!LoadMedia())
	{
		std::cout << "Error Creating Image!\n";
		system("PAUSE");
		exit(1);
	}

	Update();

	Close();
}

void Program::Update()
{
	bool done = false;

	while (!done)
	{		
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		
		back.Render(0, 0);
		
		front.SetAlpha(a);
		front.Render(0, 0);


		SDL_RenderPresent(renderer);
		
		done = Input();
	}
}

bool Program::Input()
{
	bool result = false;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			result = true;
		
		if (e.type = SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_DOWN:
				if (a - 5 < 0)
					a = 0;
				else
					a -= 5;
				break;

			case SDLK_UP:
				if (a + 5 > 255)
					a = 255;
				else
					a += 5;
				break;

			default:
				break;
			}
		}

	}


	return result;
}

bool Program::CreateWindow(int width, int height)
{
	bool result = true;

	window = SDL_CreateWindow("SDL Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
		result = false;

	return result;
}

bool Program::LoadMedia()
{
	bool result = true;

	front.LoadTexture("res/front.png", renderer);
	front.SetBlendMode(SDL_BLENDMODE_BLEND);
	back.LoadTexture("res/back.png", renderer);

	return result;
}

void Program::Close()
{

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = NULL;
	window = NULL;

	SDL_Quit();
}

