#include "StartScreen.h"

/*Constructor de la clase Start Screen*/
StartScreen::StartScreen()
{
	//Top bar
	TopText = new GameObject(Vector2(Graphics::returnPTR()->SCREEN_WIDTH / 2 , 80.0f));	//Se crea un gameObject que nos permite tomar de referencia para posicionar nuestras texturas
	CenterPoint = new GameObject(Vector2(Graphics::returnPTR()->SCREEN_WIDTH / 2, Graphics::returnPTR()->SCREEN_HEIGHT / 2));	//Center Point Toma la parte central de la pantalla
	input = InputManager::getPtr();	//Se crea un apuntador 
	
}

/*Destructor de la clase StartScreen*/
StartScreen::~StartScreen()
{
	delete TopText;	//Se elimina el objeto TopText
	TopText = nullptr;	//Se hace nulo
	
	delete backGround;	//Se elimina el objeto de backGround
	backGround = nullptr;	//Se hace nulo

	delete titleText;	//Se elimina titleText
	titleText = nullptr;	//Se hace nulo

	delete startText;	//Se elimina startText
	startText = nullptr;	//Se hace nulo

	delete QuitText;	//Se elimina QuitText
	QuitText = nullptr;	//Se hace nulo

}

/*Update de la clase StartScreen, la cual se encargará de modificar los textos que se encuentren dentro de la pantall*/
void StartScreen::Update()
{
	input->Update();	//Inicia la función Update de los input
	mousePos = input->MousePosition();
	SDL_Rect** rectArr = new SDL_Rect * [screenVec.size];
	printf("MousePosition\nX: %f\nY: %f\n", input->MousePosition().x, input->MousePosition().y);
	for(int i = 0; i < screenVec.size; i++)
	{
		rectArr[i] = screenVec.return_at(i);
	}
	for(int i = 0; i < screenVec.size; i++)
	{
		if(mousePos.x >= rectArr[i]->x && mousePos.x <= rectArr[i]->x + rectArr[i]->w
		   && mousePos.y >= rectArr[i]->y && mousePos.y <= rectArr[i]->y + rectArr[i]->h)
		{
			if(input->MouseButtonPressed(InputManager::left) && i == 1)
			{
				startGame = true;
			}
		}
	}
	input->UpdatePrevInput();

}

/*Se renderizan todos nodos del vector d ela ventana*/
void StartScreen::Render()
{
	backGround->Render();
	Node<Texture*>* it = screenVec.first;	//Se crea un iterador que recorrerá toda la lista de la clase
	while(it != nullptr)
	{
		(*screenVec.return_at(it->path))->Render();	//Se renderiza cada elemento de la lista
		it = it->next;
	}

}

/*Esta función sólo carga los sprites, los englobé aquí para que no se llenara otra función*/
void StartScreen::MainMenu()
{
	Vector2 position = TopText->GetPosition();		//Se guardan dos variables para facilitar la carga de esta información
	Vector2 position2 = CenterPoint->GetPosition();	//Se guardan dos variables para facilitar la carga de esta información

#pragma region título y fondo
	titleText = new Texture("Match 4: Food Edition", "arialbd.ttf", 20, { 200,0,0 });	//Se crea un texto con el título del juego
	backGround = new Texture("Fondo_800x800.png", 0, 0, 800, 800);	//Se carga la imagen del fondo
	backGround->Position(Vector2(400, 400));	//Se setea la posicón de la imagen al centro de la pantalla
#pragma endregion
	//PlayModes

	titleText->Position(Vector2(position.x, position.y));	//El título se centra en el centro de TopText

#pragma region Textos centrales
	startText = new Texture("Start", "arialbd.ttf", 20, { 200,0,0 });		//Carga del texto "Start"
	hSText = new Texture("HighScore", "arialbd.ttf", 20, { 200,0,0 });	//Carga del texto "HighScore"
	QuitText = new Texture("Quit", "arialbd.ttf", 20, { 200,0,0 });		//Carga del texto "Quit"
#pragma endregion
	
	//Se determinan las posiciones de los textos
	startText->Position(Vector2(position2.x, position2.y));	
	hSText->Position(Vector2(position2.x, position2.y * 1.25f));
	QuitText->Position(Vector2(position2.x, position2.y * 1.5f));

	//Se hace push back de cada imagen al vector ScreenVec
	
	screenVec.push_back(titleText);
	screenVec.push_back(startText);
	screenVec.push_back(hSText);
	screenVec.push_back(QuitText);


	


}

void StartScreen::GameScreen()
{

}
