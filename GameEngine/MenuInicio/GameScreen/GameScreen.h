#ifndef  GAMESCREEN_H
#define GAMESCREEN_H
#include "../../MenuInicio/StartScreen/StartScreen.h"
#include "../../GameManager/Timer/Timer.h"
#include "../../GameObject/GameObject.h"
#include <Windows.h>
#include "../../Graphs/Graph.h"
//#include "../../GameManager/GameManager/GameManager.h"

class GameScreen : public GameObject
{
public:
	
	void Update();
	void Render();
	void Init(void *);
	GameScreen();
	~GameScreen();
	myVector<Texture*>* textureList;

	void setBackGround(Texture* backGround);
	void setCharacter(Texture* backGround);

	Texture* GetBackGround();
	Texture* GetCharacter();

private:
	float score = 0;
	bool change = true;
	int counter = 0;
	
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
