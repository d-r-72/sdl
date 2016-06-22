#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTexture(std::string path, SDL_Renderer *renderer);

	void Render(int x, int y, SDL_Rect * clip = NULL);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	void Free();
private:
	
	SDL_Texture * mTexture;
	SDL_Renderer *mRenderer;

	int mWidth;
	int mHeight;
};

#endif //TEXTURE_H

