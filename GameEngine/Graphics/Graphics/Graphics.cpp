#include "Graphics.h"

Graphics* Graphics::ptr = NULL;
bool Graphics::initialize = false;


/*Esta función te regresa un apuntador a la clase de Graphics ya que es un Singleton y sólo necesitamos una instancia de esta clase.*/
Graphics* Graphics::returnPTR()
{
	//Su el apuntador es nulo, crealo
	if(ptr == nullptr)
	{
		ptr = new Graphics();
	} 

	return ptr;
}

/*Al cerrar el juego, manda a llamar esta función donde se borran todas las variables*/
void Graphics::Release()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
	initialize = false;	//El booleando hazlo falso
	
	//Cierra todos los programas
}

/*Constructor de la clase graphics*/
Graphics::Graphics()
{
	renderer = nullptr; //Haz nulo el renderer
}

/*Manda a llamar el destructor de la clase*/
Graphics::~Graphics()
{
	SDL_DestroyWindow(mainWindow);	//Destruye la ventana de la ventana
	mainWindow = nullptr;	//Haz la ventana nula
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	TTF_Quit();
	IMG_Quit();
	
	SDL_Quit();	//Cierra SDL
}

/*Esta función pregunta si la ventana se hace falsa o verdadera, dependiendo de la respuesta se crea o no la ventana*/
bool Graphics::Init()
{
	try {

		//Mensaje que muestra si no se inicializa la ventana
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			throw("SDL could not initialize! SDL Error: %s",SDL_GetError());
		
		} else   //Si logra inicializar, sucederá esto
		{
			if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				throw("Warning: Linear texture filtering not enabled!");
			}
	
			//Se crea la ventana de juego con las variables de ancho y altura
			mainWindow = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
			//Si no logra crearse, presentará el siguiente mensaje
			if(!mainWindow)
			{
				throw("Window could not be created! SDL Error: %s\n", SDL_GetError());
			} else
			{	//Pero si logra crearse, empezaré con el ciclo de render de la ventana
	
				renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
				if(renderer == NULL)
				{
					throw("Renderer Creation Error: %s\n", SDL_GetError());
				}
	
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	
				int flags = IMG_INIT_PNG;	//"Bandera" que nos permite determinar si se cargan imágenes o no
				//If que pregunta si se logró cargar el programa de SDL_Image
				if(!(IMG_Init(flags) & flags))
				{
					throw("IMG initialization ERROR: %s\n", IMG_GetError());
				}
	
				
				if(TTF_Init() == -1)
				{
					throw("TTF ERROR: %s\n", TTF_GetError());
				}
	
				surface = SDL_GetWindowSurface(mainWindow);
			}	
			return true;	//Regresa verdadero
		}
	}
	catch (string str) {
		SetConsoleTextAttribute(hConsole, 4);
		cout << str << endl;
		return false;
	}
	catch(...) {

	}
}

/*Esta función nos permite determinar la anchura de la ventana de juego
*@param[int width] la anchura de la ventana que se quiere que se tenga
*/
void Graphics::setWidth(int width)
{
	try
	{
		//Pregunta si width es menor a cero o mayor a 1920
		if(width < 0 || width > 1920)
			throw(width); //En caso de serlo, lanza un error
		else
		{
			SCREEN_WIDTH = width; //En caso de no serlo, establece la nueva anchura de la pantalla.
		}
	} catch(int x)
	{
		cout << "Your width : " << x << " is out of bounds (0 - 1920)\n";
	} catch(exception & e)
	{
		cout << "EXCEPTION CAUGHT:" << e.what() << endl;
	}
}

/*Esta función nos permite determinar la altura de la ventana de juego
*@param[int height] la altura de la ventana que se quiere que se tenga
*/
void Graphics::setHeight(int height)
{
	try
	{
		//Pregunta si widtheighth es menor a cero o mayor a 1920
		if(height < 0 || height > 1080)
			throw(height); //En caso de serlo, lanza un error
		else
		{
			SCREEN_HEIGHT = height; //En caso d eno serlo, establece la nueva altura de la pantalla.
		}
	} catch(int x)
	{
		cout << "Your height : " << x << " is out of bounds (0 - 1080)\n";
	} catch(exception & e)
	{
		cout << "EXCEPTION CAUGHT:" << e.what() << endl;
	}
}

SDL_Renderer* Graphics::getRenderer()
{
	try {
		if (renderer)
			return renderer;
		else {
			throw(0);
		}
	}
	catch (int x) {
		cout << "There is no available Renderer!\n";
	}
}

SDL_Surface* Graphics::GetSurface()
{
	try {
		if (surface)
			return surface;
		else
			throw(0);
	}
	catch (int x) {
		cout << "There is no surface available!\n";
	}
	
}


/*Función que carga texturas por medio de su dirección de su dirección en el archivo y se le añadirá a un vector
	@param[ path ] direccion dentro de la carpeta donde se encuentra el archivo
	@param[ vector ] vector al que se le añadirá la información
	@return[texture] una textura que modificará el surface actual*/
SDL_Texture* Graphics::LoadTexture(std::string path, AssetList<SDL_Texture*>& vector)
{
	SDL_Texture* texture = NULL;	//Empieza en nula 
	SDL_Surface* surface = IMG_Load(path.c_str());	//Esta superficie toma la imagen de este path

	//Si es nulo, manda a llamar ese error
	if(surface == nullptr)
	{
		printf("IMAGE LOAD ERROR: Pat(%s) - Error(%s)\n", path.c_str(), IMG_GetError());	//Error que indica que falló la carga de imagen
		return texture;
	} else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);	//Se crea una textura gracias a la superficie que carga la imagen.
		vector.push_back(path, texture);	//Se ingresa esta variable hasta atrás 
		
		//Si la textura es nula, imprime su error
		if(texture == nullptr)
		{
			printf("Create Texture Erro: %sn", SDL_GetError());	//
			return texture;
		}

	}
	SDL_FreeSurface(surface);	//Se libera la superficie actual
	return texture;
}


/*Crea una textura para el texto
	@param[ font ] estilo de la palabras
	@param[text] texto que se quiere imprimir
	@áram[key] llave que distinguirá a los textos
	@param[ textVector ] vector de textos que almacenará un nuevo elemento
	@param */
SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, std::string key, 
										 AssetList<SDL_Texture*>& textVector, AssetList<TTF_Font*>& fontVector, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);	//Crea una superficie con el texto indicado, junto a su font y color
	
	//Si la superficie es nula, imprime su error
	if(surface == nullptr)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return nullptr;	//Regresa nuñp
	}
	//En caso contrario
	else
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);	//Crea una textura con la superficie de texto
		textVector.push_back(text, texture);	//Añade la textura al vector de texturas
		fontVector.push_back(key, font);	//Añade el font al vector de fonts

		//Si la textura es nula, imprime un error
		if(texture == nullptr)
		{
			printf("Text texture Creation Error: %s\n", SDL_GetError());
			return nullptr;
		}
		SDL_FreeSurface(surface);
		return texture;
	}
}

/*Se limpia el buffer actual*/
void Graphics::RenderClear()
{
	SDL_RenderClear(renderer);
}

/*Función que manda a llamar las texturas que se creen y se dibujan en la superficie*/
void Graphics::DrawTexture(SDL_Texture* texture,SDL_Rect *clipp, SDL_Rect* rect)
{
	SDL_RenderCopy(renderer, texture, clipp, rect);
}

/*Manda a llamar la función render al momento de crear una nueva ventana*/
void Graphics::Render()
{
	SDL_SetRenderDrawColor(Graphics::returnPTR()->getRenderer(), 0x00, 0x00, 0x00, 0xff);
	SDL_RenderPresent(renderer); //Actualiza el buffer de la ventana

}