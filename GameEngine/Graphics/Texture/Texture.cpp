#include "Texture.h"


Texture::Texture()
{
}

/*Constructor de la clase Texture, requiere de un string que será la ubicación de la imagen
	@param[ path ] ubiación de donde se encuentra la imagen*/
Texture::Texture(std::wstring path)
{
	rect = new SDL_Rect();

	graphics = Graphics::returnPTR();	//Manda a crear o llamar el apuntador de la clase graphics

	texture = AssetManager::getPTR()->GetTexture(path);	//Manda a llamar dos clases, AssetManagerPTR, donde obtiene su apuntador y luego GetTexture, donde consigue la imagen 
	this->textText = path;
	clipped = false;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect->w = width;
	rect->h = height;

	
}

/*Constructor de la clase texture que sirve para texturas animadas con imágenes que tienen más de un elemnto. Esto nos permite avanzar entre cada una para poder cambiar la textura actual
	@param[path] dirección de la textura dentro del archivo debug del juego
	@param[x] posición en la imagen en X donde comienza la animación
	@param[y] posición de la imagen en Y donde comienza la animación
	@param[w} anchura del segmento de la imagen
	@param[h] altura del segmento d ela imagen*/
Texture::Texture(std::wstring path, int x, int y, int w, int h, int id)
{
	graphics = Graphics::returnPTR();	//Pregunta por el apuntador de la clase Graphics
	texture = AssetManager::getPTR()->GetTexture(path);	//Pregunta por el apuntador de la classe assetManager y luego busca la función de GetTexture
	this->textText = path;	//Path se igual al path del argumento
	clipped = true;	//Clipp es true
	rect = new SDL_Rect();
	width = w;	//width es igual a la w del argumento
	height = h;	//Height es igual a la h del argumento
	rect->w = width;	//La anchura de rect es igual a width
	rect->h = height;	//La altrua de rect es igual a height
	ID = id;
	clippedRect.x = x;	//La posición de clippRect en X es igual a x
	clippedRect.y = y;	//La posición de clippRect en Y es igual a y
	clippedRect.w = w;	//La anchura de clippedRect es igual a la w del parámetro
	clippedRect.h = h;	//La altura de clippedRect es igual a la h del parámetro



}

Texture::Texture(std::wstring path, int x, int y, int w, int h)
{
	graphics = Graphics::returnPTR();	//Pregunta por el apuntador de la clase Graphics
	texture = AssetManager::getPTR()->GetTexture(path);	//Pregunta por el apuntador de la classe assetManager y luego busca la función de GetTexture
	this->textText = path;	//Path se igual al path del argumento
	clipped = true;	//Clipp es true
	rect = new SDL_Rect();
	width = w;	//width es igual a la w del argumento
	height = h;	//Height es igual a la h del argumento
	rect->w = width;	//La anchura de rect es igual a width
	rect->h = height;	//La altrua de rect es igual a height
	clippedRect.x = x;	//La posición de clippRect en X es igual a x
	clippedRect.y = y;	//La posición de clippRect en Y es igual a y
	clippedRect.w = w;	//La anchura de clippedRect es igual a la w del parámetro
	clippedRect.h = h;	//La altura de clippedRect es igual a la h del parámetro
}

/*Constructor de la clase texture que SÓLO sirve para añadir textos
	@param[text] el text que queremos que se imprima en la pantalla
	@param[fontPath] ubicación del font dentro del archivo del juego
	@param[size] tamaño de las letras del texto.
	@param[ color ] color de las palabras*/ 
Texture::Texture(std::wstring text, std::wstring fontPath, int size, SDL_Color _color)
{
	graphics = Graphics::returnPTR();	//Llama el apuntador de graphics
	color = _color;
	String s;
	texture = AssetManager::getPTR()->GetText(text, fontPath, size , color);	//Obtiene el texto de assetManager
	textText = AssetManager::getPTR()->text;
	this->fontPath = fontPath;
	clipped = false;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect = new SDL_Rect();
	this->size = size;
	rect->w = width;
	rect->h = height;
}


Texture::~Texture()
{

}

/*Esta función ubicará a las imágenes donde se haya especificado*/
void Texture::Render()
{
	Vector2 pos = Position();	//Se guarda una variaple a la posición
	rect->x = (int)(pos.x - width * 0.5f);	//Se resta la posición de X con la mitad de la anchura de la imagen
	rect->y = (int)(pos.y - height * 0.5f);//Se resta la posición de Y con la mitad de la anchura de la imagen
	graphics->DrawTexture(texture, (clipped)? &clippedRect : NULL, rect);	//Se dibuja una textura con la posibilidad de que sea una texura animada
	//graphics->DrawTexture(text,  NULL, rect);
}
