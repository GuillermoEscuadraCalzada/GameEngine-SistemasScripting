#ifndef THIRDBSNS_H
#define THIRDBSNS_H

#include "../../Graphics/Texture/Texture.h"
#include <iostream>
using std::string;
class ThirdBSNS : public Texture
{
public:
	ThirdBSNS(string fileNamee, int x, int y, int w, int h, int id = ID) : Texture(fileNamee, x, y, w, h, id) {};
	~ThirdBSNS() {};
private:
	static const int ID = 300;

};

#endif // !THIRDBSNS_H

