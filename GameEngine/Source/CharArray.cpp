#include "Includes/CharArray.h"
#include <iostream>

CharArray::CharArray(int size, int bgColor, int fgColor)
{
	Size = size;
	List = new char[Size];
	BGColor = bgColor;
	FGColor = fgColor;
}

int& CharArray::GetSize()
{
	return Size;
}

CharArray::~CharArray()
{
	if (List) { delete[] List; }
}

void CharArray::StoreValue(int index, char value)
{
	List[index] = value;
}

void CharArray::StoreAllValue(char value, bool overrideChar = false, char charAffected = ' ')
{
	for (int i = 0; i < Size; i++)	{
		char c = GetValue(i);
		if (overrideChar == true && c == charAffected) { StoreValue(i, value); }
		else { if (c == ' ') { StoreValue(i, value); } }
	}
}

void CharArray::StoreString(int index, std::string value)
{
	for (char& c : value)	{
		StoreValue(index++, c);
	}
}

char CharArray::GetValue(int index)
{
	return List[index];
}
