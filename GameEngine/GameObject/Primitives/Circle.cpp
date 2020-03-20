#include "Circle.h"

/*Constructor de un c�rculo que recibe un radio, una posici�n en X y una en Y*/
Circle::Circle(int radius, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	this->radius = radius; //Radio es igual a radio
	diameter = this->radius * 2;
	centreX = x; //Centro en X es igual a X
	centreY = y; //Centro en Y es igual a y
	position.x = x;
	position.y = y;
	rect = { centreX - radius, centreY - radius, diameter, diameter };
	this->r = r;
	this->g = g;
	this->b = b;
	a = 255;
	renderer = Graphics::returnPTR()->getRenderer();
	collider = rect;
}

Circle::Circle()
{

}

Circle::~Circle()
{
}

void Circle::Render()
{
	SDL_SetRenderDrawColor(Graphics::returnPTR()->getRenderer(), r, g, b, a);
	GenerateCircle();
}

void Circle::MoveObject()
{
	try {
		
	}
	catch (...) {

	}
}

void Circle::Update()
{
}

/*Se determinan los valores del c�rculo (radio, posici�nes en X y Y, adem�s de sus colores*/
void Circle::SetUpValues()
{
	try {
		renderer = Graphics::returnPTR()->getRenderer();
		String s = "Ingresa los valores que quires que tenga tu circunferencia.";
		s.PrintWString();
		int value;
		wcout << "Radio: ";
		cin >> value;	radius = value; //Ingresa el usuario el valor del radio y se guarda en los valores del c�rculo
		diameter = radius * 2;
		wcout << "Posici�n en X: ";
		cin >> value; centreX = position.x =value;//Ingresa el usuario el valor de la posici�n en X y se guarda en los valores del c�rculo
		wcout << "Posici�n en Y: ";
		cin >> value; centreY = position.y= value; //Ingresa el usuario el valor de la posici�n en Y y se guarda en los valores del c�rculo
		wcout << "Color R: ";
		cin >> value; r = value; //Determina el color R del c�rculo
		wcout << "Color G: ";
		cin >> value; g = value; //Determina el color G del c�rculo
		wcout << "Color B: ";
		cin >> value; b = value; //Determina el color B del c�rculo
		a = 255;
		position.x = centreX; position.y = centreY;
		rect = { centreX - radius, centreY - radius, diameter, diameter }; collider = rect;
	}
	catch (...) {

	}
}

/*Se genera un c�rculo*/
void Circle::GenerateCircle()
{
	try {	

		if (radius > 0) {
			
			int x = radius -1;
			int y = 0;
			int tX = 1, tY = 1;
			int error = tX - diameter;
			//Avanza mientras x sea mayor o igual a Y
			while (x >= y) {

		/*Se dibuan los puntos desde los centros del c�rculo*/
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
