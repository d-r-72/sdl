#include "Program.h"



Program::Program()
{
}

Program::~Program()
{
}

SDL_Surface* Program::LoadSurface(std::string path)
{
	SDL_Surface *optimized = NULL;
	SDL_Surface *result = IMG_Load(path.c_str());
	if (result == NULL)
	{
		std::cout << "Error loading " << path << std::endl;
		system("PAUSE");
		exit(1);
	}
	else
	{
		//optimized = SDL_ConvertSurface(result, screenSurface->format, NULL);
		if (optimized == NULL)
		{
			std::cout << "Error optimizing " << path << std::endl;
			system("PAUSE");
			exit(1);
		}

		SDL_FreeSurface(result);
	}

	return optimized;
}

SDL_Texture * Program::LoadTexture(std::string path)
{
	SDL_Texture *result = NULL;

	SDL_Surface *newSurface = IMG_Load(path.c_str());
	if (newSurface == NULL)
	{
		std::cout << "Error loading " << path << "\n" << IMG_GetError() << std::endl;
		system("PAUSE");
		exit(1);
	}

	result = SDL_CreateTextureFromSurface(renderer, newSurface);
	if (result == NULL)
	{
		std::cout << "Error creating texture from surface " << SDL_GetError() << std::endl;
		system("PAUSE");
		exit(1);
	}

	SDL_FreeSurface(newSurface);

	return result;
}

void Program::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	window = NULL;
	texture = NULL;
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
		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);


		SDL_Rect Fillrect = {cons::WIDTH / 4, cons::HEIGHT / 4, cons::WIDTH / 2, cons::HEIGHT / 2 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &Fillrect);

		//Render texture
		//SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_Rect rect = { cons::WIDTH / 6, cons::HEIGHT / 6, cons::WIDTH * 2 / 3, cons::HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawLine(renderer, 0, cons::HEIGHT / 2, cons::WIDTH, cons::HEIGHT / 2);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		for (int i = 0; i < cons::HEIGHT; i += 4)
		{
			SDL_RenderDrawPoint(renderer, cons::WIDTH / 2, i);
		}

		//Update
		SDL_RenderPresent(renderer);

		done = Input();
	}
}

bool Program::Input()
{
	bool result = false;
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT)
			result = true;

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

	//texture = LoadTexture("res/image.png");

	return result;
}

void Program::Close()
{
	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	renderer = NULL;
	window = NULL;

	SDL_Quit();
}

