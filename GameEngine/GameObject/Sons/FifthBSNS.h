#ifndef FIFTHBSNS_H
#define FIFTHBSNS_H

#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class FifthBSNS : public Texture
{
public:
	FifthBSNS(string fileName, int x, int y, int w, int h, int id = ID) : Texture(fileName, x, y, w, h, id) {};
	~FifthBSNS() {};
private:
	static const int ID = 500;

};



#endif // !FIFTHBSNS_H
