#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "../../Graphics/AnimatedTextures/AnimatedTexture.h"
#include "../../GameManager/InputManager/InputManager.h"
#include "../../myVector.h"

class StartScreen : public GameObject
{
	//Top Bar
	GameObject* TopText;
	Texture* titleText;
	Texture* backGround;
	
	Vector2 mousePos;
	InputManager* input;
	GameObject* CenterPoint;

	Texture* startText;
	Texture* hSText;
	Texture* QuitText;
	myVector<Texture*> screenVec;
	myVector<string>* string;
public:
	StartScreen();
	~StartScreen();
	void Update();
	void Render();
	void MainMenu();
	void GameScreen();

	bool startGame;
};


#endif //!STARTSCREEN_H

