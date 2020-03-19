#ifndef SQUARE_H
#define SQUARE_H
#include "Primitives.h"
class Square : public Primitives
{
public:
	int width, height;
	Square(int x, int y, int width, int height);
	~Square();
	SDL_Rect rect;
	SDL_Surface* surface;
	void Render() override;
private:

};


#endif // !SQUARE_H
