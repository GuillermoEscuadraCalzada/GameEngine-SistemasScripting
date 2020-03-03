#pragma once
#include "Nodo.h"
#include <iostream>
using std::cout;
template<class S>
class Grafo
{
public:
	Grafo();
	~Grafo();
	bool achieved = false;
	Nodo<S>* aiuda = nullptr;

	Nodo<S>* father;
	int size;
	bool exists = false;
	void insertaNodo(S data, Nodo<S>* padre); // 25% inserta un nodo agregando el apuntador a la lista de hijos del padre
	Nodo<S>* buscaNodo(S data, Nodo<S>* root); // 25% busca un nodo por su data y regresa el apuntador al nodo si es que lo encuentra
	void eliminaNodo(S data, Nodo<S>* root); // 25% busca un nodo por su data, y lo elimina, asegurándose que sus hijos son agregados a otro nodo
	void imprimeGrafo(Nodo<S>* padre); // 25% imprime el grafo de la siguiente manera: Padre1{hijo1, hijo2, hijo3,..., hijoN}

};

//Constructor predeterminado de la clase Grafo
template<class S>
inline Grafo<S>::Grafo()
{
	size = 0;
	father = nullptr;
}

//Destructor predeterminado de la clase Grafo
template<class S>
inline Grafo<S>::~Grafo()
{

}


/*El grafo buscará si el padre que se ingresa en el argumento existe, en caso de ser así, el nodo se inserta en la lista de hijos. Si el padre es nulo, se crea un nodo y forma a ser el padre
	 @param[val] dato que se quiere insertar en el nodo
	 @param[padre] padre al que pertenece*/
template<class S>
inline void Grafo<S>::insertaNodo(S data, Nodo<S>* padre)
{
	try
	{
		NodoG<S>* temp = new NodoG<S>(data);	//Crea un nodo con el valor temporal
		size++; //Aumenta el tamaño
		if(padre == father)	//El padre es nulo
		{
			if(father == nullptr)
				father = temp;	//Father es igual al temporal		
			else
			{
				temp->padre = father;	//El padre del temporal es el padre dentro del grafo
				father->listaN.addNode(temp, padre);	//Inserta temporal a la lista de father
			}
		} else if(padre != father)	//padre es diferente de father
		{
			if(father->listaN.search(padre, father) == nullptr)	//Si el padre no se encuentra de grafo, añadelo a la lista de padre
			{
				padre->padre = father;
				father->listaN.addNode(padre, father);
			} else      //El padre se encuentra dentro del grafo
			{
				NodoG<S>* hijo = father->listaN.first;//Crea un nodo que sea el primer elemento dentro de la lista de padre.
				while(hijo != nullptr)
				{
					if(hijo->value == padre->value)//El padre introducido se encuentra en la lista de hijos
					{
						padre = hijo;	//El padre introducido toma los valores del hijo
						hijo->listaN.addNode(temp, padre);	//Añade el valor al hijo
						break;	//Rompe el ciclo while
					} else if(hijo->listaN.size > 0)	//Si la lista de hijos tiene lista de hijos, avanza a ella
						hijo = hijo->listaN.first;	//Entra a la lista de hijos.
					else //Si no lo encuentra avanza al siguiente hijo
						hijo = hijo->next;
				}

			}
		}
	} catch(std::exception & e)
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	} catch(...)
	{

	}
}


/*Busca un nodo dentro del grafo
	@param[data] el valor que se quiere buscar si existe en el grafo
	@param[padre] el padre donde tiene que avanzar el iterador al momento de buscar en la lista de hijos*/
template<class S>
inline Nodo<S>* Grafo<S>::buscaNodo(S data, Nodo<S>* padre)
{
	try
	{
		if(padre == nullptr)	//El nodo es nulo, no existe en el grafo
		{
			printf("Nodo no encontrado\n");
			return nullptr;
		} else if(padre != nullptr && padre->value == data)	//El nodo existe y la raíz o el padre tiene el mismo valor
		{
			printf("Nodo encontrado!\n");
			return padre;	//Regresa al padre
		} else   //El padre existe pero su valor es diferente, por lo tanto se buscará dentro de su lista.
		{
			if(padre->listaN.size == 0)	//Si la lista del padre no tiene elementos, regresa nulo
			{
				printf("Nodo no encontrado!\n");
				return nullptr;
			} else    //La lista del padre esta llena
			{
				Nodo<S>* temp = padre->listaN.first;	//Guarda l valor temporal del primer elemento de la lista del padre
				while(temp != nullptr)	//Avamza hasta qie eñ te,´prañ sea miñp
				{
					if(temp->value == data)	//El valor del temporal es igual a data
					{
						buscaNodo(data, temp);	//Reinicia la búsqueda pero ahora temp es el padre
					} else
					{
						buscaNodo(data, temp); //Reinicia la búsqueda pero ahora temp es el padre
					}
					temp = temp->next; //Avanza en la búsqueda
				}
			}
		}
	} catch(std::exception & e)
	{
		cout << "Exception Caught: " << e.what() << "\n";
	} catch(...)
	{

	}
}


/*Elimina un nodo dentro del grafo, puede ser el padre o alguno de sus hijos
	@param[data] valor del nodo que se va a busar y eliminar
	@param[root] padre en el cual se va a buscar mientras el iterador está dentro de la lista de hijos*/
template<class S>
inline void Grafo<S>::eliminaNodo(S data, Nodo<S>* root)
{
	try
	{
		if(root->value == data && root->listaN.size == 0)	//La raíz tiene el valor y su lista no tiene elementos
		{
			if(root->prev == nullptr && root->next)	//El elemento es el primero en la lista
			{
				root->padre->listaN.first = root->next;
				root->next->prev = nullptr;
				aiuda = root->next;
			} else if(root->prev != nullptr && root->next == nullptr)	//El elemento se encuentra al final de la lista
			{
				root->prev->next = root->next;
				root->padre->listaN.last = nullptr;
			} else if(root->prev != nullptr && root->next != nullptr)	//El elemento se encuentra en medio de la lista
			{
				root->prev->next = root->next;
				root->next->prev = root->prev;
			}
			delete root;
			root = nullptr;
			size--;
		} else if(root->value != data && root->listaN.size > 0) //La raíz no tiene el mismo valor que data y el tamaño de su lista es mayor a cero
		{
			NodoG<S>* iterador = root->listaN.first;	//Guarda el valor del iterador

			while(iterador != nullptr)	//Itera hasta que sea diferente de nulo
			{
				if(iterador->value == data)	//Si el valor del iterador
				{
					NodoG<S>* temp = iterador->next;	//Guarda un nodo temporal que almacene el siguiente al iterador.
					eliminaNodo(data, iterador);

					if(temp == nullptr)
						iterador = aiuda;
					else
						iterador = temp;

					break;	//Haz un break para que no vuelva a buscar en otros nodos.
				} else
					eliminaNodo(data, iterador);

				iterador = iterador->next;	//Avanza al siguiente en la lista.

			}

		}
#pragma region El padre tiene el valor y su lista es mayor a cero.
		else if(root->value == data && root->listaN.size > 0)
		{
			NodoG<S>* temp = root->listaN.first;	//Guarda el valor del primer elemento de este padre
#pragma region El valor se encuenra en el padre de todo el grafo
			if(root->padre == nullptr)	//El valor se encuentra en el padre de todos
			{
				NodoG<S>* temp2 = temp->next;	//Se guarda un apuntador temporal a todos los valores posteriores al temporal
				temp->padre = nullptr;	//El padre del temporal es nulo

				while(temp2 != nullptr)	//Avanza hasta que temporal2 sea nulo
				{
					temp->listaN.addNode(temp2, temp);	//Se agrega cada el elemento de temporal 2 a la lista de temporal.
					temp2 = temp2->next;	//Avanza al temporal 2
				}
				delete root;
				if(root == father)
					father = temp;
				else
					root = temp;
				return;
			}
#pragma endregion
#pragma region Primer elemento de la lista
			if(root->next != nullptr && root->prev == nullptr) //El padre no tiene a nadie detrás pero sí tiene a alguien en frente
			{
				root->padre->listaN.first = root->next;//El primero en la lista del padre de este padre es el siguiente en la lista
				root->next->listaN.addNode(temp, root->next);	//Se agregan los valores de la lista a la lista del siguiente elemento.
				root->next->prev = nullptr;	//El previo al siguiente en la lista, se hace nulo
			}
#pragma endregion

#pragma region Elemento entre el principio y final
			else if(root->next != nullptr && root->prev != nullptr)	//El padre se encuentra entre dos padres diferentes.
			{
				root->prev->next = root->next;	//El nodo siguiente al anterior es el que le sigue a este.
				root->next->prev = root->prev;	//El anterior al siguiente es el anterior a este
				root->next->listaN.addNode(temp, root->next);	//Se añade la lista de este padre a la lista del siguiente en la lista
			}
#pragma endregion

#pragma region Último elemento de la lista
			else if(root->next == nullptr && root->prev != nullptr)		//Este elemento es el último de la lista.
			{
				root->prev->next = nullptr;	//El siguiente al anterior es nulo
				root->prev->listaN.addNode(temp, root->prev);	//Añade la lista al elemento anterior.
			}

#pragma endregion
#pragma region  Elemento único en la lista
			else    //El elemento se encuentra sólo en la lista.
			{
				while(temp != nullptr)	//Avanza en la lista de hijos
				{
					root->padre->listaN.addNode(temp, root->padre);	//Agrégalos a la lista del padre
					temp = temp->next;	//Avanza al siguiente elemento
				}
				root->padre->listaN.first = root->padre->listaN.first->next;	//El primer elemento cambia al que le sigue.
				aiuda = root->padre->listaN.first; //Se igualan estos nodos
				aiuda->prev = nullptr;
			}
#pragma endregion
			delete root;
			root = nullptr;
			size--;
		}
#pragma endregion


	} catch(std::exception & e)
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	} catch(...)
	{

	}
}


/*Se va a imprimir todo el grafo, dividiendo padres eh hijos por medio de corchetes.
	@param[Padre] el padre donde se encuentra el iterador actualmente.*/
template<class S>
inline void Grafo<S>::imprimeGrafo(Nodo<S>* padre)
{
	try
	{
		if(padre == nullptr)	//El padre  es nulo
			printf("Empty Graph\n\n");
		else
		{
			if(exists == false)
				cout << padre->value << "{ ";
			else if(padre == father)
				cout << padre->value << "{ ";
			NodoG<S>* iterador = padre->listaN.first;
			while(iterador != nullptr)
			{
				cout << iterador->value;
				if(iterador->listaN.size > 0)
				{
					printf(" {");
					exists = true;
					imprimeGrafo(iterador);
				}

				iterador = iterador->next;
				if(iterador == nullptr)
					printf("} ");
				else
					printf(", ");
			}
		}
	} catch(std::exception & e)
	{
		cout << "Exception caught: " << e.what() << "\n";
	} catch(...)
	{

	}


}