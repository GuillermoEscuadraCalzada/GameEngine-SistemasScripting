#ifndef MYVECTOR_H
#define MY_VECTOR_H
#include <iostream>
#include <string>
using std::cout; using std::endl; using std::exception; using std::to_string;
using std::string;

template<class T>
class Node
{
public:
	T val;
	string path;
	Node<T>* next;
	Node<T>* prev;
	int index;
	Node<T>(T value) : val(value)
	{
		path = value->GetPath();
		next = prev = nullptr;
		index = NULL;
	};

	~Node<T>() {};
};

template< class T>
class myVector
{
public: 
	int size;
	myVector<T>();
	~myVector<T>();
	Node<T>* first;
	Node<T>* last;
	void push_back(T value);
	T* return_at(string path);
	std::string* return_string(int indx);
	SDL_Rect* return_at(int index);
	void print();
};

#endif // !MYVECTOR_H

template<class T>
inline myVector< T>::myVector()
{
	first = nullptr;
	last = nullptr;
	size = 0;
}

template<class T>
inline myVector<T>::~myVector()
{
	Node<T>* it = first;
	while(it != nullptr)
	{
		Node<T>* temp = it->next;
		delete it;
		it = nullptr;
		it = temp;
	}
}

template<class T>
inline void myVector<T>::push_back(T value)
{
	try
	{
		Node<T>* temp = new Node<T>(value);
		temp->index = size;
		size++;
		if(first == nullptr)
		{
			first = temp;
			last = first;
		} else if(first == last)
		{
			first->next = temp;
			last = first->next;
		} else
		{
			last->next = temp;
			last = last->next;
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Something crashed\n";
	}
}

template<class T>
inline T* myVector<T>::return_at(string path)
{
	try
	{
		Node<T>* iterador = first;
		while(iterador != nullptr)
		{
			if(iterador->val->GetPath() == path)
			{
				return &iterador->val;
			}
			iterador = iterador->next;
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
	}
	return nullptr;
}

template<class T>
inline std::string* myVector<T>::return_string(int indx)
{
	try
	{
		Node<T>* it = first;
		while(it != nullptr)
		{
			if(indx == it->index)
			{
				return &it->val->textText;
			}
			it = it->next;
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Something crashed\n";
	}
}

template<class T>
inline SDL_Rect* myVector<T>::return_at(int index)
{
	try
	{
		Node<T>* it = first;
		while(it != nullptr)
		{
			if(index == it->index)
			{
				return it->val->rect;
			}
			it = it->next;
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Something crashed\n";
	}
}


template<class T>
inline void myVector<T>::print()
{
	try
	{
		Node<T>* iterador = first;
		
		while(iterador != nullptr)
		{
			cout << "Indice: " + to_string(iterador->index) + "\nPath:\t" + iterador->val->GetPath() +"\n";
			iterador = iterador->next;
		}


	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Something crashed\n";
	}
}

