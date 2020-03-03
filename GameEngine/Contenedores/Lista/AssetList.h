#ifndef ASSETLIST_H
#define ASSETLIST_H

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
	string path;
	int index;
	AssetNode<T>(T data) : val(data)
	{
		index = 0;
		next = nullptr;
	};
	~AssetNode<T>() {};

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

	void push_back(string key, T value);
	T at(int index);

	T returnTemplate(string key);
	void pop_back();
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

//template<class T>
//inline Vector<T>::Vector()
//{
//	try
//	{
//		
//
//	} catch(exception & e)
//	{
//		cout << "Exception caught: " << e.what() << endl;
//	} catch(...)
//	{
//
//	}
//}
//
//template<class T>
//inline Vector<T>::~Vector()
//{
//	try
//	{
//		first = last = nullptr;
//
//	} catch(exception & e)
//	{
//		cout << "Exception caught: " << e.what() << endl;
//	}catch(...)
//	{
//
//	}
//}

/*Constructor por defecto de la clase Vectors*/
template<class T>
inline AssetList<T>::AssetList()
{
	try
	{
		first = nullptr;
		last = nullptr;
		this->size = 1;
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


/*Función genérica para hacer push_back de elemenots a una lista/vector*/
template<class T>
inline void AssetList<T>::push_back(string key, T value)
{
	try
	{
		AssetNode<T>* temp = new AssetNode<T>(value);	//Guarda un nodo temporal con el valor que se ingresa en los parámetros
		temp->index = size;	//El índice de temp es igual al tamaño
		temp->path = key;	//El path de temp es igual a la llave
		size++;	//Aumenta el tamaño
		
		//Si first es nulo, añade temp a esta posición 
		if(first == nullptr)
		{
			first = temp;	//First toma el valor de temp
			last = first;	//Last es igual a first
		} 
		//Si first es igual a last
		else if(first == last)	
		{
			first->next = temp; //El siguiente a first toma el valor de temp
			last = first->next;	//Last toma el valor de first->next
		} 
		//En caso contrario, el siguiente a last es el valor de temp
		else
		{
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

/*Esta función regresará el tipo de variable elegida. En caso de que no exista, regresará nulo, en caso contrario, regresará el valor del nodo
	@param[ key ] dirección del elemento de este vector dentro de las carpetas del proyecto
	@return te regresa el tipo de variable*/
template<class T>
inline T AssetList<T>::returnTemplate(string key)
{
	try
	{
		AssetNode<T>* iterador = first; //Crea un iterador en l
		while(iterador != nullptr)
		{
			if(iterador->path == key)
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


///*Utiliza la función de SDL para destruir o liberar las variables*/
template<class T>
void AssetList<T>::freeMemory()
{
	try
	{
		AssetNode<T>* iterador = first;	//Iterador toma la primera posición del vector
		
		//Avanza hasta ser nulo
		while(iterador != nullptr)	
		{
			//Pregunta si el template es igual a SDL_Texture
			if(std::is_same_v<T, SDL_Texture*>)
			{
				SDL_Texture* text = iterador->val;//Guarda una variable texture
				SDL_DestroyTexture(text);
				iterador = nullptr;
			}/* else if(std::is_same_v<T, TTF_Font*>)
			{
				TTF_Font* thisFont = iterador->val;
				TTF_CloseFont(thisFont);
				iterador = nullptr;
			}*/
			iterador = iterador->next;
		}
	} catch(const std::exception& e)
	{

	}
}

template<class T>
inline void AssetList<T>::pop_back()
{

	try
	{

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
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
			cout << "Indice: " + to_string(iterador->index) + "\nPath:\t" + iterador->path + "\n";
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


