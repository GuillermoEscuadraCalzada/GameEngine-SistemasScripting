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
	std::string textText;
	std::string fontPath;
	Texture();
	Texture(std::string path);
	Texture(std::string path, int x, int y, int w, int h, int id);
	Texture(std::string path, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	
	~Texture();
	int ID;
	SDL_Rect* rect;
	std::string GetPath();


	int size;
	int index;

	virtual void Render();
};


inline std::string Texture::GetPath()
{
	return textText;
}
#endif // !TEXTURE_H
