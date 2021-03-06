#ifndef STRING_H
#define STRING_H
#include <iostream>
//typedef basic_string<wchar_t> wstring;
using namespace std;
class String
{
public:	
	bool operator==(String& compare);

	void operator=(String set);
	void operator=(const string&  set);
	void operator=(const wstring& add);
	void operator=(const char* add);
	
	void operator+=(const string& s);
	void operator+=(const wstring& s);
	
	String operator+(const string& s);
	String operator+(String& s);
	String operator+(const wstring& s);
	String operator+(const char* s);
	String operator+(const char s);
	std::wstring convert(const string& toConvert);
	String();
	String(string str);
	String(wstring& wstr);
	String(const char* c);
	~String();
	wstring GetWString();
	void setWString(const wstring&);
	void PrintWString();
private:
	wstring wString;

};


#endif // !STRING_H
