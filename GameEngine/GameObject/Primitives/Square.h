#ifndef SQUARE_H
#define SQUARE_H
#include "Primitives.h"
#include <wincrypt.h>
class Square : public Primitives
{
public:
	int width, height;
	Square(int x, int y, int width, int height);
	Square();
	~Square();
	SDL_Rect rect;
	SDL_Surface* surface;
	void Render() override;
	void lua_CreateObject(string fileName);

	void Update();
};


#endif // !SQUARE_H
