#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include "../AssetManager/AssetManager.h"

using std::string;

class AudioManager
{
private:
	static AudioManager* ptr;
	AssetManager* assetMNGR;
	AudioManager();
	~AudioManager();
public:
	static AudioManager* getPTR();
	static void Release();

#pragma region Musica
	void PlayMusic(string fileName, int loops = -1);
	void PauseMusic();
	void ResumeMusic();
#pragma endregion Funciones de la música

#pragma region SFX
	void PlaySFX(string fileName, int loops = -1, int channel = 0);
#pragma endregion Funciones del SFX


};

#endif // !AUDIOMANAGER_H

