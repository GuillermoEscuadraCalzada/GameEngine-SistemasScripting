#ifndef VECTOR2_H
#define VECTOR2_H
#include <math.h>
#include <iostream>

struct Vector2
{
	float x;
	float y;

	/*El vector recibe par�metros de flotantes y actualliza a los valores dentro de este struct y se imprime en esa ubicaci�n
	@param[x] posici�n en X
	@param[y] posici�n en Y*/
	Vector2(float _x = 0.0f, float _y = 0.0f) :x(_x), y(_y) {};
	
	/*Esta funci�n permite realizar la operaci�n de += 
		@param[Vector2 rhs] el vector que modificar� la posici�n del vector actual*/
	Vector2& operator +=(const Vector2& rhs) {
		x += rhs.x;	//El valor de x suma su valor actual m�s el del par�metro
		y += rhs.y;	//El valor de y suma su valor actual m�s el del par�metro
		return *this;
	};

	/*Esta funci�n permite realizar la operaci�n de -=
	@param[Vector2 rhs] el vector que modificar� la posici�n del vector actual*/
	Vector2& operator -=(const Vector2& rhs)
	{
		x += rhs.x;//El valor de x resta su valor actual m�s el del par�metro
		y += rhs.y;//El valor de y resta su valor actual m�s el del par�metro
		return *this;
	};

	Vector2& scale(float number) {
		
		x *= number;
		y *= number;
		
		return *this;
	};


};

/*Operador que te permite sumar y actualizar el valor de 'x' y 'y'
	@para[vector2 lhs] es el vector principal
	@param[Vector2 rhs] es el vector que modificar� la posici�n del vector original
	@return el vector del objeto va a cambiar su posic�n de acuerdo al resultado*/
inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

/*Operador que te permite restar y actualizar el valor de 'x' y 'y'
	@para[vector2 lhs] es el vector principal
	@param[Vector2 rhs] es el vector que modificar� la posici�n del vector original
	@return el vector del objeto va a cambiar su posic�n de acuerdo al resultado*/
inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

/*Operador que te permite multiplicar y actualizar el valor de 'x' y 'y'
	@para[vector2 lhs] es el vector principal
	@param[Vector2 rhs] es el vector que modificar� la posici�n del vector original
	@return el vector del objeto va a cambiar su posic�n de acuerdo al resultado*/
inline Vector2 operator *(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 operator *(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

inline bool operator <(const Vector2& lhs, const Vector2& rhs)
{
	if(lhs.x < rhs.x && lhs.y < rhs.y)
		return true;
	else
		return false;
}


inline bool operator <=(const Vector2& lhs, const Vector2& rhs)
{
	if(lhs.x <= rhs.x && lhs.y <= rhs.y)
		return true;
	else
		return false;
}

inline bool operator >(const Vector2& lhs, const Vector2& rhs)
{
	if(lhs.x > rhs.x && lhs.y > rhs.y)
		return true;
	else
		return false;
}


inline bool operator >=(const Vector2& lhs, const Vector2& rhs)
{
	if(lhs.x >= rhs.x && lhs.y >= rhs.y || lhs.x > rhs.x || lhs.y > rhs.y)
		return true;
	else
		return false;
}
inline bool operator !=(const Vector2& lhs, const Vector2& rhs)
{
	if(lhs.x != rhs.x && lhs.y != rhs.y || lhs.x != rhs.x || lhs.y != rhs.y)
		return true;
	else
		return false;
}

#endif // !VECTOR2_H
