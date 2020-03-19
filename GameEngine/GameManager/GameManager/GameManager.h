#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "../AudioManager/AudioManager.h"
#include "../../String/String.h"
#include "../../Lua.h"
#include "../../GameObject/Primitives/Circle.h"
#include "../../GameObject/Primitives/Square.h"
#include "../../MenuInicio/StartScreen/ScreenManager.h"
#include "../../Console/Console.h"
#include <ctime>
#include <Windows.h>
class GameManager
{
public:
	static GameManager* GetPtr();
	void StartUp();
	static void Close();
	StackAllocator* stackAllocator;
	Square* square;
#pragma region Updates
	void MainUpdate();
#pragma endregion
	


private: 
	const int FrameRate = 60.0f;

	static GameManager* ptr;
	HANDLE hConsole;
	Timer* timer;
	Lua* lua;

	void EarlyUpdate();
	void Update();
	void LateUpdate();



	GameManager();
	~GameManager();
	Console* console;
protected:
	void Render();

	Graphics* graphics;
	AssetManager* assetM;
	AudioManager* audioMGR;
	InputManager* inputMGR;
	ScreenManager* screenMGR;
	SDL_Event eventHandler;
	bool quit;

	void GetSingletons();
};

#endif // !GAMEMANAGER_H
