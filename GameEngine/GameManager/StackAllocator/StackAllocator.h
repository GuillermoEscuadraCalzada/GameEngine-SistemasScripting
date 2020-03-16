#include <iostream>
#include "../../ConfigIni/ConfigIni.h"
#include "../../ConfigIni/INIReader.h"
class StackAllocator
{

public:
	static StackAllocator* getPTR();
	//static StackAllocator* getPTR();
	typedef size_t Marker;
	void* alloc(size_t allocsize);
	Marker getMarker();
	//void freeToMarker(Marker marker);
	void clear();
	INIReader* iniReader;
private:
	static StackAllocator* ptr;
	StackAllocator(size_t size);
	StackAllocator();
	~StackAllocator();
	//tamano del buffer total
	Marker maxSize;
	void* start;
	Marker marker;
	ConfigIni* config = new ConfigIni();
	Marker prev;
};