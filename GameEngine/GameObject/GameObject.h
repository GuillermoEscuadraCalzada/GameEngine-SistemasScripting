#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"

class GameObject
{
public:
	enum SPACE { local = 0, world = 1 };
	GameObject(float x = 0, float y = 0);
	GameObject(Vector2 pos);
	~GameObject();

	void Position(Vector2 position);
	Vector2 Position(SPACE space = world);
	Vector2 GetPosition() {
		return Pos;
	};
	Vector2 addFloat(float x, float y)
	{
		Pos.x += x;
		Pos.y += y;
		return Pos;
	}
	void setPosition(Vector2 pos)
	{
		Pos = pos;
	}
	void setActive(bool active);
	bool returnActive();
	void Translate(Vector2 vec);


	void MoveObject();

	float length(Vector2 thisVec)
	{
		return sqrt(thisVec.x * thisVec.x + thisVec.y * thisVec.y);
	}
	void setAngle(Vector2 vector, float angle);

private:
	Vector2 Pos;
	bool active;

	virtual void Update();
	virtual void Render();
};




#endif // !GAMEOBJECT_H