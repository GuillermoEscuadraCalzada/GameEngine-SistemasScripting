#ifndef STACK_H
#define STACK_H
#include <iostream>
using std::cout; using std::endl; using std::exception;

/*Clase nodo del stack*/
template<class T>
class StackNode
{
public: 
	StackNode<T>* next; //Apuntador al siguiente en el stack
	StackNode<T>* prev;	//Apuntador al anterior en el stack
	T value; //Valor que guardará el nodo
	int index;	//Indice del nodo
	
	/*Constructor de la clase StackNode
	 *@param[T _value] cualquier elemento que  se desee ingresar en el stack se almacenará en el nodo
	 */
	StackNode<T>(T _value) : value(_value) 
	{
		index = 0;
		//Apuntadores comienzan en nulo
		next = nullptr;
		prev = nullptr;
	};
	~StackNode<T>() {};	//Destructor de la clase stackNode
};

/*Clase Stack*/
template<class T>
class Stack
{
public:

	Stack<T>();
	~Stack<T>();
	StackNode<T>* first; //Primer elemento de la clase Stack
	StackNode<T>* last; //último elemento de la clase Stack
	int size = 0; //Tamaño del stack
	void push_front(T value);
	bool destroy();
	
};

/*Constructor de la clase stack*/
template<class T>
inline Stack<T>::Stack()
{
	try
	{
		first = last = nullptr; //Los apuntadores comienzan siendo nulos
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It exploded!\n";
	}
}

/*Destructo de la clase stack*/
template<class T>
inline Stack<T>::~Stack()
{
	try
	{
		StackNode<T>* it = first; //Iterador que comienza en el primer elemento del stack
		//Se hacen los elemento del stack nulos
		while(it != nullptr)
		{
			StackNode<T>* Temp = it->next;	//Guarda un apuntador al siguiente del iterador
			delete it; //Elimina al iterador
			it = nullptr;	//Hazlo nulo
			it = Temp; //Ahora se vuelve el temporal
			if(it != nullptr)
				it->prev = nullptr; //Haz al anterior nulo
		}
	} catch(exception & e)
	{

	} catch(...)
	{

	}
}

/*El stack es una pila de elementos, por lo que cada que se ingrese un nuevo elementos, se irá volviendo el elemento de hasta arriba de nuesto contenedor
 *@param[T value] elemento que se ingresará en el stack y se guardará en el nodo
 */
template<class T>
inline void Stack<T>::push_front(T value)
{
	try
	{

		StackNode<T>* temp = new StackNode<T>(value);	//Un nodo temporal que almacenará este valor
		temp->index = size;	//Indice del temporal es igual al tamaño
		size++;	//Aumenta el tamaño
		//Si first es igual a nulo
		if(first == nullptr)	
		{
			first = temp; //First es igual al temporal
			last = first;	//Last es igual a first
		}
		//Si first es igual a last
		else if(first == last)
		{
			first = temp; //First es igual al temporal
			first->next = last; //El elemento siguiente a first es last
			last->prev = first; //El anterior a last es first

		} else
		{//Si hay dos elementos en la lista
			StackNode<T>* tempFirst = first; //Nodo temporal que es igual a first
			first = temp;	//First toma el valor del temporal
			first->next = tempFirst; //El siguiente a first es tempFirst
			tempFirst->prev = first;	//El anterior a tempFirst es first
		}

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

/*Esta función destruirá todos los elementos del grafo que se encuentren dentro del stack de un nodo en la lista del grafo
 *@return verdadero para que así se puedan sumar puntos al score del jugador*/
template<class T>
inline bool Stack<T>::destroy()
{
	try
	{
		StackNode<T>* it = first;
		while(it != nullptr)
		{
			if(it->value->father != nullptr)
				it->value->father = nullptr;
			delete it->value->value;
			it->value->value = nullptr;
			
			it = it->next;
		}
		return true;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}


}



#endif STACK_H