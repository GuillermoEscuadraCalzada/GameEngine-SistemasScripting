#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "../../Graphics/Graphics/Graphics.h"
#include "../AudioManager/AudioManager.h"
#include "../../GameObject/GameObject.h"
#include "../../MenuInicio/StartScreen/ScreenManager.h"
#include "../../ConfigIni/ConfigIni.h"
#include "../../ConfigIni/INIReader.h"
#include "../StackAllocator/StackAllocator.h"
#include <ctime>
#include <Windows.h>
class GameManager
{
public:
	static GameManager* GetPtr();
	void StartUp();
	static void Close();
	StackAllocator* stackAllocator;

#pragma region Updates
	void EarlyUpdate();
	void Update();
	void MainUpdate();
	void LateUpdate();
#pragma endregion


	void Render();

	int GetWidth();
	int GetHeight();
	Texture* backGround; 

private: 
	ConfigIni* initialize = new ConfigIni();

	HANDLE hConsole;
	void* buff;
	Timer* timer;

	bool quit;
	static GameManager* ptr;
	Graphics* graphics;
	AssetManager* assetM;
	AudioManager* audiMGR;
	InputManager* inputMGR;
	ScreenManager* screenMGR;

	myVector<Texture*> textureVect;
	myVector<AnimatedTexture*> animVect;

	SDL_Event eventHandler;

	const int FrameRate = 60.0f;
	GameManager();
	~GameManager();
	AnimatedTexture* anText;
protected:
	int firstMemory;
	int secondMemory;
	int thirdMemory;

};

#endif // !GAMEMANAGER_H
