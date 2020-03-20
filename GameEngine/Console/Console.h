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
	enum LANGUAGE { SPANISH, ENGLISH };
	LANGUAGE languages;
private:
	static Console* ptr;
	Console();
	~Console();
};
#endif // !CONSOLE_H


