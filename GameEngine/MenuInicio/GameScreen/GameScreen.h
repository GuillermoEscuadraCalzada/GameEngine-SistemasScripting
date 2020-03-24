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
#include <chrono>
#include <thread>
#include <map>
class GameScreen 
{
public:
	void Update();
	void Render();
	void Init();
	GameScreen();
	~GameScreen();
	HANDLE hConsole;
	myVector<Texture*>* textureList;
	AssetList<Primitives*>* primitivesList;
	map<wstring, Primitives*> primitivesMap;
	void setBackGround(Texture* backGround);
	void setCharacter(Texture* backGround);
	void CreateObjects();
	Texture* GetBackGround();
	Texture* GetCharacter();
	Console* console;
	//void setStackAllocator(StackAllocator* stackAlloc);
private:
	float score = 0;
	bool change = true;
	int counter = 0;
	int MoveObject(lua_State* lua);
	StackAllocator* stackAllocator;
	InputManager* input;
	int milisegundos = 0;
	int segundos = 0;
	int minutos = 0;
	float totalTime = 0;
	Timer* timer;
	Texture* backGround = nullptr;
	Texture* character;
	String s;

};
#endif // ! GAMESCREEN_H
