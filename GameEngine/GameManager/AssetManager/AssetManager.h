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
	
	static AssetManager* getPTR();
	static void Close();

	SDL_Texture* GetTexture(string fileName);
	SDL_Texture* GetText(string text, string fileName, int size, SDL_Color color);
	Mix_Music* GetMusic(string fileName);
	Mix_Chunk* GetSFX(string fileName);

	string texture;
	string text;
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

	TTF_Font* GetFont(string fileName, int size);
	AssetManager();
	~AssetManager();
	

};

#endif //! ASSETMANAGER_H
