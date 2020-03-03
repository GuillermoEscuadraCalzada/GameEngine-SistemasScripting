#include "AssetManager.h"

AssetManager* AssetManager::ptr = nullptr;



AssetManager::AssetManager()
{
}

/*Destructo de la clase AssetManager. Buscará cerrar todas las librerías externas
tanto de fonts, música, etc.*/
AssetManager::~AssetManager()
{
	//Ir buscando durante el vector de fonts y cerrar cada font
	AssetNode<TTF_Font*>* ffont = font.first;
	//Avanza hasta que sea nulo
	while(ffont != nullptr)
	{
		AssetNode<TTF_Font*>* temp = ffont->next;
		//TTF_CloseFont(ffont->val);	//Se cierra el font
		delete ffont;
		ffont= nullptr;
		ffont = temp;	//Avanza a su siguiente puesto en el vector
	}

	//Ir buscando en el vector de texturas
	AssetNode<SDL_Texture*>* textureIt = textures.first;
	//Avanzar hasta que sea nulo
	while(textureIt != nullptr)
	{
		AssetNode<SDL_Texture*>* temp = textureIt->next;
		SDL_DestroyTexture(textureIt->val);	//Destruir la textura
		delete textureIt;
		textureIt = nullptr;
		textureIt = temp;	//Avanzar al siguiente
	}

	//Ir buscando en el vector de textos
	AssetNode<SDL_Texture*>* textIt = texts.first;

	//Avanza hasta que sea nulo
	while(textIt != nullptr)
	{
		AssetNode<SDL_Texture*>* temp = textIt->next;

		SDL_DestroyTexture(textIt->val);	//Destruye las texturas
		delete textIt;
		textIt = nullptr;
		textIt = temp;

	}

	AssetNode<Mix_Music*>* musicIt = music.first;
	while(musicIt != nullptr)
	{
		AssetNode<Mix_Music*>* temp = musicIt->next;

		Mix_FreeMusic(musicIt->val);
		delete musicIt;
		musicIt = nullptr;
		musicIt = temp;
	}

	AssetNode<Mix_Chunk*>* chunkIt = sfx.first;
	while(musicIt != nullptr)
	{
		AssetNode<Mix_Chunk*>* temp = chunkIt->next;

		Mix_FreeChunk(chunkIt->val);
		delete chunkIt;
		chunkIt = nullptr;
		chunkIt = temp;
	}
	
}

/*Obtienes el apuntador de la clase AssetManager*/
AssetManager* AssetManager::getPTR()
{
	//Pregunta si el apuntador es nulo, si lo es, crealo, si no, no hagas nada
	if(ptr == nullptr)
		ptr = new AssetManager();

	return ptr;
}

void AssetManager::Close()
{
	delete ptr;
	ptr = nullptr;

}

/*Esta función busca la dirección de la imagen dentro de los achivos
	@param[ filenName ]  Nombre de la textura dentro del archivo del proyecto
	@return un apuntador a SDL_Texture*/
SDL_Texture* AssetManager::GetTexture(std::string fileName)
{
	try
	{
		std::string fullPath = SDL_GetBasePath();	//Este string con la función SDL_GetBasePath busca dentro de todos los archivos hasta encontrar con la ubicación correcta del Debug
		fullPath.append("Assets/Textures/" + fileName);	//Esto toma el archivo donde guardaremos la dirección y le añadirá el nombre de la imagen
		SDL_Texture* text = textures.returnTemplate(fullPath);	//Crea una variable que guarde la posición de la textura en el vector de texturas
		
		/*Si esta función regresa nula*/
		if(text == NULL)
			text = Graphics::returnPTR()->LoadTexture(fullPath, textures); //Crea una variable SDL_Texture y carga una textura al vector de texturas
		
	
		return text;	//Regresa esta textura
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
	
}

/*Esta función obtiene el texto dentro de la capeta del juego
	@param[ text] texto que se quiere imprimir
	@param[ fileName ] nombre del font
	@param[ size ] tamaño de la palabras
	@param[ color ] color de las palabras
	@return una textura que se podrá imprimir en la pantalla*/
SDL_Texture* AssetManager::GetText(string text, string fileName, int size, SDL_Color color)
{
	try
	{
		
		TTF_Font* myFont = GetFont(fileName, size);	//Crea un font con sus respectivas características

		string key = text + fileName + (char)size +(char)color.r+ (char)color.g + (char)color.b;	//Crea una llave que distinguirá a todos los fonts 
		this->text = text;
		SDL_Texture* texture = texts.returnTemplate(key);
		//Pregunta si el font ya fue creado
		if(texture == nullptr)
			texture = Graphics::returnPTR()->CreateTextTexture(myFont, text, key, texts, font, color); //Crea una textura con las características creadas
		
		return texture;

	} catch(exception & e)
	{
		cout << "Eceptio caught: " << e.what() << endl;
	} catch(...)
	{
		printf("Ups! It crashed!\n");
	}
}

/*Función que se encargará de abrir los archivos de música. Si no existe en el vector de música, lo creará, pero si ya existe regresará el archivo en esta 
dirección
	@param[ fileName ] ubicación del archivo Debug
	@return archivo de música que se reproducirá*/
Mix_Music* AssetManager::GetMusic(string fileName)
{
	try
	{
		string fullPath = SDL_GetBasePath();	//Consigue el directorio base del archivo
		fullPath.append("Assets/Music/" + fileName);	//Agrega este string a full path
		Mix_Music* myMusic = music.returnTemplate(fullPath);
		//Busca en lista de música si es que ya existe
		if( myMusic== nullptr)
		{
			myMusic = myMusic = Mix_LoadMUS(fullPath.c_str());	//Crea una variable que sea similar a la música que se encuentra en esta dirección
			//Si sigue siendo nula, imprime un error
			if(myMusic == nullptr)
			{
				printf("Music error loading: File: %s ---- Error: %s", fullPath.c_str(), Mix_GetError());
				return nullptr;	//Regresa nulo
			}
			
		} 
		return myMusic;	//Regresa la variable que se encuenrta aquí
	} catch(exception & e)
	{
		cout << "Eceptio caught: " << e.what() << endl;
	} catch(...)
	{
		printf("Ups! It crashed!\n");
	}
	


}

/*Función que se encargará de obtener el sound effect dentro de los archivos de SFX. Si no existe en el vector de sfx, lo creará, pero si ya existe 
regresará este sfx.
	@param[ fileName ]*/
Mix_Chunk* AssetManager::GetSFX(string fileName)
{
	string fullPath = SDL_GetBasePath();	//Busca el archivo Debug dentro del archivo de juego
	fullPath.append("Assets/SFX/" + fileName);	//Añadirá las carpetas indicadas al string de fullPath
	Mix_Chunk* chunk = sfx.returnTemplate(fullPath);
	//Buscará en el vector de sfx si ya existe el archivo con esta dirección
	if( chunk == nullptr)
	{
		chunk = Mix_LoadWAV(fullPath.c_str());
		
		if(chunk == nullptr)
		{
			printf("Sound Effect error loading: File: %s ---- Error: %s", fullPath.c_str(), Mix_GetError());
			return nullptr;
		}
	
	} 
	return chunk;
}

/*Consigue el tipo de letra que se va a usar para el texto
	@param[ fileName ] Nombre del archivo
	@param[ size ] tamaño de la letra
	@return te regresa el font*/
TTF_Font* AssetManager::GetFont(string fileName, int size)
{
	/*Busca la dirección desde la carpeta raíz del programa y después llega hsata Debug
	y avanza hasta las cartpetas indicadas en el Append*/
	string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Fonts/" + fileName);

	string key = fullPath + (char)size;	//Se consigue una llave con el fullPath + el tamaño

	//Pregunta si en el vector ya existe o si es nulo
	if(font.returnTemplate(key) == nullptr)
	{
		TTF_Font* tFont = TTF_OpenFont(fullPath.c_str(), size);	//Guarda un font en esta posición
		
		if(tFont == nullptr)
			printf("Font loading Error: Font: %s -- Error: %s", fileName.c_str(), TTF_GetError());
		return tFont;
	}

}


