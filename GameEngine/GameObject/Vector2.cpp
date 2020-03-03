#include "Vector2.h"

/**/
Vector2 Vector2::normalizeVector
(Vector2 target, Vector2 objectVector)
{
	try
	{
		Vector2* distance = new Vector2(target.x - objectVector.x, target.y - objectVector.y); //Se consigue la distancia entre los dos vectores por medio de una resta entre el objetivo final y el seeker
		float magnitude = sqrt(pow(distance->x, 2) + pow(distance->y, 2));//se consigue la magnitud del vector elevando al cuadrado las entradas y sacando raíz cuadrada de las sumas 
		Vector2* normalized = new Vector2(distance->x / magnitude, distance->y / magnitude); //Se normaliza el vector para que sea unitario y así poder convertirse en cualquier otro vector

		return *normalized;

	} catch(std::exception & e)
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	}

}


