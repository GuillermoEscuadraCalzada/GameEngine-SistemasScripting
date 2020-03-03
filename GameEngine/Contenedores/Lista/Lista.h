#pragma once
#include <iostream>
using std::cout;
template<class S>
class Lista
{
public:
	S first;
	S last;
	int size;
	Lista();
	~Lista();
	bool found;
	void addNode(S val, S padre);
	S search(S val);
	S search(S val, S padre);
};

//Constructor predeterminado de la clase Lista
template<class S>
inline Lista<S>::Lista()
{
	//listData = NULL;
	first = last = NULL;
	size = 0;
}

//Destructor predeterminado de la clase lista
template<class S>
inline Lista<S>::~Lista()
{
}


/*Se agrega un nodo a la lista de cualquier tipo
	@param[val] se intoduce el valor que se quiere ingresar a la lista.*/
template<class S>
inline void Lista<S>::addNode(S val, S padre)
{
	try
	{
		size++; //Aumenta el tamaño de la lista
		if(first == NULL)
		{
			first = val;
			first->padre = padre;
			last = first;
		} else if(first == last) //Sólo hay un elemento en la lista. 
		{
			last = val; //El último obtiene el valor de un nuevo nodo
			last->index++;
			first->next = last; //Last se vuelve el segundo elemento en la lista
			last->prev = first;
			last->padre = first->padre;
		} else  //Se añaden más elementos a la lista
		{
			last->next = val;	//Se crea un nodo posterior al último elemento

			last->next->index = last->index;	//El índice de este último obtiene el indice de su anterior
			last->next->index++;	//Aumenta uno su índice
				
			last->next->prev = last;	//El previo de esta lísta es el último en la lista actualmente
			last->next->padre = last->padre;	//Obtiene el padre de su elemento anterior
			last = last->next;

		}
	} catch(std::exception & e)
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	} catch(...)
	{

	}
}


/*Se busca un valor en la lista para saber si existe o no
	@Param[val] lo que se desea buscar en la lista.*/
template<class S>
inline S Lista<S>::search(S val)
{
	try
	{
		bool skip = false;
		if(first == nullptr)		//La lista está vacía
		{
			return nullptr;
		} else  //La lista tiene más de un elemento
		{
			S iterador = first;  //Este iterador forma parte del primer elemento de la lista
			while(iterador != nullptr)  //Busca hasta que llegue a ser nullptr
			{

				if(iterador->value == val->value) //Si el iterador encuentra este valor, imprime que lo encontró
				{
					return iterador;	//Se regresa este iterador
				} else if(iterador->value != val->value)
				{
					S temp = iterador;
					if(iterador->listaN.size > 0)	//En caso de que el iterador no contentga el valor del argumento, busca en su lista
					{
						S hijo = iterador->listaN.first;	//Hijo guarda el valor  del primer elemento en la lista del padre.
						while(hijo != nullptr)
						{
							if(hijo->value == val->value)//Si el hijo se encuentra en la lista, regresa al hijo
							{
								//hijo->visited = true;
								return hijo; //Regresa al hijo
							} else
								hijo = hijo->next;
						}
					}
				}
				iterador = iterador->next;
			}

			return nullptr;

		}
	} catch(std::exception & e) //Esta excepción te muestra algún potencial error
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	} catch(...)
	{

	}
}

template<class S>
inline S Lista<S>::search(S val, S padre)
{
	try
	{
		S iterador = padre->listaN.first;	//Toma el valor del primero en la lista de padre
		bool skip = false;
		found = false;
		if(padre == nullptr)	//El padre es nulo
			return nullptr;	//Regresa nulo
		else if(padre->value == val->value)	//Si el padre contiene el valor de val, regresa este nodo
		{
			return padre;
		} else
		{
			while(iterador != nullptr)	//Avanza hasta ser nulo
			{
				if(iterador->value == val->value)	//Si el iterador contiene el valor	
				{
					if(iterador->visited != true)	//Pregunta si ya fue visitado
					{
						found = true;	//Pon a found verdadero si no fue visitado
						iterador->visited = true;	//Si no fue visitado, regresa verdadero
					} else //Si ya fue visitado
					{
						found = true;	//Pon a found verdadero
						return iterador;	//Regresa este iterador
					}
				} else if(iterador->visited == true && iterador->listaN.size > 0)	// El iterador ya fue visitado pero tiene una lista de hijos con elementos
				{
					search(val, iterador);//Repite esta función en la lista de hijos
				}
				if(found == true)	//Si ya se encontró un valor, rompe el ciclo while
					break;

				iterador = iterador->next;
			}
		}
		return iterador;
	} catch(std::exception & e) //Esta excepción te muestra algún potencial error
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	} catch(...)
	{

	}
}