#include "ConfigIni.h"
ConfigIni* initialize = new ConfigIni();
HANDLE hConsole;

ConfigIni::ConfigIni(string fileName)
{
	try
	{
		
	} catch(string s)
	{
		cout << s;
		exit(0);
	}
	catch(const std::exception& e)
	{ 
		cout << "Exception caught: " << e.what() << endl;
	}


}

ConfigIni::ConfigIni()
{
}

ConfigIni::~ConfigIni()
{
}

void ConfigIni::openFile(const string& file)
{
	try
	{
		fileName = file;
		this->file.open(file);
		if(this->file.fail())
		{
			throw(file);
		} else
		{
			this->file.clear();
		}
	} catch(string s)
	{
		cout << "Your file " + file + "couldn't be open\n";
		exit(0);
	} catch(const std::exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}
}

void ConfigIni::closeFile()
{
	try
	{
		if(file.is_open())
			file.close();
		else
		{
			throw("File is already closed\n");
		}
	} catch(string s)
	{
		cout << s;
	} catch(const std::exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}
}


void ConfigIni::insertSection(const string& section)
{
	try
	{
		file << "[" << section << "]" << endl;
	} catch(const std::exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}
}

void ConfigIni::insertValue(const string& key, const string& value)
{
	try
	{
		file << key << "=" << value << endl;
	}  catch(const std::exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}
}

void ConfigIni::insertComment(const string& comment)
{
	try
	{
		file << "# " << comment << std::endl;
	} catch(const std::exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}
}

void ConfigIni::insertBlankLine()
{
	try
	{
		file << endl;
	} catch(string s)
	{
		cout << s;
		exit(0);
	} catch(const std::exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}
}

void ConfigIni::StartUp() {
	try {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		initialize->openFile("config.ini"); //Se abre el archivo
		initialize->insertSection("window"); //Se crea una sección
		initialize->insertValue("width", "800"); //Se crea la variable "width"
		initialize->insertValue("height", "800"); //Se crea la variable "heigth"
		initialize->insertBlankLine(); //Ingresa una línea en blanco
		initialize->insertSection("memory"); //Se crea una sección
		initialize->insertValue("third", "300"); //Se crea la variable "heigth"
		initialize->insertBlankLine(); //Ingresa una línea en blanco
		initialize->closeFile(); //Se cierra el archivo
		SetConsoleTextAttribute(hConsole, 3);
		initialize->readFile();//Se lee el archivo para asegurarse de que se guardaron las variables

	} catch(exception & e) {
		cout << "Exception caught: " << e.what() << endl;
	}
}

void ConfigIni::readFile()
{
	try
	{
		readableFile.open(fileName);
		if(readableFile.is_open())
		{
			string str;
			while(getline(readableFile, str))
			{
				cout << str << endl;
			}

		}
	} catch(exception & e)
	{
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}