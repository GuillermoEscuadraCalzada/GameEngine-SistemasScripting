#include "Square.h"

/*Crea un cuadrado por medio de lua
 *@param[lua_State* lua] el stado de lua con el que se maneja el programa
 *@return regresa el número de objetos que sea crean*/
int lua_CreateSquare(lua_State* lua) {
	try {
		Square* square = (Square*)lua_newuserdata(lua, sizeof(Square*)); //Crea un nuevo cuadrado 
		square->surface = Graphics::returnPTR()->GetSurface(); //Ingresa la superficie del cuadrante
		lua_Number vecX = lua_tonumber(lua, -6);//Recupera este valor de lua
		lua_Number vecY = lua_tonumber(lua, -5);//Recupera este valor de lua
		square->setPosition(Vector2(vecX, vecY)); //Actualiza la posición del cuadrado
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
 *@param[int x] posición en X dentro de la pantalla
 *@param[int y] posición en Y dentro de la pantalla
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
	handler = GetStdHandle(STD_OUTPUT_HANDLE);
	console = Console::GetPTR();
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
	if (input->MousePosition().x > rect.x && input->MousePosition().x < rect.x + rect.w &&
		input->MousePosition().y > rect.y && input->MousePosition().y < rect.y + rect.h 
		) {
		if (input->MouseButtonDown(InputManager::left) && setActive == false) {
			setActive = true;
			wcout <<L"X: " << input->MousePosition().x << L"X: " << input->MousePosition().y << endl;
		}
	}
	//Si el objeto está activado, se puede mover, si no lo está no puede moverse
	if (setActive == true) {
		MoveObject();
	}
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
			rect.x = position.x; //Actualiza la posición del rect del cuadrado en el eje X
		}
		else if (input->keyDown(SDL_SCANCODE_A)) {
			position.x -= 10;
			if (position.x + width < 0)//Pregunta si el cuadrado se sale del lado izquierdo de la pantalla
				position.x = graphics->SCREEN_WIDTH;
			rect.x = position.x;//Actualiza la posición del rect del cuadrado en el eje X
		}
		else if (input->keyDown(SDL_SCANCODE_W) && jumping == false) {
			position.y -= 10;
			if (position.y  < 0)//Pregunta si el cuadrado se sale del de arriba de la pantalla
				position.y = graphics->SCREEN_HEIGHT;
			rect.y = position.y;//Actualiza la posición del rect del cuadrado en el eje Y

		}
		else if (input->keyDown(SDL_SCANCODE_S) && jumping == false) {
			position.y += 10;
			if (position.y > graphics->SCREEN_HEIGHT)//Pregunta si el cuadrado se sale del lado de abajo de la pantalla
				position.y = 0;
			rect.y = position.y;//Actualiza la posición del rect del cuadrado en el eje Y
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


/*Crea un objeto por medio de Lua, abriendo el texto especificado en el argumento
 *@param[string fileName] el nombre del archivo que se abrirá para lua*/
void Square::lua_CreateObject(string fileName)
{
	try {

		/*Checa si existe el archivo de lua con el nombre especificado*/
		if (lua->CheckLua(lua->GetState(), luaL_dofile(lua->GetState(), fileName.c_str()))) {
			lua_register(lua->GetState(), "CreateSquare", lua_CreateSquare);
			lua_getglobal(lua->GetState(), "CreateLuaSquare"); //Conseguir la función global de lua
			if (lua_isfunction(lua->GetState(), -1)) {
				wcout << "Ingrese valores para la creación de su cuadro.\n";
				int numb = 400; 
				wcout << "Pos X: ";
				cin >> numb;
				if (cin.fail()) //Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb);//Ingresa el valor a lua
				wcout << "Pos Y: ";
				cin >> numb;
				if (cin.fail())//Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb); //Ingresa el valor a lua
				wcout << "Width: ";
				numb = 100;
				cin >> numb;

				if (cin.fail())//Si el usuario implementa una letra manda error
					throw(numb);
				lua_pushnumber(lua->GetState(), numb); //Ingresa el valor a lua
				wcout << "Height: ";
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
					wcout << "Lua created a square\n";
				}
			}
		}
	}
	catch (int x) {
		String s = "This is a bad input, you need to write a number\n";
		s.PrintWString();
		console->finalMSG += s.GetWString();
	}
	catch (exception & e) {
		String s;
		SetConsoleTextAttribute(handler, 4);
		if (console->languages == 0) {
			s = "HUBO UNA EXEPCIÓN";
			s.PrintWString();
		}
		else if (console->languages == 1) {
			 s = "THERE WAS AN EXCEPTION";
			s.PrintWString();
		}
		console->finalMSG += s.GetWString();
	}
	catch (...) {

	}
}

/*Se setean todos los valores del cuadrado por medio de un getline, esto significa posición, tamaño, color, etc.*/
void Square::SetUpValues()
{
	try {
		SetConsoleTextAttribute(handler, 5);
		String s = "Ingrese valores para la creación de su cuadro.\n";
		s.PrintWString();
		int x = 0;
		SetConsoleTextAttribute(handler, 7);
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
		position.x = rect.x= x - width/2; position.y = rect.y = y - height/2; //Se actualizan las posiciones en del cuadrado }
		SetConsoleTextAttribute(handler, 2);
		s =  "Escribe los colores de tu cuadrado en numeros. Solo se pueden de 1 a 3 digitos. (Numero maximo 255, minimo 0)\n";
		s.PrintWString();
		wstring s2;
		cin.ignore();
		getline(wcin, s2); //Obtén el string y cuardalo dentro de una variable
		r = stoi(s2);
		getline(wcin, s2);
		g = stoi(s2);
		getline(wcin, s2);
		b = stoi(s2);		
		if (r < 0 || r >255 || g < 0 || g >255 || b < 0 || b >255)
			throw - 1;
		SetConsoleTextAttribute(handler, 1);
		s = "Color: " + to_string((int)r) + ", " + to_string((int)g )+ ", " + to_string((int)b) + ", " + to_string((int)a);
		s.PrintWString();
		collider = rect;
	}
	catch (int x) {
		SetConsoleTextAttribute(handler, 4);
		if (console->languages == 0) {
			String s = "Hubo un error en tu código! Mal elemento para tu caudrado";
			s.PrintWString();
		}
		else if (console->languages == 1) {
			String s = "There was an error in your code! Wrong element for your square";
			s.PrintWString();
		}
	}
}
