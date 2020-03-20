#include "Square.h"
int lua_CreateSquare(lua_State* lua) {
	Square* square = (Square*)lua_newuserdata(lua, sizeof(Square*)); //Crea un nuevo cuadrado 
	square->surface = Graphics::returnPTR()->GetSurface();
	lua_Number vecX = lua_tonumber(lua, -6);
	lua_Number vecY = lua_tonumber(lua, -6);
	square->setPosition(Vector2(vecX, vecY));
	square->position = square->GetPosition();
	lua_Number width = lua_tonumber(lua, -4);

	lua_Number height = lua_tonumber(lua, -3);

	square->width = width;
	square->height = height;
	square->rect = { (int)square->position.x - square->width / 2, (int)square->position.y - square->height / 2,square->width, square->height };

	return 1;
}
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

Square::Square()
{

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

void Square::Update()
{
}

/*Crea un objeto por medio de Lua, abriendo el texto*/
void Square::lua_CreateObject(string fileName)
{
	try {

		if (lua->CheckLua(lua->GetState(), luaL_dofile(lua->GetState(), fileName.c_str()))) {
			//Crea una función dentro de esta función y lo vuelve de tipo entero
			//auto lua_CreateSquare = [](lua_State* lua) -> int {

			//	
			//};

			lua_register(lua->GetState(), "CreateSquare", lua_CreateSquare);
			lua_getglobal(lua->GetState(), "CreateLuaSquare");

			if (lua_isfunction(lua->GetState(), -1)) {
				cout << "Ingrese valores para la creación de su cuadro.\n";
				int numb = 400; 
				cout << "Pos X: ";
				//cin >> numb;
				lua_pushnumber(lua->GetState(), numb);
				cout << "Pos Y: ";
				//cin >> numb;
				lua_pushnumber(lua->GetState(), numb);
				cout << "Width: ";
				numb = 100;
				//cin >> numb;
				lua_pushnumber(lua->GetState(), numb);
				cout << "Height: ";
				//cin >> numb;
				lua_pushnumber(lua->GetState(), numb);
				if (lua->CheckLua(lua->GetState(), lua_pcall(lua->GetState(), 4, 1, 0))) {

					lua_getglobal(lua->GetState(), "square");
					
					Square* square = (Square*)lua_touserdata(lua->GetState(), -1);
					surface = square->surface;
					this->position = square->position;
					this->width = square->width; this->height = square->height;
					this->rect = square->rect;
					cout << "Lua created a square\n";
				}
			}
		}
	}
	catch (exception & e) {

	}
	catch (...) {

	}
}
