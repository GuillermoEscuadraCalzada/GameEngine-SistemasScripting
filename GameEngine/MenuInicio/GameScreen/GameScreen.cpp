#include "GameScreen.h"
bool createObj = false;
GameScreen::GameScreen() {
	timer = Timer::getPTR();	//Busca el apuntador del tiempo
	input = InputManager::getPtr();	//Busca el apuntador del input
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	textureList = new myVector<Texture*>();
	primitivesList = new AssetList<Primitives*>();
	stackAllocator = StackAllocator::getPTR();
}

GameScreen::~GameScreen()
{
	timer = nullptr;
	input = nullptr;
	if (backGround) {
		delete backGround;
		backGround = nullptr;
	}
	if (character) {
		delete character;
		character = nullptr;
	}
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
		if(backGround) //Si el fondo existe, regrésalo
			return backGround;
		else //No existe
			throw(backGround); //Lanza un error
	} catch(Texture * text) {
		SetConsoleTextAttribute(hConsole, 4);
		String s = "Este objeto es nulo.";
		s.PrintWString();
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
		String s = "Este objeto es nulo.";
		s.PrintWString();
	}
}


/*Actualización de la pantalla gameScreen, donde suceden todas las acciones del jugador, disminución del tiempo, etc.*/
void GameScreen::Update()
{
	try
	{
		//input->Update();
		if (createObj == false) {
			s = "Presiona el botón 1 para crear un cuadrado.\nPresiona el botón 2 para crear un círculo.";
			s.PrintWString();
			createObj = true;
		}
		//std::this_thread::sleep_for(std::chrono::seconds(5));
		if (input->keyPressed(SDL_SCANCODE_1)) {
			void* buff = stackAllocator->alloc(sizeof(Square*));
			Square* sq = new /*(buff)*/ Square();
			sq->SetUpValues();
			//Square* sq = new Square();
			//sq->lua_CreateObject("D:/Programación/GameEngine/GameEngine/Lua/Prueba2.lua");

			wstring name = L"Escribe el nombre de tu objeto\n";
			wcout << name;
			wcin >> name;
			primitivesMap.insert(pair<wstring, Square*>(name, sq));

		    primitivesList->push_back(name, sq);
			//Circle* circle = new  Circle(10, 400, 400, 200, 100, 50);
			//primitivesList->push_back(L"Circle", circle);
			primitivesList->print();
			createObj = false;
		}
		else if (input->keyPressed(SDL_SCANCODE_2)) {
			void* buff = stackAllocator->alloc(sizeof(Circle*));
			Circle* circle = new /*(buff)*/ Circle();
			circle->SetUpValues();
			wstring name = L"Escribe el nombre de tu objeto\n";
			wcout << name;
			wcin >> name;
			primitivesList->push_back(name, circle);
			primitivesList->print();
			createObj = false;
		}
		if (primitivesMap.size() > 0) {

		}
		if (primitivesList->getSize() > 0) {
			AssetNode<Primitives*>* it = primitivesList->first;
			while (it != primitivesList->last->next) {
				it->val->Update();
				it = it->next;
			}
		}
		input->UpdatePrevInput();

	} catch(std::exception & e){
		SetConsoleTextAttribute(hConsole, 4);
		wcout << "Exception caught: " << e.what() << std::endl;
	}
}

/*Se renderizan todos los elementos de la lista de primitivas*/
void GameScreen::Render()
{
	try
	{
		if (primitivesList->getSize() > 0) {
			AssetNode<Primitives*>* it = primitivesList->first;
			while (it != primitivesList->last->next) {
				it->val->Render();
				it = it->next;
			}
		}
		//if(backGround)	
		//	backGround->Render(); ///Renderiza el fondo
		//if(character)
		//	character->Render(); //Renderiza el personaje
	} catch(exception & e)
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Esta función establece todos los elementos que se encontrarán dentro de esta pantalla de juego
 *@param[void * buff] el buffer que permitirá la entrada de todos los elementos*/
void GameScreen::Init() {
	try {
	
		//setBackGround(new  Texture("Fondo_800x800.png", 0, 0, 800, 800));/*setBackGround(new (buff) Texture("Fondo_800x800.png", 0, 0, 800, 800));*/ //Selecciona una textura para el fondo
		//GetBackGround()->setPosition(Vector2(400, 400)); //Establece su posición
		//setCharacter(new  Texture("HollowKnight.png", 0, 0, 179, 185));//setCharacter(new (buff) Texture("HollowKnight.png", 0, 0, 179, 185)); //Establece una nueva imagen para el personaje
		//GetCharacter()->setPosition(Vector2(400, 400)); //Establece su posición
	} catch(exception & e) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}
