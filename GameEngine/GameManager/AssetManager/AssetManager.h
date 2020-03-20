#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "../../Graphics/Graphics/Graphics.h"
#include "../../Contenedores/Lista/AssetList.h"

#include <SDL_mixer.h>
#include <iostream>
using std::string; using std::cout; using std::exception; using std::endl;

class AssetManager
{
public:
	Console* console;
	static AssetManager* getPTR();
	static void Close();

	SDL_Texture* GetTexture(wstring fileName);
	SDL_Texture* GetText(wstring text, wstring fileName, int size, SDL_Color color);
	Mix_Music* GetMusic(wstring fileName);
	Mix_Chunk* GetSFX(wstring fileName);

	wstring texture;
	wstring text;
	AssetList<SDL_Texture*> GetTextureVector()
	{
		return textures;
	}

private:
	static AssetManager* ptr;
	//Vector<string> textures;
	AssetList<SDL_Texture*> textures;
	AssetList<SDL_Texture*> texts;
	AssetList<TTF_Font*> font;
	AssetList<Mix_Music*> music;
	AssetList<Mix_Chunk*> sfx;

	TTF_Font* GetFont(wstring fileName, int size);
	AssetManager();
	~AssetManager();
	

};

#endif //! ASSETMANAGER_H
