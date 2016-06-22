#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <string>

#include "constants.h"
#include "Texture.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

class Program
{
public:
	Program();
	~Program();

	void Init();

private:
	bool CreateWindow(int width, int height);
	bool LoadMedia();
	void Close();
	void Update();
	bool Input();

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Rect mSpriteClips[4];
	Texture mSpriteSheet;
	

	SDL_Event e;
};

#endif //PROGRAM_H

