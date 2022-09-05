// TODO: Implement this source file
#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>
#include "MyString.h"

MyString::MyString(): lengthOfString(0), capacityOfString(1), smiles(nullptr)
{
	smiles = new char[capacityOfString];
	smiles[0] = '\0';
}

MyString::MyString(const MyString& string): lengthOfString(string.lengthOfString), capacityOfString(string.capacityOfString), smiles(nullptr)
{
	smiles = new char[capacityOfString];
	for(size_t x = 0; x < string.length(); x++)
		smiles[x] = string.smiles[x];
		
	smiles[lengthOfString] = '\0';
}

MyString::MyString(const char* string): lengthOfString(0), capacityOfString(1), smiles(nullptr)
{
	smiles = new char[capacityOfString];
	for(int x = 0; x < string[x]; x++)
	{
		lengthOfString++;
		if(lengthOfString == capacityOfString)
			resize(capacityOfString * 2);
		smiles[x] = string[x];
	}
	
	smiles[lengthOfString] = '\0';
}

MyString::~MyString()
{
	delete[] smiles;
}

void MyString::resize(size_t newSize)
{
	capacityOfString = newSize;
	char* temp = new char[newSize];
	for(size_t x = 0; x < lengthOfString; x++)
		temp[x] = smiles[x];
	
	delete[] smiles;
	smiles = temp;
	temp = nullptr;
	smiles[capacityOfString] = '\0';
}

size_t MyString::capacity() const
{
	return capacityOfString;
}

size_t MyString::size() const
{
	return lengthOfString;
}

size_t MyString::length() const
{
	return lengthOfString;
}

const char* MyString::data() const
{
	return smiles;
}

bool MyString::empty() const
{
	bool emptyOrNot = false;
	if(this->length() == 0)
		emptyOrNot = true;
	
	return emptyOrNot;
}

const char& MyString::front() const
{
	return smiles[0];
}

const char& MyString::at(size_t index) const
{
	if(index >= length())
		throw std::invalid_argument("Invalid Index");
	
	return smiles[index];
}

void MyString::clear()
{
	lengthOfString = 0;
	capacityOfString = 1;
	
	delete[] smiles;
	smiles = new char[1];
	smiles[0] = '\0';
}

MyString& MyString::operator= (const MyString& string)
{
	delete[] smiles;
	lengthOfString = string.length();
	capacityOfString = string.capacity();
	smiles = new char[capacityOfString];
	for(size_t x = 0; x < string.length(); x++)
		smiles[x] = string.smiles[x];
	
	smiles[lengthOfString] = '\0';
	return *this;
}

MyString& MyString::operator+= (const MyString& string)
{
	size_t tempSize = lengthOfString;
	for(size_t x = 0; x < string.length(); x++)
	{
		if(capacityOfString == x + tempSize)
			resize(capacityOfString * 2);
		
		lengthOfString++;
		smiles[x + tempSize] = string.at(x);
	}
	
	smiles[lengthOfString] = '\0';
	return *this;
}

size_t MyString::find(const MyString& string, size_t index) const
{
	for(size_t x = index; x < length(); x++)
	{
		bool found = true;
		if(smiles[x] == string.at(0))
		{
			if(string.length() == 1)
				return x;
			for(size_t y = 0; y < string.length(); y++)
				if(smiles[x + y] != string.at(y))
				{
					found = false;
					break;
				}
			if(found)
				return x;
		}
	}
	return -1;
}

std::ostream& operator<< (std::ostream& os, const MyString& string)
{
	for(size_t x = 0; x < string.length(); x++)
		os << string.at(x);
		
	return os;
}