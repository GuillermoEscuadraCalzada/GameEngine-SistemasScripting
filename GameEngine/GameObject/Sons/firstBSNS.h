#ifndef _FIRSTBSNS_H
#define _FIRSTBSNS_H

#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;

class firstBSNS : public Texture
{

	static const int ID = 50;
public:
	firstBSNS(string fileNamee, int x, int y, int w, int h, int id = ID) : Texture(fileNamee, x, y, w, h, id) {};
	~firstBSNS() {};

};



#endif // !_FIRSTBSNS_H



