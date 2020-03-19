#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <Windows.h>
//#include "../../GameManager/StackAllocator/StackAllocator.h"
#include "../GameScreen/GameScreen.h"
class ScreenManager
{
	enum SCREENS {start, play};
	InputManager* input;
	SCREENS currentScreen;
	static ScreenManager* ptr;
	//StackAllocator* stackAllocator;

public:

	GameScreen* gameScreen;
	static ScreenManager* getPTR();
	static void Release();
	void Init();
	void Update();
	void Render();
	//void setStackAlloc(StackAllocator* stack);
private:

	HANDLE hConsole;
	ScreenManager();
	~ScreenManager();
};
#endif //!SCREENMANAGER_H