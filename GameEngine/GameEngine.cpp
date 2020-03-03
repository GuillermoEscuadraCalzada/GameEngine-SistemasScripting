// GameEngine.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "GameManager/GameManager/GameManager.h"
int main(int argc, char* args[])
{
	GameManager* game = GameManager::GetPtr();
	game->MainUpdate();
	GameManager::Close();
	game = nullptr;
	return 0;
}