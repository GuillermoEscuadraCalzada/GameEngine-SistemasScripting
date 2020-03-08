#include <iostream>
class StackAllocator
{

public:
	typedef size_t Marker;
	StackAllocator(size_t size);
	void* alloc(size_t size);
	Marker getMarker();
	void freeToMarker(Marker marker);
	void clear();

private:
	//int maxSize;
	Marker maxSize;
	void* start;
	Marker marker;
	
	Marker prev;
};