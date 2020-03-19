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
	virtual void Render();
};


#endif //!PRIMITIVES_H