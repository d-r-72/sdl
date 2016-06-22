#include "Texture.h"



Texture::Texture()
{
	mTexture = NULL;
	mRenderer = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	Free();
}

bool Texture::LoadTexture(std::string path, SDL_Renderer *renderer)
{
	mRenderer = renderer;

	SDL_Texture * newTexture = NULL;

	SDL_Surface * newSurface = IMG_Load(path.c_str());

	if (newSurface == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
		system("PAUSE");
		exit(1);
	}
	else
	{
		SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(mRenderer, newSurface);
		if (newTexture == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
			system("PAUSE");
			exit(1);
		}
		else
		{
			mWidth = newSurface->w;
			mHeight = newSurface->h;
		}
	}

	SDL_FreeSurface(newSurface);

	mTexture = newTexture;
	return mTexture != NULL;
}

void Texture::Render(int x, int y)
{
	SDL_Rect rect = { x, y, mWidth, mHeight };
	SDL_RenderCopy(mRenderer, mTexture, NULL, &rect);
}

void Texture::Free()
{	
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		SDL_DestroyRenderer(mRenderer);
		mWidth = 0;
		mHeight = 0;
	}
}
