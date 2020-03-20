#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_image.h>
#include "../../Contenedores/Lista/AssetList.h"
#include <Windows.h>
#include "../../Lua/Lua.h"
class Graphics
{
public:
	 int SCREEN_WIDTH;
	 int SCREEN_HEIGHT;

	static Graphics* returnPTR();
	static void Release();

	SDL_Texture* LoadTexture(std::string path, AssetList<SDL_Texture*>& vector);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, std::string key, 
								   AssetList<SDL_Texture*>& textVector, AssetList<TTF_Font*>& fontVector, SDL_Color color);
	
	void RenderClear();
	void DrawTexture(SDL_Texture* texture, SDL_Rect* clipp,  SDL_Rect* rect);

	void Render();
	bool Init();
	void setWidth(int width);
	void setHeight(int height);
	SDL_Renderer* getRenderer();
	SDL_Surface* GetSurface();
private:
	SDL_Window* mainWindow;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	static Graphics* ptr;
	HANDLE hConsole;
	static bool initialize;


	Graphics();
	~Graphics();

};


#endif 