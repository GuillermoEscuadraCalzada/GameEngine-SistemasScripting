#ifndef CONFIGINI_H
#define CONFIGINI_H
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
using namespace std;
class  ConfigIni
{
public:
	ConfigIni(string fileName);
	ConfigIni();
	~ ConfigIni();

	void openFile(const string& file);
	void closeFile();
	void insertSection(const string& section);
	void insertValue(const string& key, const string& value);
	void insertComment(const string& comment);
	void insertBlankLine();
	void StartUp();

	void readFile();
private:
	ofstream file;
	fstream readableFile;
	string fileName;

};


#endif // !CONFIGINI_H

