#ifndef  GRAPHLIST_H
#define GRAPHLIST_H
#include <iostream>
#include "../GameObject/Vector2.h"
#include "Stack/Stack.h"

#include "../GameObject/Sons/firstBSNS.h"
#include "../GameObject/Sons/SecondBSNS.h"
#include "../GameObject/Sons/ThirdBSNS.h"
#include "../GameObject/Sons/FourthBSNS.h"
#include "../GameObject/Sons/FifthBSNS.h"
#include "../GameObject/Sons/SixthBSNS.h"

using std::string; using std::exception; using std::cout; using std::endl;
enum num
{
	firstt = 1,
	second = 2,
	third = 3,
	fourth = 4,
	fifth = 5,
	sixth = 6
};

//Clase nodo que se enocntrará dentro del grafo
template<class T>
class GraphNode
{
public:
	T value; //Cualquier valor que entre al template se guardará en el nodo
	Vector2 position;

	myVector<T>* list;
	int index;	//Indice del nodo
	bool visited;	//Valor que determina si ya fue visitado o no
	Stack<GraphNode*>* nodeStack;
	bool searching;
	GraphNode<T>* next;	//Apuntador al siguiente elemento dentro del grafo
	GraphNode<T>* prev;	//Apuntador al elemento anterior dentro del grafo
	GraphNode<T>* top;	//Apuntador a una posición superior dentro del grafo
	GraphNode<T>* bottom;	//Apuntador que busca la posición inferior de este nodo
	GraphNode<T>* father;

	/*Constructor de la clase nodo
		@param[T value] cualquier elemento que se añade a esta lista y se lo iguala al valor de la clase*/
	GraphNode<T>(T _value, Vector2 vec) : value(_value), position(vec)
	{
		visited = false;	//Visited empieza en falso
		index = 0;	//Indice es igual a cero
		next = prev = top = bottom = father = nullptr;
		list = nullptr;
		nodeStack = new Stack<GraphNode<T>*>();
		
	};
	
	GraphNode<T>() {};
};



template<class T>
class GraphList
{
public:
	int index2 = 0;
	int counter = 0;

	GraphNode<T>* first;
	GraphNode<T>* nodeToFind;

	//GraphNode<T>* last;
	int size = 64;
	GraphList<T>();
	~GraphList<T>();
	bool found = false;
	bool stop = false;
	void push_at(int index, int index2, GraphNode<T>* value);
	GraphNode<T>* return_at_array(int index, int index2);
	GraphNode<T>* return_at_index(int index, GraphNode<T>* root);
	GraphNode<T>* detectMouse(GraphNode<T>* root, Vector2 mousePos, bool pressed);
	GraphNode<T>* searchNode(GraphNode<T>* first, GraphNode<T>* node);
	void bool_to_false(GraphNode<T>* first);
	void addSons(GraphNode<T>* first);
	void deleteImages(GraphNode<T>* first);
	bool Update(GraphNode<T>* first);
	void renderNode(GraphNode<T>* node);
	void swap(GraphNode<T>* ghLeft, GraphNode<T>* ghRight);
	void push_new_images(GraphNode<T>* first);
	GraphNode<T>* graphArr[8][8];
private:
};

template<class T>
inline GraphList<T>::GraphList()
{
	try
	{
		first = nullptr;
		nodeToFind = nullptr;
		
	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	}
	catch(...)
	{
		cout << "Ups, something crashed!\n";
	}

}

/*Destructor de la clase grafo*/
template<class T>
inline GraphList<T>::~GraphList()
{
	try
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				graphArr[i][j] = nullptr;
			}
		}
	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups, something crashed!\n";
	}
	
}

/*Push at timará dos índices que le ayudarán a ingresar un nodo a su arreglo de nodos
 *@param[int index] indice de las filas del arreglo [index][]
 *@param[int index2] indice de las columnas del arreglo [index][index2]
 *@param[GraphNode* value] nodo que entrará al arreglo en los índices establecidos*/
template<class T>
inline void GraphList<T>::push_at(int index, int index2, GraphNode<T>* value)
{
	try{	
		bool placed = false;	//Booleano que hará un break en el primer for, así se evita buscar en todas las posiciones
		GraphNode<T>* temp = value;//un nodo temporal que es igual al valor
		
		//Ciclo entre el arreglo de los nodos
		for(int i = 0; i < size;i++ )
		{
			for(int j = 0; j < size; j++)
			{
				graphArr[index][index2] = temp; //En esta posición del arreglo, se guardará el valor
				placed = true; //Se vuelve verdader
				break; //Deja de avanzar
			}
			//Si es verdadero, deja de avanzar
			if(placed)
				break;
		}
	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups, something crashed!\n";
	}
}

/*Esta función nos regresa un nodo en el arreglo de nodos gracias a los índices indicados en los parámetros
 *param[int index] indice en las filas del arreglo
 *param[int index2] indice en las columnas del arreglo
 *return el nodo en esa posición 
 */
template<class T>
inline GraphNode<T>* GraphList<T>::return_at_array(int index, int index2)
{
	try
	{
		/*Se recorre todo el arreglo hasta encontrar la posición de los índices dentro del arreglo*/
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				//Si 'i' y 'j' son iguales, regresa este nodo
				if(i == index && j == index2)
				{
					return graphArr[i][j];	//Regresa este nodo
				}
			}
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
	
	}
}

/*Esta función avanzará por todos los nodos hasta encontrar con el nodo indicado y así poder hallar el indicado
 *@param[int index] indice que se debe buscar entre los nodos
 *@param[GraphNode<T>* root] apuntador que nos servirá para ir por medio de la recursividad entre ndoos.*/
template<class T>
inline GraphNode<T>* GraphList<T>::return_at_index(int index, GraphNode<T>* root)
{
	try
	{
		GraphNode<T>* it = root;	//Nodo iterador que es igual a root
		GraphNode<T>* it2 = nullptr;	//Segundo nodo iterador iniciado en nulo

		//Si el apuntador debajo de la raíz es diferente a nulo, el segundo iterador avanza ahí mismo
		if(root->bottom != nullptr)
			it2 = root->bottom;

		//Si index es mayor al último índice o si el índice es menor a cero, regresa nulo, esta fuera de los límites
		if(index > size - 1 || index < 0)
			return nullptr;
		
		/*Avanza el primer iterador hasta encontrar el resultado*/
		while(it != nullptr)
		{
			//Si el iterador tiene el índice igual al introducido, regresa este valor
			if( it->index == index)
			{
				nodeToFind = it;
				found = true;
			}
			//Si su siguiente nodo es nulo, avanza al nodo inferior al nodo principal de esta línea
			if(it->next == nullptr)
			{
				//Si ese iterador es diferente de nulo, avanza
				if(it2 != nullptr)
				{
					return_at_index(index, it2); //Avanza al nodo inferior del primer nodo de esta fila	
				}
			}
			if(found)
				break;
			it = it->next;
		}
		found = false;
		return nodeToFind;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}


/*Esta función detecta si el mouse se encuentra en la ubicación del nodo correspondiente a la posición del mouse
 *@param[GraphNode<T>*] Nodo principal desde donde comenzará la búsqueda
 *@param[Vector2] vector que nos indica la posición del mouse
 *@param[bool] este booleano proviene del InputManager y pregunta si algun botón del mouse fue presionado
 *@return nodo de la clase Lista.*/
template<class T>
inline GraphNode<T>* GraphList<T>::detectMouse(GraphNode<T>* root, Vector2 mousePos, bool pressed)
{
	try
	{
		GraphNode<T>* it = root;	//Nodo que es igual a la raíz desde donde partirá
		GraphNode<T>* it2 = nullptr;	//Ese nodo comienza en nulo

		//Si el apuntador debajo de la raíz es diferente a nulo, el segundo iterador avanza ahí mismo
		if(root->bottom != nullptr)
			it2 = root->bottom;

		/*Avanza el primer iterador hasta encontrar el resultado*/
		while(it != nullptr)
		{
			//Pregunta si la posición del mouse se encuentra entre el cuadrante de la imagen y regresa su valor
			if(it->value  && mousePos.x >= it->value->rect->x && mousePos.x <= it->value->rect->x + it->value->rect->w
			   && mousePos.y >= it->value->rect->y && mousePos.y <= it->value->rect->y + it->value->rect->h)
			{
				cout << it->value->textText << endl;
				if(pressed)
				{

					nodeToFind = it;	 //Este nodo guarda el valor del iterador.
					found = true;	//Este booleano se vuelve verdadero
				}
			}

			//Si su siguiente nodo es nulo, avanza al nodo inferior al nodo principal de esta línea
			if(it->next == nullptr)
			{
				//Si ese iterador es diferente de nulo, avanza
				if(it2 != nullptr)
				{
					detectMouse(it2, mousePos, pressed);
				}
			}
			//Si es verdadero, detente
			if(found)
				break;
			
			it = it->next;
		}
		found = false;
		return nodeToFind;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

/*Se busca un nodo dentro de todos los nodos del grafo
 *@param[GraphNode<T>* first] nodo desde el cual se empezará a buscar en la fila
 *@param[GraphNode<T>* node] nodo que se desea encontrar*/
template<class T>
inline GraphNode<T>* GraphList<T>::searchNode(GraphNode<T>* first, GraphNode<T>* node)
{
	try
	{
		GraphNode<T>* it = first;	//Nodo que se igualará al primer nodo del argumento, 
		GraphNode<T>* it2 = nullptr;	//Un nodo que es nulo 

		//Si el nodo inferior al nodo del argumento es diferente de nulo, el nodo it2 será igual a ese valor
		if(first->bottom != nullptr)
			it2 = first->bottom;


		//Itera por todo el grafo
		while(it != nullptr)
		{

			//Si encuentras el nodo
			if(it == node)
			{
				nodeToFind = it;	//NodeToFind es igual al iterador
				found = true;	//Regresa verdadero
			}
			//Si el siguiente del iterador es igual a nulo, 
			if(it->next == nullptr)
			{
				//Y mientras it2 no sea nulo,
				if(it2 != nullptr)
					searchNode(it2, node); //Avanza al iterador it2
			}
			//Si se encontró el nodo, ya no avances más
			if(found)
				break;
			it = it->next; //Avanza al siguiente

		}
		found = false;	//Found se vuelve falso
		return nodeToFind; //Regresa NodeToFind
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

/*Al finalizar el swap y de ingresar los elementos al stack de cada padre, se deben de regresar los booleanos de visitado a falso
	@param[GraphNode<T>* first] elemento al que se avanzará para poder iterar*/
template<class T>
inline void GraphList<T>::bool_to_false(GraphNode<T>* first)
{
	try
	{
		GraphNode<T>* it = first;	//Iterador que toma la posición del argumento
		GraphNode<T>* it2 = nullptr;	//Iterador nulo
		if(it->bottom != nullptr)	//Si el iterador inferior es nulo
			it2 = it->bottom;	//It2 es el nodo inferior

		//Avanza hasta ser nulo
		while(it != nullptr)
		{
			it->visited = !it->visited; //Cambia los valores del booleano
			//Pregunta si next es nulo
			if(it->next != nullptr)
				it = it->next;	//Avavanza a next
			else
			{	//Si fue nulo
				//Pregunta si it2 es nulo
				if(it2 != nullptr)
				{
					bool_to_false(it2);	//Recursividad en it2
					break;//Aal finalizar la recursividad rompe el ciclo
				} else
					return; //Regresa
			}
		}

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

/*Itera por todo el grafo y pregunta si al rededor de cada nodo hay un objeto igual, si es igual, toma el primer elemento del nodo de ese tipo y busca entre sus similares cercanos, al final se agregan al stack de este nodo
 *@param[GraphNode<T>* first] nodo desde donde comenzará la búsqueda
 */
template<class T>
inline void GraphList<T>::addSons(GraphNode<T>* first)
{
	try
	{
		GraphNode<T>* it = first; //Apuntador al primer elemento del grafo
		GraphNode<T>* it2 = nullptr;		//Segundo apuntador en la posición del 
		
		//Pregunta si el nodo inferior es nulo
		if(it->bottom != nullptr)
			it2 = it->bottom;	//It 2 es igual a este nodo

		while(it != nullptr)
		{
			it->visited = true;	//Este iterador ya fue visitado.
			it->searching = true;	//La búsqueda comienta
			//Mientras esté activa
			while(it->searching)
			{
				if(it->top != nullptr && !it->top->visited && it->top->value->textText == it->value->textText) {//Pregunta si el superior es diferente de nulo y si no ha sido visitado
					if(it->father == nullptr){//Pregunta si el padre es igual a nulo
						if(it->nodeStack == nullptr) //Si el stack es nulo
							it->nodeStack = new Stack<GraphNode<T>*>();	//Crea uno nuevo
						it->top->father = it;//El padre es el iterador
						it->nodeStack->push_front(it->top); //Ingresa este elemento al stack
					} else
					{
						if(it->father->nodeStack == nullptr)
							it->father->nodeStack = new Stack<GraphNode<T>*>();
						it->top->father = it->father;
						it->father->nodeStack->push_front(it->father);
					}
					addSons(it->top);
				}
				else if(it->prev != nullptr && !it->prev->visited && it->prev->value->textText == it->value->textText) {//Pregunta si el nodo de la derecha es diferente de nulo y si no ha sido visitado, además de preguntar si el texto es el mismo
					if(it->father == nullptr){ //Pregunta si el padre es nulo
						if(it->nodeStack == nullptr)
							it->nodeStack = new Stack<GraphNode<T>*>();
						it->prev->father = it; //El padre es el iterador
						it->nodeStack->push_front(it->prev); //añade prev al stack del iterador
					} else { //Si no es nulo
						if(it->father->nodeStack == nullptr)	//Pregunta si stack es nulo
							it->father->nodeStack = new Stack<GraphNode<T>*>(); //Crea uno nuevo
						it->prev->father = it->father;//El padre del iterador es el padre de prev
						it->father->nodeStack->push_front(it->prev);	//Añade prev al stack del padre
					}
					addSons(it->prev);	//Recursividad en prev
				}
				//Pregunta si el nodo de la derecha es diferente de nulo y si no ha sido visitado, además de preguntar si el texto es el mismo
				else if(it->next != nullptr && !it->next->visited && it->next->value->textText == it->value->textText) {//Pregunta si el padre es nulo
					if(it->father == nullptr) { //Pregunta si el padre es nulo
						if(it->nodeStack == nullptr) //Pregunta si el stack es nulo
							it->nodeStack = new Stack<GraphNode<T>*>();
						it->next->father = it;	//El iterador es el padre
						it->nodeStack->push_front(it->next); //Ingresa next al stack del iterador
					} else	{ //Si no es nulo
						if(it->father->nodeStack == nullptr) //Pregunta si el stack es nulp
							it->father->nodeStack = new Stack<GraphNode<T>*>(); //Crea un nuevo stack
						it->next->father = it->father; //El padre es el padre del iterador
						it->father->nodeStack->push_front(it->next);	//Ingresa este nodo al stack del padre
					}
					addSons(it->next); //Recursividad en este nodo
				}
				else if(it->bottom != nullptr && !it->bottom->visited && it->bottom->value->textText == it->value->textText) { //Pregunta si el nodo inferior es nulo y si no ha sido visitado
					if(it->father == nullptr) {	//Pregunta si el padre del iterador es igual a nulo
						//Pregunta si el stack del iterador es igual a nulo
						if(it->nodeStack == nullptr)
							it->nodeStack = new Stack<GraphNode<T>*>(); //Crea un nuevo stack
						it->bottom->father = it; //El padre es el iterador
						it->nodeStack->push_front(it->bottom); //Ingresa el nodo inferior al stack
					} else { //Si 
						if(it->father->nodeStack == nullptr)
							it->father->nodeStack = new Stack<GraphNode<T>*>();
						it->bottom->father = it->father;
						it->father->nodeStack->push_front(it->bottom);
					}
					addSons(it->bottom);
				} else  { //Si no funciona ningún caso, busca si el padre sigue buscando o si ya dejó de buscar
					if(it->father != nullptr) { //Pregunta si el padre es nulo
						if(it->father->searching) { //Pregunta si el padre sigue 
							it->searching = !it->searching; //el iterador deja de buscar
							return; //Regresa
						} else 
							it->searching = !it->searching;
						
					} else //Si no tiene padre es porque este nodo es el padre
						it->searching = !it->searching;
				}
			} 
			if(it->next != nullptr)
				it = it->next;
			else if(it2 != nullptr)
			{
				addSons(it2);
				break;
			} else
				it = nullptr;
		}


	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}

}


/*Destruir las imágenes requiere que el stack del objeto tenga 3 o más elementos dentro del stack del nodo
 *@param[GraphNode<T>* first] el primer elemento del grafo o el elemento que se utilizará para la recursividad
 */
template<class T>
inline void GraphList<T>::deleteImages(GraphNode<T>* first)
{
	try
	{
		GraphNode<T>* it = first;	//Iterador en el nodo
		GraphNode<T>* it2 = nullptr;	//SSegundo iterador nulo
		//Si el apuntador inferior existe
		if(it->bottom)
			it2 = it->bottom; //El segundo iterador avanará ahí mismo

		while(it != nullptr)
		{
			//Pregunta si el stack del iterador es diferente de nulo y si el tamaño es mayor o igual a tes
			if(it->nodeStack != nullptr && it->nodeStack->size >= 3)
			{
				delete it->value;	//Borra el valor actual del nodo
				it->value = nullptr;	//Hazlo nulo
				it->nodeStack->destroy();	//Destruye cada valor del stack
				it->nodeStack = nullptr; //Haz nulo el stack del iterador
			}
			if(it->next != nullptr) //Si el siguiente es diferente de nulo
				it = it->next;	//Avanza a esa posición
			else
			{
				if(it2 != nullptr)
				{ //Si el iterador 2 es diferente de nulo
					deleteImages(it2);	//Recursa en el iterador 2
					break; //Termina el while
				} else
					return;	//Regresa
			}
		}

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
	
}

/*Función que hará que todas las imágenes caigan al momento de revisar si el apuntador superior es dferente de nulo
 *@param[GraphNode<T>* first] apuntador al nodo que se iterará*/
template<class T>
inline bool GraphList<T>::Update(GraphNode<T>* first)
{
	try
	{
		GraphNode<T>* it = first;	//iterador en el nodo indicado
		GraphNode<T>* it2 = nullptr; //Iterador que es nulo
		if(it->bottom) //Si la parte inferior del iterador existe, el segundo iterador avanzará ahí
			it2 = it->bottom; //it2 avanza al nodo inferior
		//bool searching;

		////Mientras el iterador no sea nulo
		while(it)
		{
			if(!it->top)
			{ //Si next existe
				if(it->next)
					it = it->next; //Avanza al siguiente
				else
				{ //Si no existe, avanza a la siguiente fila
					if(it2)
					{//Si existe la fila inferior, recursa en esa fila
						Update(it2);
						break;
					} else//En caso contario, regresa
						return true;
				}

			} else
			{ //Si el nodo de arriba existe				
				if(!it->value && it->top->value)
				{ //Pregunta si el valor actual es nulo y si el valor de arriba existe 
					T val = it->top->value;	//Guarda un valor que es igual al valor del nodo superior
					it->value = it->top->value;	//El valor del nodo actual es igual al del nodo superior
					it->value->Position(Vector2(it->position.x + it->value->rect->w / 2, it->position.y + it->value->rect->h / 2));	//Positiona ahora el valor actual en la posición del nodo 
					//delete it->top->value;
					it->top->value = nullptr;	//haz nulo el de arriba
					if(it->next) //Avanza al siguiente
						it = it->next;
					else
					{ //Si no existe, avanza a la siguiente fila
						if(it2)
						{
							Update(it2);
							break;
						} else //Si la siguiente fila no existe, regresa
							return true;
					}
				} else if(it->value && it->top->value || it->value && !it->top->value || !it->value && !it->top->value)
				{
					it = it->next;
				}
			}
		

		}

		
		

	}
  catch(exception & e)
   {
   	cout << "Exception caught: " << e.what() << endl;
   } catch(...)
   {
   	cout << "Ups! It crashed!\n";
   }
}

/*Esta función nos permite renderizar cualquier imagen dentro de los nodos en el arreglo de manera recursiva,
 *guardos una variable del siguiente al que apunta el nodo principal y cada vez que ese sea nulo, avanzamos al que se encuentra en la parte
 *inferior al nodo principal
 *@param[node] nodo que irá recorriendo la función*/
template<class T>
inline void GraphList<T>::renderNode(GraphNode<T>* node)
{
	try
	{

		GraphNode<T>* it = node;	//Un iterador al nodo del argumento
		GraphNode<T>* it2 = nullptr; //Un iterador que comienza nulo
		if(node->bottom != nullptr) //Si el nodo que se encuentra debajo del nodo principal es diferente de nulo, el nodo it2 avanza a ese nodo
		{
			it2 = node->bottom;
		}

		//Avanza hasta que este sea nulo
		while(it != nullptr)
		{
			//Si esete iterador no es nulo, renderizalo
			if(it != nullptr && it->value != nullptr)
			{
				it->value->Render();
			}
			//Si su siguiente nodo es nulo, avanza al nodo inferior al nodo principal de esta línea
			if(it->next == nullptr)
			{
				//Si ese iterador es diferente de nulo, avanza
				if(it2 != nullptr)
				{
					renderNode(it2);
				}
			}
			it = it->next;	//Avanza al siguiente para finalizar
		}
		////Se cicla en todo el arreglo 
		//for(int i = 0; i < 8; i++)
		//{
		//	for(int j = 0; j < 8; j++)
		//	{
		//		graphArr[i][j]->value->Render(); //Se renderiza cada nodo
		//	}
		//}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

/*Esta función intercambiará las texturas de los nodos seleccionados con el mouse
 *@param[GraphNode<T>* ghleft] primer nodo tocado en el juego
 *@param[GraphNode<T>* ghRight] segundo nodo tocado en el juego*/
template<class T>
inline void GraphList<T>::swap(GraphNode<T>* ghLeft, GraphNode<T>* ghRight)
{
	try
	{

		GraphNode<T>* firstNode = searchNode(first, ghLeft);	//Busca el nodo en el grafo y guardalo dentro de una variable
		GraphNode<T>* secondNode = searchNode(first, ghRight); //Busca el nodo en el grafo y fuardalo dentro de una variable
		T text1 = firstNode->value;	//Crea una variable tipo template e igualala al valor dentro de firstNode
		T text2 = secondNode->value;	//Crea una variable tipo template e igualala al valor dentro de secondNode

		//Preguntar si el segundo nodo es algún hijo del primer nodo, si lo es, crea un vector temporal
		if(secondNode == firstNode->next || secondNode == firstNode->prev || secondNode == firstNode->top || secondNode == firstNode->bottom)
		{
			Vector2 temp = text1->Position();	//Vector temporal de la posición de text1
			text1->Position(text2->Position()); //Text 1 cambia su posición al de text2
			text2->Position(temp); //Text2 toma el valor del vector temporal
			firstNode->value = text2;	//El valor del primer nodo cambia
			secondNode->value = text1;	//Al igual que el valor del segundo nodo
			
		}
		else
		{
			printf("Te conozco?\n");
		}


	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

/*Se añaden nuevas imágenes que irán cayendo constántemente cada vez que una imagen se destruya
	@param[GraphNode<T>* first] nodo desde el que se iterará*/
template<class T>
inline void GraphList<T>::push_new_images(GraphNode<T>* first)
{
	try
	{
		GraphNode<T>* it = first;
		GraphNode<T>* it2 = nullptr;
		if(it->next) //Si la parte inferior del iterador existe, el segundo iterador avanzará ahí
			it2 = it; //it2 avanza al nodo inferior
		counter = 0;
		/*Se crean todas las imágenes */
		firstBSNS* firstB = new firstBSNS("FirstBSNS.png", 0, 0, 70, 70);
		SecondBSNS* secondBSNS = new SecondBSNS("SecondBSNS.png", 0, 0, 70, 70);
		ThirdBSNS* thirdBSNS = new ThirdBSNS("ThirdBSNS.png", 0, 0, 70, 70);
		FourthBSNS* fourthBSNS = new FourthBSNS("FourthBSNS.png", 0, 0, 70, 70);
		FifthBSNS* fifthBSNS = new FifthBSNS("FifthBSNS.png", 0, 0, 70, 70);
		SixthBSNS* sixthBSNS = new SixthBSNS("SixthBSNS.png", 0, 0, 70, 70);

		/*Itera hasta ser nulo*/
		while(it) {
			if(!it->value){ //Pregunta si el valor de este nodo es nulo 
				while(it)
				{
					if(!it->value)
					{ //Si es 
						it = it->bottom;
						counter++;
					} else
					{
						it = it2;
						break;
					}

				}
				if(counter > 0) {
					Texture** rect = new Texture * [counter];
					for(int i = 0; i <= counter; i++) {
						int random = rand() % 6 + 1;

						switch(random){
						case firstt:
							rect[i] = firstB;
							break;
						case second:
							rect[i] = secondBSNS;
							break;
						case third:
							rect[i] = thirdBSNS;
							break;
						case fourth:
							rect[i] = fourthBSNS;
							break;
						case fifth:
							rect[i] = fifthBSNS;
							break;
						case sixth:
							rect[i] = sixthBSNS;
							break;
						}

						it->value = rect[i];
						it->value->Position(Vector2(it->position.x + it->value->rect->w / 2, it->position.y + it->value->rect->h / 2));
						if(!it->bottom->value)
							it = it->bottom;
						else
						{
							if(it2->next)
								push_new_images(it2->next);
							else
							{
								return;
							}

						}
						
					}
				} 
			}
			it = it->next;	
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

#endif // ! GRAPHLIST_H