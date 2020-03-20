
#ifndef TEXTURE_H
#define TEXTURE_H
#include "../../GameObject/GameObject.h"
#include "../../Graphics/Graphics/Graphics.h"
#include "../../GameManager/AssetManager/AssetManager.h"
class Texture : public GameObject
{
protected:
	bool clipped;
	SDL_Texture* texture;
	SDL_Texture* text;
	Graphics* graphics;
	int width, height;
	SDL_Rect clippedRect;

public:
	SDL_Color color;
	std::wstring textText;
	std::wstring fontPath;
	Texture();
	Texture(std::wstring path);
	Texture(std::wstring path, int x, int y, int w, int h, int id);
	Texture(std::wstring path, int x, int y, int w, int h);
	Texture(std::wstring text, std::wstring fontPath, int size, SDL_Color color);
	~Texture();
	int ID;
	SDL_Rect* rect;
	std::wstring GetPath();


	int size;
	int index;

	virtual void Render();
};


inline std::wstring Texture::GetPath()
{
	return textText;
}
#endif // !TEXTURE_H
