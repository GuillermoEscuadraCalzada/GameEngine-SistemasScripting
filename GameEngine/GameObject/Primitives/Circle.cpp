#include "Circle.h"

/*Constructor de un círculo que recibe un radio, una posición en X y una en Y*/
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
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	input = InputManager::getPtr();
	timer = Timer::getPTR();
	graphics = Graphics::returnPTR();
}

Circle::~Circle()
{

}

void Circle::Render()
{
	SDL_SetRenderDrawColor(Graphics::returnPTR()->getRenderer(), r, g, b, a);
	GenerateCircle();
}

/*El círculo pued moverse*/
void Circle::MoveObject()
{
	try {
		width = rect.w;
		height = rect.h;
		if (input->keyDown(SDL_SCANCODE_D)) {
			position.x += 10;
			if (position.x > graphics->SCREEN_WIDTH) //Pregunta si el cuadrado se sale del lado derecho de la pantalla
				position.x = 0;
			rect.x = position.x; //Actualiza la posición del rect del cuadrado en el eje X
		}
		else if (input->keyDown(SDL_SCANCODE_A)) {
			position.x -= 10;
			if (position.x + width < 0)//Pregunta si el cuadrado se sale del lado izquierdo de la pantalla
				position.x = graphics->SCREEN_WIDTH;
			rect.x = position.x;//Actualiza la posición del rect del cuadrado en el eje X
		}
		else if (input->keyDown(SDL_SCANCODE_W)) {
			position.y -= 10;
			if (position.y < 0)//Pregunta si el cuadrado se sale del de arriba de la pantalla
				position.y = graphics->SCREEN_HEIGHT;
			rect.y = position.y;//Actualiza la posición del rect del cuadrado en el eje Y

		}
		else if (input->keyDown(SDL_SCANCODE_S)) {
			position.y += 10;
			if (position.y > graphics->SCREEN_HEIGHT)//Pregunta si el cuadrado se sale del lado de abajo de la pantalla
				position.y = 0;
			rect.y = position.y;//Actualiza la posición del rect del cuadrado en el eje Y
		}
	}
	catch (...) {

	}
}

void Circle::Update()
{
	try {
		if (input->MousePosition().x > rect.x&& input->MousePosition().x < rect.x + rect.w &&
			input->MousePosition().y > rect.y&& input->MousePosition().y < rect.y + rect.h
			) {
			if (input->MouseButtonDown(InputManager::left) && setActive == false) {
				setActive = true;
				wcout << L"X: " << input->MousePosition().x << L"X: " << input->MousePosition().y << endl;
			}
		}
		if (setActive == true) {
			MoveObject();
		}
	}
	catch (...) {

	}
}

/*Se determinan los valores del círculo (radio, posiciónes en X y Y, además de sus colores*/
void Circle::SetUpValues()
{
	try {
		renderer = Graphics::returnPTR()->getRenderer();
		SetConsoleTextAttribute(hConsole, 2);
		String s = "Ingresa los valores que quires que tenga tu circunferencia.";
		s.PrintWString();
		int value;
		SetConsoleTextAttribute(hConsole, 6);
		wcout << "Radio: ";
		cin >> value;	radius = value; //Ingresa el usuario el valor del radio y se guarda en los valores del círculo
		diameter = radius * 2;
		wcout << "Posición en X: ";
		cin >> value; centreX = position.x =value;//Ingresa el usuario el valor de la posición en X y se guarda en los valores del círculo
		wcout << "Posición en Y: ";
		cin >> value; centreY = position.y= value; //Ingresa el usuario el valor de la posición en Y y se guarda en los valores del círculo
		wcout << "Color R: ";
		cin >> value; r = value; //Determina el color R del círculo
		wcout << "Color G: ";
		cin >> value; g = value; //Determina el color G del círculo
		wcout << "Color B: ";
		cin >> value; b = value; //Determina el color B del círculo
		a = 255;
		if (r < 0 || r >255 || g < 0 || g >255 || b < 0 || b >255)
			throw - 1;
		position.x = centreX; position.y = centreY;
		rect = { centreX - radius, centreY - radius, diameter, diameter }; collider = rect;
	}
	catch (int x) {
		SetConsoleTextAttribute(hConsole, 6);
		String s;
		if (console->languages == 0) {
		s = "Hubo un error en el código! Palabra ingresada en vez de número";
		s.PrintWString();

		}
		else if (console->languages == 1) {
			s = "There was an error with your code! You used a word instead of a number";
			s.PrintWString();
		}
		console->finalMSG += s.GetWString();
	}
	catch (...) {

	}
}

/*Se genera un círculo*/
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
		SetConsoleTextAttribute(hConsole, 6);
		String s;
		if (console->languages == 0) {
			s = "El círculo debe tener un radio mayor a cero.\n";
			s.PrintWString();

		}
		else if (console->languages == 1) {
			s = "Circle must hava radius bigger than zero";
			s.PrintWString();
		}
		console->finalMSG += s.GetWString();
	}
}
