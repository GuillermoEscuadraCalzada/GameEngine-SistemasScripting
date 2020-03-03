#ifndef SIXTHBSNS_H
#define SIXTHBSNS_H
#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class SixthBSNS : public Texture
{
public:
	SixthBSNS(string fileName, int x, int y, int w, int h, int id = ID) : Texture(fileName, x, y, w, h, id) {};
	~SixthBSNS() {};
private:
	static const int ID = 600;

};


#endif // !SIXTHBSNS_H
