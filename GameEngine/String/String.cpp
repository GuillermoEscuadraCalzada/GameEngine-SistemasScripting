#include "String.h"
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <comdef.h>

/*Operador de igualación que pregunta si dos strings son iguales o no*/
bool String::operator==(String& compare)
{
	// TODO: Insertar una instrucción "return" aquí
	try {
        if (wString == compare.GetWString())
            return true;
        throw(false);
   	}
	catch (bool b) {
		cout << "Este string no es igual al que se propone\n";
	}
}

/*Se igualan todos objetos de clse string, el wstring de este objeto toma el valor del argumento*/
void String::operator=(String add)
{
    // TODO: Insertar una instrucción "return" aquí
    wString = add.GetWString();
}

void String::operator=(const string& add)
{
    wString = convert(add);
}

void String::operator=(const std::wstring& add)
{
    wString = add;
}

void String::operator=(const char* add)
{
    wString = convert(string(add));
}

/*Se le suma al widestring el string del argumento, primero lo convierte y se resuelve la operación*/
void String::operator+=(const string& s)
{
    wString += convert(s);
}

/*Sumarle al wstring de la clase, cualquier string que se desee*/
String String::operator+(const string& s)
{
    return String(wString += convert(s));
}

/*Sumarle al wstring el wstring de otro objeto String*/
String String::operator+(String s)
{
    return String(wString + s.GetWString());
}


String String::operator+(const wstring& s)
{
    return String(wString += s);
}

String String::operator+(const char* s)
{
    return String(wString += convert(string(s)));
}

/*Convierte un string común y corriente a un wstring, para que acepte todo tipo de caracteres*/
std::wstring String::convert(const string& toConvert)
{
    try
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(toConvert);
    }
    catch (std::range_error & e)
    {
        size_t length = toConvert.length();
        std::wstring result;
        result.reserve(length);
        for (size_t i = 0; i < length; i++)
        {
            result.push_back(toConvert[i] & 0xFF);
        }
        return result;
    }
}


String::String()
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    wString = L"";
}

String::String(const string& str)
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    wString = convert(str);
}

String::String(const std::wstring& wstr)
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    wString = wstr;
}

String::String(const char* c)
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    wString = convert(c);
}
String::~String()
{
}

std::wstring String::GetWString()
{
    return wString;
}

void String::setWString(const wstring& string)
{
    wString = string;
}
