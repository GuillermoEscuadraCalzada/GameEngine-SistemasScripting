#ifndef FOURTHBSNS_H
#define FOURTHBSNS_H

#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class FourthBSNS: public Texture
{
	static const int ID = 400;
public: 
	FourthBSNS(string fileNamee, int x, int y, int w, int h, int id = ID) : Texture(fileNamee, x, y, w, h, id) {};
	~FourthBSNS() {};
};
#endif // !FOURTHBSNS_H

