#ifndef SQUARE_H
#define SQUARE_H
#include "Primitives.h"
#include <wincrypt.h>
using namespace std;
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
	void Update() override;
	void MoveObject()override;
	bool OnCollisionDetection(SDL_Rect rect) override;

	void lua_CreateObject(string fileName);
	void SetUpValues();
	void Jump() override;
	int maxHeight;
	bool jumping = false;
};


#endif // !SQUARE_H
