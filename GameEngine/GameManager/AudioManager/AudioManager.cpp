#include "AudioManager.h"
AudioManager* AudioManager::ptr = nullptr;

/*Constructor por defecto de la clase Audio Manager*/
AudioManager::AudioManager()
{
	assetMNGR = AssetManager::getPTR();	//Se crea un apuntador de esta clase

	//Si el audio falla, imprime un error
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("Mixer Initialization Error: %s\n", Mix_GetError());
	}
}

/*Destructor por defecto de la clase AudioManager*/
AudioManager::~AudioManager()
{
	assetMNGR = nullptr;
	Mix_Quit();	//Se cierra la librearía de Mixer
}

/*Función que creará el apuntador de esta clase*/
AudioManager* AudioManager::getPTR()
{
	//Si apuntador es nulo, crea una nueva clase AudioManager
	if(ptr == nullptr)
	{
		ptr = new AudioManager();
	}

	return ptr;	//Regresa el apuntador
}

/*Release eliminará el apuntador y lo hará nulo*/
void AudioManager::Release()
{
	delete ptr;
	ptr = nullptr;
}

/*Play music se encargará de reproducir la música por las veces que se indique
	@param[fileName] nombre del audio
	@param[loops] número de veces que se quiere repetir (1 o infinitas)*/
void AudioManager::PlayMusic(string fileName, int loops)
{
	String s = fileName;
	Mix_PlayMusic(assetMNGR->GetMusic(s.GetWString()), loops);
}

/*Esta función se encargará de pausar la música*/
void AudioManager::PauseMusic()
{
	if(Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

/*Función que se encargará de continuar con la música en el momento que se quedó pausada*/
void AudioManager::ResumeMusic()
{
	if(Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

/*PlaySFX es una función que reproducirá una vez o muchas veces un sfx
	@param[fileName] nombre del sfx
	@param[loops] numero de veces que se repetirá el sfx
	@param[channel] "canal" donde se quiere que suene el sfx*/
void AudioManager::PlaySFX(string fileName, int loops, int channel)
{
	String s;
	Mix_PlayChannel(channel, assetMNGR->GetSFX(s.convert(fileName)), loops);
}
