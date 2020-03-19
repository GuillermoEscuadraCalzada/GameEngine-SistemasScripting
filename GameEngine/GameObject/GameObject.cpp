#include "GameObject.h"
#include <algorithm>
Vector2 pos2;
bool change = true;
int counter = 0;
float wanderAngle = 0.0f;

/*Este constructo de game object, setea la posición del objeto en el lugar indicado
	@param[ x ] posición en x dentro de la pantalla
	@param[ y ] posición en y dentro de la pantalla*/
GameObject::GameObject(float x, float y)
{
	Pos.x = x;	//El vector Pos recibe en su vector x el float x
	Pos.y = y;	//El vecto Pos recibe en su vector y el float y
}

GameObject::GameObject(Vector2 pos)
{
	Pos = pos;
}

/*Destructro de la clase GameObject*/
GameObject::~GameObject()
{
}

/*El vector position se iguala al vector del argumento
	@param[ position ] Este argumento será la posión del objeto*/
void GameObject::Position(Vector2 position)
{
	Pos = position;
}


Vector2 GameObject::Position(SPACE space)
{
	return Pos;
}

Vector2 GameObject::GetPosition()
{
	return Pos;
}

Vector2 GameObject::addFloat(float x, float y)
{
	Pos.x += x;
	Pos.y += y;
	return Pos;
}

void GameObject::setPosition(Vector2 pos)
{
	Pos = pos;
}


/*Translate cambia la posicion de acuerdo al vector dentro del parámetro
	@param[Vector 2 vec] vector que modificará la posición del objeto*/
void GameObject::Translate(Vector2 vec)
{
	Pos += vec;
}

float GameObject::length(Vector2 thisVec)
{
	return sqrt(thisVec.x * thisVec.x + thisVec.y * thisVec.y);
}

void GameObject::Update()
{
	
}

void GameObject::Render()
{
}
