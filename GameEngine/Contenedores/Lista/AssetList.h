#ifndef ASSETLIST_H
#define ASSETLIST_H

#include "../../String/String.h"
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
using std::cout; using std::exception; using std::endl; using std::to_string; using std::string; using std::is_same;

template<class T>
class AssetNode
{
public:
	T val;
	AssetNode<T>* next;
	String path;
	int index;
	AssetNode<T>(T data) : val(data)
	{
		index = 0;
		next = nullptr;
	};
	~AssetNode<T>() {};
	int number = 0;
private: 
};

template<class T>
class AssetList
{
public:
	AssetNode<T>* first;
	AssetNode<T>* last;
	//int size;
	AssetList<T>();

	~AssetList<T>();

	void push_back(wstring key, T value);
	T at(int index);

	T returnTemplate(wstring key);
	void print();
	void freeMemory();

	int getCurrent()
	{
		return current;
	}

	int getSize()
	{
		return size;
	}


private:
	int size;
	int current;
};

/*Constructor por defecto de la clase Vectors*/
template<class T>
inline AssetList<T>::AssetList()
{
	try
	{
		first = nullptr;
		last = nullptr;
		this->size = 0;
		this->current = 0;
		
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}


/*Constructo para la clase Vector*/
template<class T>
inline AssetList<T>::~AssetList()
{
	try
	{
		size = NULL;
		current = NULL;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}catch(...)
	{

	}
}


/*Funci�n gen�rica para hacer push_back de elemenots a una lista/vector*/
template<class T>
inline void AssetList<T>::push_back(wstring key, T value)
{
	try
	{
		AssetNode<T>* temp = new AssetNode<T>(value);	//Guarda un nodo temporal con el valor que se ingresa en los par�metros
		temp->index = size;	//El �ndice de temp es igual al tama�o
		temp->path = key;	//El path de temp es igual a la llave
		size++;	//Aumenta el tama�o
		
		//Si first es nulo, a�ade temp a esta posici�n 
		if(first == nullptr)
		{
			first = temp;	//First toma el valor de temp
			last = first;	//Last es igual a first
		} 
		//Si first es igual a last
		else if(first == last)	
		{
			if (temp->path == first->path) {
				int numb = first->number;
				numb++;
				temp->number = numb;
				temp->path += to_string(temp->number);
			}
			first->next = temp; //El siguiente a first toma el valor de temp
			last = first->next;	//Last toma el valor de first->next
		} 
		//En caso contrario, el siguiente a last es el valor de temp
		else
		{
			if (temp->path == last->path) {
				temp->number = last->number + 1;
				temp->path += to_string(temp->number);
			}
			last->next = temp;	//El siguiente a last toma el valor de temp
			last = last->next;	//Last se convierte en last->next
		}



	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}

template<class T>
inline T AssetList<T>::at(int index)
{
	try
	{
		AssetNode<T>* it = first;
		while(it != nullptr)
		{
			if(index == it->index)
			{
				return it->val;
			}
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}

/*Esta funci�n regresar� el tipo de variable elegida. En caso de que no exista, regresar� nulo, en caso contrario, regresar� el valor del nodo
	@param[ key ] direcci�n del elemento de este vector dentro de las carpetas del proyecto
	@return te regresa el tipo de variable*/
template<class T>
inline T AssetList<T>::returnTemplate(wstring key)
{
	try
	{
		AssetNode<T>* iterador = first; //Crea un iterador en l
		while(iterador != nullptr)
		{
			if(iterador->path.GetWString() == key)
			{
				return iterador->val;
			}

			iterador = iterador->next;
		}
		return nullptr;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}


///*Utiliza la funci�n de SDL para destruir o liberar las variables*/
template<class T>
void AssetList<T>::freeMemory()
{
	try
	{
		AssetNode<T>* iterador = first;	//Iterador toma la primera posici�n del vector
		
		//Avanza hasta ser nulo
		while(iterador != nullptr)	
		{
			//Pregunta si el template es igual a SDL_Texture
			if(std::is_same_v<T, SDL_Texture*>)
			{
				SDL_Texture* text = iterador->val;//Guarda una variable texture
				SDL_DestroyTexture(text);
				iterador = nullptr;
			}
			iterador = iterador->next;
		}
	} catch(const std::exception& e)
	{

	}
}


/*Imprime las direcciones de las texturas o de algun otro elemento*/
template<class T>
inline void AssetList<T>::print()
{
	try
	{
		AssetNode<T>* iterador = first;
		while(iterador != nullptr)
		{
			wcout << L"Indice: " + to_wstring(iterador->index) +  L"\nPath:\t" + iterador->path.GetWString() + L"\n";
			iterador = iterador->next;
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}





#endif // !ASSETLIST_H


