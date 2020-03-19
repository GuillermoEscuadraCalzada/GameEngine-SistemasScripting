#include "GameManager.h"
GameManager* GameManager::ptr = nullptr;

/*Constructor principal de GameManager*/
GameManager::GameManager()
{
	try {
		lua = new Lua();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		quit = false;	//Quit es falso
		GetSingletons();
		square = new Square(graphics->SCREEN_WIDTH / 2, graphics->SCREEN_HEIGHT / 2, 50, 50);
	}  catch (exception & e) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Destructor principal del juego, se cierran todas las clases que sean singleton y se eliminan apuntadores*/
GameManager::~GameManager()
{
	//Manda a llamar la función release del juego
	Graphics::Release();
	graphics = nullptr;	//Haz nulo este apuntador


	AssetManager::Close();
	assetM = nullptr;

	AudioManager::Release();
	audioMGR = nullptr;

	InputManager::Release();
	inputMGR = nullptr;

	Timer::Release();
	timer = nullptr;

	ScreenManager::Release();
	screenMGR = nullptr;

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
		lua->LoadFile("Prueba.lua");
		/*Inicialización del stack allocator*/
		clock_t t = clock();
		stackAllocator = StackAllocator::getPTR();
		graphics->setWidth(stackAllocator->getPTR()->iniReader->GetInteger("window", "width", -1)); //Se setea la anchura de la ventana
		graphics->setHeight(stackAllocator->getPTR()->iniReader->GetInteger("window", "height", -1)); //Se setea la altura de la ventana

		//stackAllocator = new StackAllocator(1024 * 1024 * thirdMemory);
		clock_t dt = clock() - t;
		SetConsoleTextAttribute(hConsole, 2);
		printf("Tomo %f segundos inicializar StackAllocator.\n", ((float)dt) / CLOCKS_PER_SEC);

		int n = 100000;
		t = clock() - t;
		printf("Tomo %f segundos asignar con memoria dinamica.\n", ((float)t) / CLOCKS_PER_SEC);
		SDL_ShowCursor(0); //Se oculta el cursor
	}
	catch(const std::exception& e)
	{
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
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
	while(!quit /*&& menuInicio->continuee*/)
	{
		timer->Update();

		//Manda a llamar el sistema de eventos de SDL
		while(SDL_PollEvent(&eventHandler) != 0)
		{
			if(eventHandler.type == SDL_QUIT)	//Si se termina el programa, termina el loop
				quit = true;
			if (inputMGR->getPtr()->keyDown(SDL_SCANCODE_ESCAPE) ){
				quit = true;
			}

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

		console = Console::GetPTR();
		if (!console) throw(console);
		
	}
	catch (Timer * timer) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: TIMER DIDN'T OPEN" << endl;
		exit(0);
	}
	catch (Graphics * graphics) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: GRAPHICS DIDN'T OPEN" << endl;
		exit(0);
	}
	catch (AssetManager * assetM) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: ASSET MANAGER DIDN'T OPEN" << endl;
		exit(0);
	}
	catch (InputManager * inputMGR) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: INPUT MANAGER DIDN'T OPEN" << endl;
		exit(0);
	}
	catch (AudioManager * audioMGR) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: AUDIO MANAGER DIDN'T OPEN" << endl;
		exit(0);
	}
	catch (ScreenManager * screenMGR) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: SCREEN MANAGER DIDN'T OPEN" << endl;
		exit(0);
	}
	catch (Console * console) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "WARNING: CONSOLE DIDN'T OPEN" << endl;
		exit(0);
	}
}



//Función que cierra esta clase y elimina todos los elementos del juego
void GameManager::Close()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
	
}
