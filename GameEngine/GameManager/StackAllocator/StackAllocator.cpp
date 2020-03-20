#include "StackAllocator.h"
StackAllocator* StackAllocator::ptr = nullptr;
/*Asignación de memoria para las variables*/
StackAllocator::StackAllocator()
{
	try {
		
		config->StartUp();
		iniReader = new INIReader("config.ini");
		if (iniReader->ParseError() < 0)
		{ //Si no se puede leer nada, manda error
			string str = "No se puede cargar archivo ini\n";
			throw(str);
		}
		int third = iniReader->GetInteger("memory", "third", -1);
		size_t size = 1024 * 1024 * third;
		//printf("%i,%i \n", sizeof(void*), sizeof(size_t));
		static_assert(sizeof(size_t) >= sizeof(void*), "the size of uint must be greater than or equal to the size of a pointer");
		//maxSize = size;
		start = malloc(size);
		maxSize = size;
		if(start == NULL)
		{
			printf("Error al asignar memoria");
		}
		marker = (size_t)start;
		prev = marker;
	}
	catch (string str) {
		
	}
}

StackAllocator::~StackAllocator()
{
}

StackAllocator* StackAllocator::getPTR()
{
	if (!ptr) {
		ptr = new StackAllocator();
	}
	return ptr;
}

void* StackAllocator::alloc(size_t allocsize)
{
	//comprobar si la memoria pedida es igual o menor al tamano que queda en el stack
	if(prev + allocsize <= maxSize)
	{
		prev = marker;
		marker = marker + allocsize;
		return (void*)prev;
	} else
		return NULL;
}

StackAllocator::Marker StackAllocator::getMarker()
{
	return marker;
}

void StackAllocator::clear()
{
	//mover el marcador al inicio del stack
	marker = (size_t)start;
}