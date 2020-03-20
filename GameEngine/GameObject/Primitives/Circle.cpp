#include "Circle.h"

/*Constructor de un círculo que recibe un radio, una posición en X y una en Y*/
Circle::Circle(int radius, int x, int y)
{
	this->radius = radius; //Radio es igual a radio
	centreX = x; //Centro en X es igual a X
	centreY = y; //Centro en Y es igual a y
	position.x = x;
	position.y = y;
	renderer = Graphics::returnPTR()->getRenderer();
}

Circle::~Circle()
{
}

inline void Circle::Render()
{
	SDL_SetRenderDrawColor(Graphics::returnPTR()->getRenderer(), 0x00, 0xff, 0xf0, 0xff);
	GenerateCircle();
}

/*Se genera un círculo*/
void Circle::GenerateCircle()
{
	try {	

		if (radius > 0) {
			const int diameter = radius * 2;
			int x = radius -1;
			int y = 0;
			int tX = 1, tY = 1;
			int error = tX - diameter;
			//Avanza mientras x sea mayor o igual a Y
			while (x >= y) {

		/*Se dibuan los puntos desde los centros del círculo*/
		SDL_RenderDrawPoint(renderer, position.x + x, position.y - y);
		SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
		SDL_RenderDrawPoint(renderer, position.x - x, position.y - y);
		SDL_RenderDrawPoint(renderer, position.x - x, position.y + y);
	
		SDL_RenderDrawPoint(renderer, position.x + y, position.y - x);
		SDL_RenderDrawPoint(renderer, position.x + y, position.y + x);
		SDL_RenderDrawPoint(renderer, position.x - y, position.y - x);
		SDL_RenderDrawPoint(renderer, position.x - y, position.y + x);


		if (error <= 0) {
			y++;
			error += tY;
			tY += 2;
		}

		if (error > 0) {
			x--;
			tX += 2;
			error += (tX - diameter);
		}
	}
		}
		else {
			throw(0);
		}
	}
	catch (int x) {
		cout << "El circulo debe tener un radio mayor a cero.\n";
	}
}
