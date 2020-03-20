#include "Timer.h"

Timer* Timer::ptr = nullptr;

/*Constructor de la clase Timer*/
Timer::Timer()
{
	Reset();	//Se resetean todos los valores 
	timeScale = 1.0f;

}

Timer::~Timer()
{
}

/*Apuntador de esta clase para saber si ya fue creada y no volverla a crear*/
Timer* Timer::getPTR()
{
	//Pregunta si el apuntador es nulo
	if(ptr == nullptr)
		ptr = new Timer();	//Crea el apuntador
	return ptr;	//Regresa el apuntador
}

/*Releas elimina el apuntador y lo hace nulo*/
void Timer::Release()
{
	delete ptr;
	ptr = nullptr;
}

/*Esta función reinicia todos los valores del timer*/
void Timer::Reset()
{
	startTicks = SDL_GetTicks();	//Agarra los ticks del programa y los almacena
	elapsedTime = 0;	//Elapsed time empieza en cero
	deltaTime = 0.0f;//Delta time empieza en cero

}

/*Esta función nos regresa el delta time cuando queramos
	@return deltaTime;*/
float Timer::DeltaTime()
{
	return deltaTime;	//Regresa el deltaTime
}

/*Seteamos el Time Scale
	@param[ timeScale ] el timeScale que queremos que se tenga*/
void Timer::TimeScale(float timeScale)
{
	this->timeScale = timeScale;
}

/*Nos regresa el timeScale
	@return nos regresa el TimeScale del juego*/
float Timer::TimeScale()
{
	return timeScale;
}

/*Actualiza constantemente el timer del juego*/
void Timer::Update()
{
	elapsedTime = SDL_GetTicks() - startTicks;	//ElapsedTime es el tiempo inicial del juego menos el tick inicial
	deltaTime = elapsedTime ;	//Delta time es elapsed time por .001 ya que elapsed time viene en milisegundos
}
