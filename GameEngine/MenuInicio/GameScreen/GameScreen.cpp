#include "GameScreen.h"
bool createObj = false;
GameScreen::GameScreen() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	timer = Timer::getPTR();	//Busca el apuntador del tiempo
	input = InputManager::getPtr();	//Busca el apuntador del input
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	textureList = new myVector<Texture*>();
	primitivesList = new AssetList<Primitives*>();
	stackAllocator = StackAllocator::getPTR();
	console = Console::GetPTR();
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

void GameScreen::CreateObjects()
{
	try {
		if (createObj == false) {
			SetConsoleTextAttribute(hConsole, 6);

			if (console->languages == 0)
				s = "Presiona el botón 1 para crear un cuadrado.\nPresiona el botón 2 para crear un círculo.";
			else if (console->languages == 1)
				s = "Press button 1 to create a Square.\nPress button 2 to create a circle.";
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
			SetConsoleTextAttribute(hConsole, 2);

			wstring name;
			if (console->languages == 0)
				name = L"Escribe el nombre de tu objeto\n";
			else if (console->languages == 1)
				name = L"Write the name of your object\n";
			wcout << name;
			wcin >> name;
			primitivesList->push_back(name, sq);
			primitivesList->print();
			createObj = false;
		}
		else if (input->keyPressed(SDL_SCANCODE_2)) {
			void* buff = stackAllocator->alloc(sizeof(Circle*));
			Circle* circle = new /*(buff)*/ Circle();
			circle->SetUpValues();
			SetConsoleTextAttribute(hConsole, 2);
			wstring name;
			if (console->languages == 0)
				name = L"Escribe el nombre de tu objeto\n";
			else if (console->languages == 1)
				name = L"Write the name of your object\n";
			wcout << name;
			wcin >> name;
			primitivesList->push_back(name, circle);
			primitivesList->print();
			createObj = false;
		}
	}
	catch (...) {

	}
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
		if (console->languages == 0) {
			String s = "Este objeto es nulo.";
			s.PrintWString();
		}
		else if (console->languages == 1) {
			String s = "This object is nil.";
			s.PrintWString();
		}
		console->finalMSG += s.GetWString();
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
		input->Update();
		if (createObj == false) {
			SetConsoleTextAttribute(hConsole, 6);
		
			if (console->languages == 0)
				s = "Presiona el botón 1 para crear un cuadrado.\nPresiona el botón 2 para crear un círculo.";
			else if (console->languages == 1)
				s = "Press button 1 to create a Square.\nPress button 2 to create a circle.";
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
			SetConsoleTextAttribute(hConsole, 2);

			wstring name;
			if (console->languages == 0)
				name = L"Escribe el nombre de tu objeto\n";
			else if (console->languages == 1)
				name = L"Write the name of your object\n";
			wcout << name;
			wcin >> name;
		    primitivesList->push_back(name, sq);
			primitivesList->print();
			createObj = false;
		}
		else if (input->keyPressed(SDL_SCANCODE_2)) {
			void* buff = stackAllocator->alloc(sizeof(Circle*));
			Circle* circle = new /*(buff)*/ Circle();
			circle->SetUpValues();
			SetConsoleTextAttribute(hConsole, 2);
			wstring name;
			if (console->languages == 0)
				name = L"Escribe el nombre de tu objeto\n";
			else if (console->languages == 1)
				name = L"Write the name of your object\n";
			wcout << name;
			wcin >> name;
			primitivesList->push_back(name, circle);
			primitivesList->print();
			createObj = false;
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
		if (console->languages == 0) {
			String s = "EXCEPCIÓN ATRAPADA: ";
			wcout << s.GetWString() << e.what() << endl;
		}
		else if (console->languages == 1) {
			String s = "EXCEPTION CAUGHT: ";
			wcout << s.GetWString() << e.what() << endl;
		}
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

	} catch(exception & e)
	{
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "EXCEPCIÓN ATRAPADA: ";
			wcout << s.GetWString() << e.what() << endl;
		}
		else if (console->languages == 1) {
			String s = "EXCEPTION CAUGHT: ";
			wcout << s.GetWString() << e.what() << endl;
		}
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
		if (console->languages == 0) {
			String s = "EXCEPCIÓN ATRAPADA: ";
			wcout << s.GetWString() << e.what() << endl;
		}
		else if (console->languages == 1) {
			String s = "EXCEPTION CAUGHT: ";
			wcout << s.GetWString() << e.what() << endl;
		}
	}
}
