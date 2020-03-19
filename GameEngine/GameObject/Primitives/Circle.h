#ifndef CIRCLE_H
#define CRICLE_H
#include "Primitives.h"
class Circle : public Primitives
{
public:
	Circle(int radius, int x, int y);
	~Circle ();
	void Render() override;
	SDL_Renderer* renderer;
private:
	int radius, centreX, centreY;
	void GenerateCircle();
};



#endif // !CIRCLE_H
