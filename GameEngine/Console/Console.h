#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <fstream>
#include "../String/String.h"
using namespace std;
class Console
{

public:
	static Console* GetPTR();
	void SaveConsole();
	String finalMSG;
private:
	static Console* ptr;
	Console();
	~Console();
};
#endif // !CONSOLE_H


