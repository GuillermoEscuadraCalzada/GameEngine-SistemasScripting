#ifndef SECONDBSNS_H
#define SECONDBSNS_H

#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class SecondBSNS : public Texture
{
	static const int ID = 200;
public:
	SecondBSNS(string fileName, int x, int y, int w, int h, int id = ID) : Texture(fileName, x, y, w, h, id) {  };
	~SecondBSNS() {};
};
#endif //!SECONDBSNS_H