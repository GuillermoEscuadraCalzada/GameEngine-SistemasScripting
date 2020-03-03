#include "ScreenManager.h"

ScreenManager* ScreenManager::instance = nullptr;

/*Constructor por defecto de la clase ScreenManager*/
ScreenManager::ScreenManager()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	input = InputManager::getPtr();	  //Apuntador de la clase Input
	gameScreen = new GameScreen();	  //Se crea un objeto de la clase GameScree
	currentScreen = play;		     //El enum comienza con la variable start

}


/*Destructor de la clase Screen Manager que elimina cada uno de los apuntadores que existan*/
ScreenManager::~ScreenManager()
{
	
	input = nullptr;	//Input se hace nulo
	delete gameScreen;	//Elimina el objeto de GameScreen
	gameScreen = nullptr;	//Lo hace nulo

}

/*Al ser una clase Singleton y se debe de buscar el apuntador, si es nulo, se debe de crear
	@return apuntador de esta clase*/
ScreenManager* ScreenManager::getPTR()
{
	//Si es nulo, crea un nuevo objeto de esta clase
	if(instance == nullptr)	
		instance = new ScreenManager();
	return instance;	//Regrea el apuntador
}

/*Elimina el apuntador y lo hace nulo*/
void ScreenManager::Release()
{
	delete instance;
	instance = nullptr;
}

void ScreenManager::Init(void * buff)
{
	try
	{
		switch(currentScreen)
		{
		case play: {
			gameScreen->Init(buff);
		}
		default:
			break;
		}
	} catch(exception & e)
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Exception caught: " << e.what() << endl;
	}
}

/*Actualiza los estados de juego que se encuentran en el enum*/
void ScreenManager::Update()
{

	/*Se hace un switch entre las pantallas actuales del juego*/
	switch(currentScreen)
	{
	case play:
		//gameScreen->Update();	//Se llama la función update de GameScreen

	default:
		break;
	}

}

/*Se renderizan todas las ventanas existentes en el juego*/
void ScreenManager::Render()
{
	/*Se hace otro switch entre las ventanas actuales del juego y se mandan a llamar los render*/
	switch(currentScreen)
	{

	case play:
			gameScreen->Render();	//Se renderiza esta sección
		break;
	default:
		break;
	}
}


