#ifndef PRIMITIVES_H
#define PRIMITIVES_H
#include "../GameObject.h"
#include "SDL.h"

class Primitives : public GameObject
{
public:
	Primitives();
	~Primitives();
	Vector2 position;
	SDL_Rect collider;
	virtual void Render();
	virtual void Update();
	virtual void MoveObject();
	virtual void Jump();
	Uint8 r, g, b, a; //Colores RGB del 
	virtual bool OnCollisionDetection(SDL_Rect rect);
};


#endif //!PRIMITIVES_H