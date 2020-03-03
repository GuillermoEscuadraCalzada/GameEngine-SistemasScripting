#include "GameManager.h"
GameManager* GameManager::ptr = nullptr;
AnimatedTexture* hollowKnight;


/*Constructor principal de GameManager*/
GameManager::GameManager()
{
	try {

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		quit = false;	//Quit es falso
		timer = Timer::getPTR();
		graphics = Graphics::returnPTR(); //Manda a llamar graphics junto con su función del apuntador
		if(!Graphics::returnPTR())
			throw(graphics);
		StartUp();
		graphics->Init();
		//Si es falso, termina el update del juego
		assetM = AssetManager::getPTR();
		inputMGR = InputManager::getPtr();
		audiMGR = AudioManager::getPTR();
		screenMGR = ScreenManager::getPTR();
		
		buff = stackAllocator->alloc(sizeof(Texture*));
		screenMGR->Init(buff);

	} catch(Graphics* graphics) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "GRAPHICS DIDN'T OPEN" << endl;
	} catch(exception & e) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}

	//screenMGR->gameScreen->setBackGround( new /*(buff)*/ Texture("Fondo_800x800.png", 0, 0, 800, 800));
	//screenMGR->gameScreen->GetBackGround()->setPosition(Vector2(400, 400));

	//screenMGR->gameScreen->setCharacter(new /*(buff)*/ Texture("HollowKnight.png", 0, 0, 179, 185));
	//screenMGR->gameScreen->GetCharacter()->setPosition(Vector2(400, 400));
}

/*Destructor principal del juego, se cierran todas las clases que sean singleton y se eliminan apuntadores*/
GameManager::~GameManager()
{
	//Manda a llamar la función release del juego
	Graphics::Release();
	graphics = nullptr;	//Haz nulo este apuntador
	
	delete backGround;
	backGround = nullptr;

	AssetManager::Close();
	assetM = nullptr;

	AudioManager::Release();
	audiMGR = nullptr;

	InputManager::Release();
	inputMGR = nullptr;

	Timer::Release();
	timer = nullptr;

	ScreenManager::Release();
	screenMGR = nullptr;

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
		initialize->StartUp();
		INIReader reader("config.ini"); //Se abre el archivo de nuevo
		if(reader.ParseError() < 0)
		{ //Si no se puede leer nada, manda error
			string str = "No se puede cargar archivo ini\n";
			throw(str);
		}

		graphics->setWidth(reader.GetInteger("window", "width", -1)); //Se setea la anchura de la ventana
		graphics->setHeight(reader.GetInteger("window", "height", -1)); //Se setea la altura de la ventana
		thirdMemory = reader.GetInteger("memory", "third", -1);
		clock_t t = clock();

		//asignar 32 MB de memoria dinamica
		stackAllocator = new StackAllocator(1024 * 1024 * thirdMemory);
		clock_t dt = clock() - t;
		SetConsoleTextAttribute(hConsole, 2);
		printf("Tomo %f segundos inicializar StackAllocator.\n", ((float)dt) / CLOCKS_PER_SEC);

		int n = 100000;
		t = clock() - t;
		printf("Tomo %f segundos asignar con memoria dinamica.\n", ((float)t) / CLOCKS_PER_SEC);
		SDL_ShowCursor(0); //Se oculta el cursor
	} catch(string s)
	{
		SetConsoleTextAttribute(hConsole, 4);
		//system("color 2");
		cout << s;
		exit(0);

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

	/*audiMGR->PlayMusic("funkorama.mp3");*/
	while(!quit /*&& menuInicio->continuee*/)
	{
		timer->Update();

		//Manda a llamar el sistema de eventos de SDL
		while(SDL_PollEvent(&eventHandler) != 0)
		{
			if(eventHandler.type == SDL_QUIT)	//Si se termina el programa, termina el loop
				quit = true;
		}

		if(timer->DeltaTime() >= 1.0f / FrameRate)
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}


/*Función que renderiza cada textura dentro del vector de texturas*/
void GameManager::Render()
{

	graphics->ClearBackBuffer();

	screenMGR->Render();

	graphics->Render();	//Actualiza constantemente el render del juego

}

int GameManager::GetWidth() {
	return graphics->SCREEN_WIDTH;
}

int GameManager::GetHeight() {
	return graphics->SCREEN_HEIGHT;
}

//Función que cierra esta clase y elimina todos los elementos del juego
void GameManager::Close()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
}
