#include "GameManager.h"
GameManager* GameManager::ptr = nullptr;

/*Constructor principal de GameManager*/
GameManager::GameManager()
{
	try {
		/*Inicialización del stack allocator*/
		stackAllocator = StackAllocator::getPTR();
		console = Console::GetPTR();
		if (!console) throw(console);
		lua = Lua::GetPTR();
		String language("Choose your language/Elige tu idioma: 1 == Español.\n2 == English\n");
		language.PrintWString();
		wstring str;
		wcin >> str;
		if (wcin.fail()|| stoi(str) > 2 || stoi(str) <1)
			throw(-1);

		if (str == L"1") console->languages = console->SPANISH;
		else if(str == L"2")  console->languages = console->ENGLISH;
		//lua->Test("Prueba.lua");
		//lua->TestCallFunctionFromCPP("Prueba.lua");
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		quit = false;	//Quit es falso
		GetSingletons();
	}
	catch (int x) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "Hubo un error al elegir el lenguaje ";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s = "There was an error selecting the language ";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		Close();
		quit = true;
	}
	catch (exception & e) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "EXCEPCIÓN ATRAPADA: ";
			wcout << s.GetWString() << e.what() << endl;
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			cout << "EXCEPTION CAUGHT: " << e.what() << endl;
		}
		Close();
		quit = true;
	}
}

/*Destructor principal del juego, se cierran todas las clases que sean singleton y se eliminan apuntadores*/
GameManager::~GameManager()
{
	//Manda a llamar la función release del juego
	
	if (graphics) {
		Graphics::Release();
		graphics = nullptr;	//Haz nulo este apuntador
	}

	if (assetM) {

	AssetManager::Close();
	assetM = nullptr;
	}

	if (audioMGR)
	{

	AudioManager::Release();
	audioMGR = nullptr;
	}

	if (inputMGR) {

	InputManager::Release();
	inputMGR = nullptr;
	}

	if (timer) {

	Timer::Release();
	timer = nullptr;
	}

	if (screenMGR) {
		ScreenManager::Release();
		screenMGR = nullptr;
	}


	console = nullptr;

}

/*Esta función te permite inicializar esta clase, preguntando si ya existe un apuntador de esta clase*/
GameManager* GameManager::GetPtr()
{
	//Si el apuntador es nulo, crea la función, si no, no hagas nada. no se puede volver a crear
	if(ptr == nullptr)
		ptr = new  GameManager();
	
	return ptr;	//Regresa el apuntador
}

/*Esta función setea la ventana del juego, abriendo un archivo .ini y parsea todo su contenido para leer y recuperar su información*/
void GameManager::StartUp()
{
	try
	{
		String s;
	
		clock_t t = clock();
		graphics->setWidth(stackAllocator->getPTR()->iniReader->GetInteger("window", "width", -1)); //Se setea la anchura de la ventana
		graphics->setHeight(stackAllocator->getPTR()->iniReader->GetInteger("window", "height", -1)); //Se setea la altura de la ventana

		//stackAllocator = new StackAllocator(1024 * 1024 * thirdMemory);
		clock_t dt = clock() - t;
		SetConsoleTextAttribute(hConsole, 2);
		if (console->languages == 0) {
			s =("Tomó " + to_string((float)dt / CLOCKS_PER_SEC)+ "segundos inicializar StackAllocator." );
			s.PrintWString();
		} else if (console->languages == 1) {
			s = ("It took " + to_string((float)dt / CLOCKS_PER_SEC) + "seconds to initialize.");
			s.PrintWString();
		}
		int n = 100000;
		t = clock() - t;
		if (console->languages == 0) {
			s = "Tomó " + to_string((float)t / CLOCKS_PER_SEC) + " segundos asignar con memoria dinamica.\n";
			s.PrintWString();
		} else if (console->languages == 1) {
			s = "It took " + to_string((float)dt / CLOCKS_PER_SEC) + "seconds to assign with dynamic memory.";
			s.PrintWString();
		}
		//printf("Tomo %f segundos asignar con memoria dinamica.\n", ((float)t) / CLOCKS_PER_SEC);
		SDL_ShowCursor(0); //Se oculta el cursor
	}
	catch(const std::exception& e)
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

/*Inicializa el update de muchas funciónes que apenas están iniciando*/
void GameManager::EarlyUpdate()
{
	inputMGR->Update();
}

/*Update es la fucnión que actualiza todos los botones y estados del juego*/
void GameManager::Update()
{
	screenMGR->Update();
}

void GameManager::LateUpdate()
{
	inputMGR->UpdatePrevInput();
	timer->Reset();
}

 /*El update principal del juego*/
void GameManager::MainUpdate()
{
	while(!quit)
	{
		
		timer->Update();

		try {
		//Manda a llamar el sistema de eventos de SDL
			while (!SDL_PollEvent(&eventHandler))
			{
				if (eventHandler.type == SDL_QUIT)	//Si se termina el programa, termina el loop
				{
					quit = true;
					break;
				}
				if (inputMGR->getPtr()->keyDown(SDL_SCANCODE_ESCAPE) ){
					quit = true;
					break; 
				}
			}
		}
		catch (exception & e) {
			cout << e.what() << endl;
		}
		if(timer->DeltaTime() >= 1.0f / FrameRate)
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
	console->SaveConsole();
}


/*Función que renderiza cada textura dentro del vector de texturas*/
void GameManager::Render()
{

	graphics->RenderClear();
	screenMGR->Render();
	graphics->Render();	//Actualiza constantemente el render del juego

}

/*Se obtienen todos los singletons del GameEngine*/
void GameManager::GetSingletons()
{
	try {
		timer = Timer::getPTR();
		if (!timer) throw(timer);
		graphics = Graphics::returnPTR(); //Manda a llamar graphics junto con su función del apuntado
		if (!graphics) throw(graphics);
		StartUp();
		graphics->Init();

		assetM = AssetManager::getPTR();
		if (!assetM) throw(assetM);


		inputMGR = InputManager::getPtr();
		if (!inputMGR) throw(inputMGR);
		audioMGR = AudioManager::getPTR();

		if (!audioMGR) throw(audioMGR);
		screenMGR = ScreenManager::getPTR();

		if (!screenMGR) throw(screenMGR);
		screenMGR->Init();

	
		
	}
	catch (Timer * timer) {
		SetConsoleTextAttribute(hConsole, 4);

		if (console->languages == 0) {
			String s = "PELIGRO: TIMER NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s = "WARNING: TIMER DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		exit(0);
	}
	catch (Graphics * graphics) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "PELIGRO: GRAPHICS NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s = "WARNING: GRAPHICS DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		exit(0);
	}
	catch (AssetManager * assetM) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "PELIGRO: ASSET MANAGER NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s ="WARNING: ASSET MANAGER DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		exit(0);
	}
	catch (InputManager * inputMGR) {
		if (console->languages ==0) {
			String s = "PELIGRO: INPUT MANAGE NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s = "WARNING: INPUT MANAGER DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		SetConsoleTextAttribute(hConsole, 4);
		exit(0);
	}
	catch (AudioManager * audioMGR) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "PELIGRO: AUDIO MANAGER NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s =  "WARNING: AUDIO MANAGER DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		exit(0);
	}
	catch (ScreenManager * screenMGR) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "PELIGRO: SCREEN MANAGER NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages ==1) {
			String s = "WARNING: SCREEN MANAGER DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		exit(0);
	}
	catch (Console * console) {
		SetConsoleTextAttribute(hConsole, 4);
		if (console->languages == 0) {
			String s = "PELIGRO: CONSOLE NO PUDO ABRIRSE";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		else if (console->languages == 1) {
			String s = "WARNING: CONSOLE DIDN'T OPEN";
			s.PrintWString();
			console->finalMSG += s.GetWString() + L"\n";
		}
		exit(0);
	}
}



//Función que cierra esta clase y elimina todos los elementos del juego
void GameManager::Close()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
	
}
