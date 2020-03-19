#include "Square.h"
Square::Square(int x, int y, int width, int height)
{
	try {
		surface = Graphics::returnPTR()->GetSurface();
		position.x = x;
		position.y = y;

		this->width = width;
		this->height = height;
		rect = { (int)position.x - this->width/2, (int)position.y - height/2, this->width, this->height };
	}
	catch (...) {

	}
}

Square::~Square()
{
}

void Square::Render()
{

	SDL_SetRenderDrawColor(Graphics::returnPTR()->getRenderer(), 0xff, 0x00, 0xff, 0xff);
	SDL_RenderFillRect(Graphics::returnPTR()->getRenderer(), &rect);

	//SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
}
