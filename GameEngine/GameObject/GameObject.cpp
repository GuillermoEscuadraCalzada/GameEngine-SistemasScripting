#include "GameObject.h"
#include <algorithm>
Vector2 pos2;
bool change = true;
int counter = 0;
float wanderAngle = 0.0f;

/*Este constructo de game object, setea la posici�n del objeto en el lugar indicado
	@param[ x ] posici�n en x dentro de la pantalla
	@param[ y ] posici�n en y dentro de la pantalla*/
GameObject::GameObject(float x, float y)
{
	Pos.x = x;	//El vector Pos recibe en su vector x el float x
	Pos.y = y;	//El vecto Pos recibe en su vector y el float y
	
	active = true;	//Se vuelve verdadero
}

GameObject::GameObject(Vector2 pos)
{
	Pos = pos;
	pos2 = Pos;
}

/*Destructro de la clase GameObject*/
GameObject::~GameObject()
{
}

/*El vector position se iguala al vector del argumento
	@param[ position ] Este argumento ser� la posi�n del objeto*/
void GameObject::Position(Vector2 position)
{
	Pos = position;
}


Vector2 GameObject::Position(SPACE space)
{
	return Pos;
}

/*Cuando deje de estar activo, la terminar� y se detendr� en el �ltimo sprite
	@param[active] el active de la clase cambia dependiendo al par�metro*/
void GameObject::setActive(bool active)
{
	this->active = active;
}

/*Regresa si active es verdadero o falsoe
	@return verdadero o falso*/
bool GameObject::returnActive()
{
	return active;
}

/*Translate cambia la posicion de acuerdo al vector dentro del par�metro
	@param[Vector 2 vec] vector que modificar� la posici�n del objeto*/
void GameObject::Translate(Vector2 vec)
{
	Pos += vec;
}

/*Esta funci�n mover� a un personaje de un lado a otro, izquierda a derecha*/
void GameObject::MoveObject()
{
	try
	{
		if(change)
		{ //Con este booleano preguntar� hacia qu� lado se dirigir� la imagen. 
			if(this->Pos.x > 500)
			{//Si la posici�n excede los 500 pixeles
				change = !change; //El booleano se vuelve falso 
				counter++; //aumenta el entero
			}
			else
			{//Si no es mayor a 500
				this->Pos.x += 1 * 5; //Aumenta hacia la derecha 
			}
		}
		else if(!change)
		{//Si el booleano es negativo
			if(this->Pos.x < 300)
			{//Pregunta si la posici�n de este objeto es menor a 300 pixeles
				change = true; //Cambia el booleano 
				counter++; //incrementa el entero
			}
			else
				this->Pos.x += -1 * 5; //A�ade a la posici�n del jugador en X la velocidad actual de manera negativa
		}
		if(counter > 1)
			throw(counter); //Si el contador es mayor a 1, avienta un error
		else
			counter = 0; //Si no es mayor a uno
	} catch(int x)
	{
		std::cout << "The loop repeated more than once, something is wrong.\n";
	}
	catch(std::exception & e)
	{
		std::cout << "EXCEPTION CAUGHT: " << e.what() << "\n";
	}
}

void GameObject::Update()
{
	
}

void GameObject::Render()
{
}
