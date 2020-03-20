#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"
#include "../Graphics/Graphics/Graphics.h"
#include <string>
#include <iostream>
class GameObject
{
public:
	enum SPACE { local = 0, world = 1 };
	GameObject(float x = 0, float y = 0);
	GameObject(Vector2 pos);
	~GameObject();
	 
	void Position(Vector2 position);
	
	Vector2 Position(SPACE space = world);
	Vector2 GetPosition();
	Vector2 addFloat(float x, float y);
	
	void setPosition(Vector2 pos);
	void Translate(Vector2 vec);

	float length(Vector2 thisVec);
	Lua* lua = Lua::GetPTR();

private:
	Vector2 Pos;
	virtual void Update();
	virtual void Render();
};




#endif // !GAMEOBJECT_H