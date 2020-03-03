#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL.H>
#include <string.h>
#include "../../GameObject/Vector2.h"
class InputManager
{
public:
	enum MOUSE_BUTTONS
	{
		left = 0, right, middle, back, forward
	};

	static InputManager* getPtr();
	static void Release();

	bool keyDown(SDL_Scancode scanCode);
	bool keyReleased(SDL_Scancode scanCode);
	bool keyPressed(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTONS button);
	bool MouseButtonPressed(MOUSE_BUTTONS button);
	bool MouseButtonReleased(MOUSE_BUTTONS button);

	Vector2 MousePosition();

	void Update();
	void UpdatePrevInput();

private:
	static InputManager* ptr;
	int keyLength;
	int MouseXPos;
	int MouseYPos;

	Uint32 prevMouseState;
	Uint32 currentMouseState;

	Uint8* prevKeyState;
	const Uint8* keyBoardStates;
	InputManager();
	~InputManager();
};



#endif // !INPUTMANAGER_H
