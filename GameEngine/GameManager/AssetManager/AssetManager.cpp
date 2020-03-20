#include "AssetManager.h"

AssetManager* AssetManager::ptr = nullptr;



AssetManager::AssetManager()
{
	console = Console::GetPTR();
}

/*Destructo de la clase AssetManager. Buscar� cerrar todas las librer�as externas
tanto de fonts, m�sica, etc.*/
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

/*Esta funci�n busca la direcci�n de la imagen dentro de los achivos
	@param[ filenName ]  Nombre de la textura dentro del archivo del proyecto
	@return un apuntador a SDL_Texture*/
SDL_Texture* AssetManager::GetTexture(std::wstring fileName)
{
	try
	{
		std::string fullPath = SDL_GetBasePath();	//Este string con la funci�n SDL_GetBasePath busca dentro de todos los archivos hasta encontrar con la ubicaci�n correcta del Debug
		String s = fullPath;
		s.GetWString().append(L"Assets/Textures/" + fileName);
		SDL_Texture* text = textures.returnTemplate(s.GetWString());	//Crea una variable que guarde la posici�n de la textura en el vector de texturas
		
		/*Si esta funci�n regresa nula*/
		if(text == NULL)
			text = Graphics::returnPTR()->LoadTexture(s.GetWString(), textures); //Crea una variable SDL_Texture y carga una textura al vector de texturas
		
	
		return text;	//Regresa esta textura
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
	
}

/*Esta funci�n obtiene el texto dentro de la capeta del juego
	@param[ text] texto que se quiere imprimir
	@param[ fileName ] nombre del font
	@param[ size ] tama�o de la palabras
	@param[ color ] color de las palabras
	@return una textura que se podr� imprimir en la pantalla*/
SDL_Texture* AssetManager::GetText(wstring text, wstring fileName, int size, SDL_Color color)
{
	try
	{
		
		TTF_Font* myFont = GetFont(fileName, size);	//Crea un font con sus respectivas caracter�sticas
		string s = (char*)size + (char)color.r + (char)color.g + (char)color.b;
		String s2 = "";
		s2 += text + fileName + s2.convert(s);	//Crea una llave que distinguir� a todos los fonts 
		this->text = text;
		SDL_Texture* texture = texts.returnTemplate(s2.GetWString());
		//Pregunta si el font ya fue creado
		if(texture == nullptr)
			texture = Graphics::returnPTR()->CreateTextTexture(myFont, text, s2.GetWString(), texts, font, color); //Crea una textura con las caracter�sticas creadas
		
		return texture;

	} catch(exception & e)
	{
		cout << "Eceptio caught: " << e.what() << endl;
	} catch(...)
	{
		printf("Ups! It crashed!\n");
	}
}

/*Funci�n que se encargar� de abrir los archivos de m�sica. Si no existe en el vector de m�sica, lo crear�, pero si ya existe regresar� el archivo en esta 
direcci�n
	@param[ fileName ] ubicaci�n del archivo Debug
	@return archivo de m�sica que se reproducir�*/
Mix_Music* AssetManager::GetMusic(wstring fileName)
{
	try
	{
		string fullPath = SDL_GetBasePath();	//Consigue el directorio base del archivo
		String s = fullPath;
		s.GetWString().append(L"Assets/Music/" + fileName);	//Agrega este string a full path
		Mix_Music* myMusic = music.returnTemplate(s.GetWString());
		//Busca en lista de m�sica si es que ya existe
		if( myMusic== nullptr)
		{
			myMusic = myMusic = Mix_LoadMUS(fullPath.c_str());	//Crea una variable que sea similar a la m�sica que se encuentra en esta direcci�n
			//Si sigue siendo nula, imprime un error
			if(myMusic == nullptr)
			{
				printf("Music error loading: File: %s ---- Error: %s", fullPath.c_str(), Mix_GetError());
				return nullptr;	//Regresa nulo
			}
			
		} 
		return myMusic;	//Regresa la variable que se encuenrta aqu�
	} catch(exception & e)
	{
		cout << "Eceptio caught: " << e.what() << endl;
	} catch(...)
	{
		printf("Ups! It crashed!\n");
	}
	


}

/*Funci�n que se encargar� de obtener el sound effect dentro de los archivos de SFX. Si no existe en el vector de sfx, lo crear�, pero si ya existe 
regresar� este sfx.
	@param[ fileName ]*/
Mix_Chunk* AssetManager::GetSFX(wstring fileName)
{
	string fullPath = SDL_GetBasePath();	//Busca el archivo Debug dentro del archivo de juego
	String s = fullPath;
	s.GetWString().append(L"Assets/SFX/" + fileName);	//A�adir� las carpetas indicadas al string de fullPath
	Mix_Chunk* chunk = sfx.returnTemplate(s.GetWString());
	//Buscar� en el vector de sfx si ya existe el archivo con esta direcci�n
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
	@param[ size ] tama�o de la letra
	@return te regresa el font*/
TTF_Font* AssetManager::GetFont(wstring fileName, int size)
{
	/*Busca la direcci�n desde la carpeta ra�z del programa y despu�s llega hsata Debug
	y avanza hasta las cartpetas indicadas en el Append*/
	string fullPath = SDL_GetBasePath();
	String s = fullPath;
	s.GetWString().append(L"Assets/Fonts/" + fileName);
	string s2 = (char*)size;
	s.GetWString() += s.convert(s2);

	//Pregunta si en el vector ya existe o si es nulo
	if(font.returnTemplate(s.GetWString()) == nullptr)
	{
		TTF_Font* tFont = TTF_OpenFont(fullPath.c_str(), size);	//Guarda un font en esta posici�n
		
		if (tFont == nullptr) {
			
			printf("Font loading Error: Font: %s -- Error: %s", fileName.c_str(), TTF_GetError());
		}
		return tFont;
	}

}


