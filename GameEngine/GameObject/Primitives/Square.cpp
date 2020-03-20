#include "Square.h"

/*Crea un cuadrado por medio de lua
 *@param[lua_State* lua] el stado de lua con el que se maneja el programa
 *@return regresa el n�mero de objetos que sea crean*/
int lua_CreateSquare(lua_State* lua) {
	try {
		Square* square = (Square*)lua_newuserdata(lua, sizeof(Square*)); //Crea un nuevo cuadrado 
		square->surface = Graphics::returnPTR()->GetSurface(); //Ingresa la superficie del cuadrante
		lua_Number vecX = lua_tonumber(lua, -6);//Recupera este valor de lua
		lua_Number vecY = lua_tonumber(lua, -5);//Recupera este valor de lua
		square->setPosition(Vector2(vecX, vecY)); //Actualiza la posici�n del cuadrado
		square->position = square->GetPosition();
		
		lua_Number width = lua_tonumber(lua, -4); //Recupera este valor de lua

		lua_Number height = lua_tonumber(lua, -3); //Recupera este valor de lua
		if (width <= 0) {
			throw(width);
		}
		else if (height <= 0) {
			throw(height);
		}
		square->width = width; /// el ancho del cuadrado es igual al ancho de la variable de lua
		square->height = height;/// la altura del cuadrado es igual a la altura de la variable de lua
		square->rect = { (int)square->position.x - square->width / 2, (int)square->position.y - square->height / 2,square->width, square->height };
		square->input = InputManager::getPtr();
		square->graphics = Graphics::returnPTR();
		square->collider = square->rect;
		return 1;
	}
	catch (int x) {
		String s = "This input: " + to_string(x) + " needs to be greater than 0";
		s.PrintWString();
	}
}

/*Constructor de la clase cuadrado
 *@param[int x] posici�n en X dentro de la pantalla
 *@param[int y] posici�n en Y dentro de la pantalla
 *@param[int width] ancho del cuadrado
 *@param[int height] altura del cuadrado*/
Square::Square(int x, int y, int width, int height)
{
	try {
		input = InputManager::getPtr();
		graphics = Graphics::returnPTR();
		surface = Graphics::returnPTR()->GetSurface();
		position.x = x;
		position.y = y;

		this->width = width;
		this->height = height;
		rect = { (int)position.x - this->width/2, (int)position.y - height/2, this->width, this->height };
		collider = rect;
	}
	catch (...) {

	}
}

/*Constructor por defecto de la clase Square*/
Square::Square()
{
	input = InputManager::getPtr();
	timer = Timer::getPTR();
	graphics = Graphics::returnPTR();
}

/*Destructor de la clase Square*/
Square::~Square()
{

}

/*Se renderiza el cuadrado*/
void Square::Render()
{
	if (&rect) {
		SDL_SetRenderDrawColor(Graphics::returnPTR()->getRenderer(), r, g, b,a);
		SDL_RenderFillRect(Graphics::returnPTR()->getRenderer(), &rect);
	}
}

/*Update del cuadrado*/
void Square::Update()
{
	if (input->keyPressed(SDL_SCANCODE_SPACE)) {
		jumping = true;
	}
	Jump();
	MoveObject();
}

/*El objeto puede moverse de derecha a izquierda, arriba a abajo*/
void Square::MoveObject()
{
	try {
		width = rect.w;
		height = rect.h;
		if (input->keyDown(SDL_SCANCODE_D)) {
			position.x += 10;
			if (position.x > graphics->SCREEN_WIDTH) //Pregunta si el cuadrado se sale del lado derecho de la pantalla
				position.x = 0;
			rect.x = position.x; //Actualiza la posici�n del rect del cuadrado en el eje X
		}
		else if (input->keyDown(SDL_SCANCODE_A)) {
			position.x -= 10;
			if (position.x + width < 0)//Pregunta si el cuadrado se sale del lado izquierdo de la pantalla
				position.x = graphics->SCREEN_WIDTH;
			rect.x = position.x;//Actualiza la posici�n del rect del cuadrado en el eje X
		}
		else if (input->keyDown(SDL_SCANCODE_W) && jumping == false) {
			position.y -= 10;
			if (position.y  < 0)//Pregunta si el cuadrado se sale del de arriba de la pantalla
				position.y = graphics->SCREEN_HEIGHT;
			rect.y = position.y;//Actualiza la posici�n del rect del cuadrado en el eje Y

		}
		else if (input->keyDown(SDL_SCANCODE_S) && jumping == false) {
			position.y += 10;
			if (position.y > graphics->SCREEN_HEIGHT)//Pregunta si el cuadrado se sale del lado de abajo de la pantalla
				position.y = 0;
			rect.y = position.y;//Actualiza la posici�n del rect del cuadrado en el eje Y
		}
	}
	catch (...) {

	}
}

bool Square::OnCollisionDetection(SDL_Rect rect)
{
	try {

		return false;
	}
	catch (...) {
	}
}

/*El sprite salta*/
void Square::Jump()
{
	try {
		
		/*Si jump es verdadero, la posici�n del jugador subir� hasta el salto m�ximo*/
		if (jumping) {
			if (position.y <= maxHeight) { //Si el salto es igual a la altura m�xima, cambiar jump a false
				jumping = false;
			}
			position.y -= 10; //Reduce -10 a la posici�n del jugador
			rect.y = position.y;
		}
		if(!jumping){ //Si jump es negativo, pregunta si la posici�n es menor a la posici�n original
			if (position.y < maxHeight + 50) {
				position.y += 10; //Aumenta 10 a la y del jugador
				rect.y = position.y;
			}
		}
	}
	catch (...) {

	}
}


/*Crea un objeto por medio de Lua, abriendo el texto especificado en el argumento
 *@param[string fileName] el nombre del archivo que se abrir� para lua*/
void Square::lua_CreateObject(string fileName)
{
	try {

		/*Checa si existe el archivo de lua con el nombre especificado*/
		if (lua->CheckLua(lua->GetState(), luaL_dofile(lua->GetState(), fileName.c_str()))) {
			lua_register(lua->GetState(), "CreateSquare", lua_CreateSquare);
			lua_getglobal(lua->GetState(), "CreateLuaSquare"); //Conseguir la funci�n global de lua
			if (lua_isfunction(lua->GetState(), -1)) {
				wcout << "Ingrese valores para la creaci�n de su cuadro.\n";
				int numb = 400; 
				wcout << "Pos X: ";
				cin >> numb;
				if (cin.fail()) //Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb);//Ingresa el valor a lua
				cout << "Pos Y: ";
				cin >> numb;
				if (cin.fail())//Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb); //Ingresa el valor a lua
				cout << "Width: ";
				numb = 100;
				cin >> numb;

				if (cin.fail())//Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb); //Ingresa el valor a lua
				cout << "Height: ";
				cin >> numb;
				if (cin.fail())//Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb);//Ingresa el valor a lua
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
	catch (int x) {
		cout << "This is a bad input, you need to write a number\n";
	}
	catch (exception & e) {

	}
	catch (...) {

	}
}

/*Se setean todos los valores del cuadrado por medio de un getline, esto significa posici�n, tama�o, color, etc.*/
void Square::SetUpValues()
{
	try {
		String s = "Ingrese valores para la creaci�n de su cuadro.\n";
		s.PrintWString();
		int x = 0;
		wcout << "Pos X: ";
		cin >> x;
		if (cin.fail()) //Si el usuario implementa una letra manda error
			throw(x);
		int y = 0;
		wcout << "Pos Y: ";
		cin >> y;
		if (cin.fail())//Si el usuario implementa una letra manda error
			throw(y);
		
		wcout << "Width: ";
		int width = 0;
		width = 100;
		cin >> width;
		if (cin.fail())//Si el usuario implementa una letra manda error
			throw(width);
		wcout << "Height: ";
		int height = 0;
		cin >> height;
		if (cin.fail())//Si el usuario implementa una letra manda error
			throw(height);
		rect.w = width; rect.h = height; //Se actualizan las dimensiones del cuadrado
		position.x = rect.x= x - width/2; position.y = rect.y = y - height/2; //Se actualizan las posiciones en del cuadrado 
		maxHeight = position.y - 50;
		s =  "Escribe los colores de tu cuadrado en numeros. Solo se pueden de 1 a 3 digitos. (Numero maximo 255, minimo 0)\n";
		s.PrintWString();
		wstring s2;
		cin.ignore();
		getline(wcin, s2); //Obt�n el string y cuardalo dentro de una variable
		r = stoi(s2);
		getline(wcin, s2);
		g = stoi(s2);
		getline(wcin, s2);
		b = stoi(s2);		
		if (r < 0 || r >255 || g < 0 || g >255 || b < 0 || b >255)
			throw - 1;
		s = "Color: " + to_string((int)r) + ", " + to_string((int)g )+ ", " + to_string((int)b) + ", " + to_string((int)a);
		s.PrintWString();
		collider = rect;
	}
	catch (int x) {
		wcout << "There was an error in your code!\n";
	}
}
