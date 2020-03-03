#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <Windows.h>
#include "../GameScreen/GameScreen.h"
class ScreenManager
{
	enum SCREENS {start, play};
	InputManager* input;
	SCREENS currentScreen;
	static ScreenManager* instance;

public:
	GameScreen* gameScreen;
	static ScreenManager* getPTR();
	static void Release();
	void Init(void *);
	void Update();
	void Render();

private:

	HANDLE hConsole;
	ScreenManager();
	~ScreenManager();
};
#endif //!SCREENMANAGER_H