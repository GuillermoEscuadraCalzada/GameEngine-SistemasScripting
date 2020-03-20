#ifndef CIRCLE_H
#define CRICLE_H
#include "Primitives.h"
class Circle : public Primitives
{
public:
	Circle(int radius, int x, int y, Uint8 r, Uint8 g, Uint8 b);
	Circle();
	~Circle ();
	void Render() override;
	void Update() override;
	void MoveObject() override;
	SDL_Renderer* renderer;
	SDL_Rect rect;
	void SetUpValues();
private:
	int radius, centreX, centreY;
	int diameter;
	void GenerateCircle();
};



#endif // !CIRCLE_H
