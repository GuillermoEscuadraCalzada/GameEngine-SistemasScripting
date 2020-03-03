#include "GameScreen.h"

GameScreen::GameScreen() {
	timer = Timer::getPTR();	//Busca el apuntador del tiempo
	input = InputManager::getPtr();	//Busca el apuntador del input
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	textureList = new myVector<Texture*>();
}

GameScreen::~GameScreen()
{
	timer = nullptr;
	input = nullptr;
	delete backGround;
	backGround = nullptr;
}

void GameScreen::setBackGround(Texture* backGround) {
	this->backGround = backGround;
}

void GameScreen::setCharacter(Texture* character) {
	this->character = character;

}

/*Regresa el apuntador al fondo de la pantalla*/
Texture* GameScreen::GetBackGround() {
	try {
		if(backGround) //Si el fondo existe, regr�salo
			return backGround;
		else //No existe
			throw(backGround); //Lanza un error
	} catch(Texture * text) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Este objeto es nulo.\n";
	}

}

/*Se obtiene un nuevo jugador*/
Texture* GameScreen::GetCharacter() {
	try {
		if(character)
			return character;
		else
			throw(character);
	} catch(Texture * text) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Este objeto es nulo.\n";
	}
}

/*Actualizaci�n de la pantalla gameScreen, donde suceden todas las acciones del jugador, disminuci�n del tiempo, etc.*/
void GameScreen::Update()
{
	try
	{
		input->Update();
		input->UpdatePrevInput();

	} catch(std::exception & e){
		SetConsoleTextAttribute(hConsole, 4);
		cout << "Exception caught: " << e.what() << std::endl;
	}
}
	
/*Funci�n que renderiza cada elemento importante de esta ventana, los nodos del grafo, el fondo, el score y */
void GameScreen::Render()
{
	try
	{
		if(backGround)	
			backGround->Render(); ///Renderiza el fondo
		if(character)
			character->Render(); //Renderiza el personaje
	} catch(exception & e)
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Esta funci�n establece todos los elementos que se encontrar�n dentro de esta pantalla de juego
 *@param[void * buff] el buffer que permitir� la entrada de todos los elementos*/
void GameScreen::Init(void * buff) {
	try {
		setBackGround(new (buff) Texture("Fondo_800x800.png", 0, 0, 800, 800)); //Selecciona una textura para el fondo
		GetBackGround()->setPosition(Vector2(400, 400)); //Establece su posici�n

		setCharacter(new /*(buff)*/ Texture("HollowKnight.png", 0, 0, 179, 185)); //Establece una nueva imagen para el personaje
		GetCharacter()->setPosition(Vector2(400, 400)); //Establece su posici�n
	} catch(exception & e) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}
