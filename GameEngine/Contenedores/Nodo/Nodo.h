#pragma once
#include "Lista.h"
template<class T>
class Nodo
{
public:
	T value; // Esto guarda el objeto deseado
	Nodo<T>* prev;
	Lista<Nodo<T>*> listaN; // esto guarda los apuntadores a los hijos
	Nodo<T>* next;
	Nodo<T>* padre;
	int index;
	bool visited;
	Nodo(T dat) : value(dat)
	{
		//padre = NULL;
		next = prev = padre = NULL;
		index = 0;
		visited = false;
	};

	~Nodo() {};

};
