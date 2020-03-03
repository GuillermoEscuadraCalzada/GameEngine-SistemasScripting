#ifndef GRAPH_H
#define GRAPH_H
#include  "GraphList.h"
using std::exception; using std::string; using std::cout; using std::endl;
template<class T>
class Graph
{
public:
	Graph<T>();
	~Graph<T>();
	GraphNode<T>* father;
	GraphList<T>* list;
	int size;
	void InsertNode(int index, int index2, GraphNode<T>* father);
	void delete_node_Content(GraphNode<T>* Node);
	void detectMouse(Vector2 mouse, bool pressed);
};

template<class T>
inline Graph<T>::Graph()
{
	list = new GraphList<T>();
}

template<class T>
inline Graph<T>::~Graph()
{
	
}

/*Se ingresará un nodo dentro del arreglo de nodos de la lista del grafo.
 *@param[int index] primer indice del arreglo de nodos
 *@param[int index2] segundo índice del arerglo de nodos
 *@param[GraphNose node] nodo que se añadirá a este lugar*/
template<class T>
inline void Graph<T>::InsertNode(int index, int index2, GraphNode<T>* node)
{
	try
	{
		list->push_at(index, index2, node);
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

template<class T>
inline void Graph<T>::delete_node_Content(GraphNode<T>* Node)
{
}

template<class T>
inline void Graph<T>::detectMouse(Vector2 mouse, bool pressed)
{
	list->detectMouse(mouse, pressed);
}

#endif //!GRAPH_H