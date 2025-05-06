#pragma once
#include <iostream>

class CharArray
{
private:
	CharArray();

public:
	int Size = 0;
	char* List = nullptr;
	int BGColor = 7;
	int FGColor = 0;

	CharArray(int size, int bgColor = 7, int fgColor = 0);
	~CharArray();

	void StoreValue(int index, char value);
	void StoreAllValue(char value, bool overrideChar, char charAffected);
	void StoreString(int index, std::string value);
	char GetValue(int index);
	int& GetSize();
};

