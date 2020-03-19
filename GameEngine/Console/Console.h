#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>
#include <fstream>
using namespace std;
class Console
{

public:
	static Console* GetPTR();
	void SaveConsole();
private:
	string finalMSG;
	static Console* ptr;
	Console();
	~Console();
};
#endif // !CONSOLE_H


