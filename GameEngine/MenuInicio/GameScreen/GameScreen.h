#ifndef  GAMESCREEN_H
#define GAMESCREEN_H
#include "../../GameManager/StackAllocator/StackAllocator.h"
#include "../../Graphics/AnimatedTextures/AnimatedTexture.h"
#include "../../GameManager/InputManager/InputManager.h"
#include "../../GameManager/Timer/Timer.h"
#include "../../GameObject/GameObject.h"
#include "../../MenuInicio/Screens.h"
#include "../../myVector.h"
#include <Windows.h>

class GameScreen 
{
public:
	void Update();
	void Render();
	void Init();
	GameScreen();
	~GameScreen();

	myVector<Texture*>* textureList;
	AssetList<Primitives*>* primitivesList;

	void setBackGround(Texture* backGround);
	void setCharacter(Texture* backGround);

	Texture* GetBackGround();
	Texture* GetCharacter();

	//void setStackAllocator(StackAllocator* stackAlloc);
private:
	float score = 0;
	bool change = true;
	int counter = 0;
	int MoveObject(lua_State* lua);
	//StackAllocator* stackAllocator;
	InputManager* input;
	int milisegundos = 0;
	int segundos = 0;
	int minutos = 0;
	float totalTime = 0;
	Timer* timer;
	Texture* backGround;
	HANDLE hConsole;
	Texture* character;
	

};
#endif // ! GAMESCREEN_H
