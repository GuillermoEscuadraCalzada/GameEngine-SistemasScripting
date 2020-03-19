#include "Console.h"

Console* Console::ptr = nullptr;

Console* Console::GetPTR()
{
	if (!ptr)
		ptr = new Console();
	return ptr;
}

Console::Console()
{
}

Console::~Console()
{
}

void Console::SaveConsole()
{
	std::ofstream outfile("../ConsoleError/Console.txt");
	finalMSG += "ola qué tal";
	outfile << finalMSG;
	outfile.close();
}