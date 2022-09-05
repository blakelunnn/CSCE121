#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    if (digit < '0' || digit > '9')
		throw std::invalid_argument("Invalid Input");
	int decimal = digit - 48;
    return decimal;
}

char decimal_to_digit(unsigned int decimal) {
    if (decimal > 9)
		throw std::invalid_argument("Invalid Input");
	char digit = decimal + 48;
    return digit;
}

string trim_leading_zeros(string num) {
    int count = 0;
	long unsigned int index = 0;
	bool done = false;
	bool negative = false;
	
	
	if(num.at(0) == '-')
	{
		num = num.substr(1);
		negative = true;
	}
	while (!done)
	{
		if((index < num.size() - 1) && (num.at(index) == '0'))
		{
			count++;
			index++;
		}
		else
			done = true;
	}
	num = num.substr(count);
	if(negative && num != "0")
		num.insert(0, "-");
    return num;
}

string add(string lhs, string rhs) {
	bool negative = false;
	rhs = trim_leading_zeros(rhs);
	lhs = trim_leading_zeros(lhs);
	
	int indexLHS = lhs.size() - 1;
    int indexRHS = rhs.size() - 1;
    string answer = "";
    int carry = 0;
    int numLHS = 0;
    int numRHS = 0;
    int combined = 0;
    
	if(rhs == "0" && lhs == "0")
		return "0";
	
	if(rhs == "0")
		return lhs;
	if(lhs == "0")
		return rhs;
	
	
	
	if(lhs.at(0) == '-')
    {
        lhs = lhs.substr(1);
        rhs = rhs.substr(1);
        indexLHS--;
        indexRHS--;
        negative = true;
    }
	
    while (indexLHS >= 0 && indexRHS >= 0)
    {
        
        numLHS = digit_to_decimal(lhs.at(indexLHS));
        
        numRHS = digit_to_decimal(rhs.at(indexRHS));
        combined = numLHS + numRHS + carry;
        
        if(combined >= 10)
        {
            combined %= 10;
            answer.insert(0, std::to_string(combined));
            carry = 1;
        }
        else
        {
            answer.insert(0, std::to_string(combined));
            carry = 0;
        }
        indexLHS--;
        indexRHS--;
    }
    
	if(indexLHS < 0 && indexRHS < 0 && carry == 1)
		answer.insert(0, "1");
	
    while(indexLHS >= 0)
    {
        if(carry == 1)
        {
            numLHS = digit_to_decimal(lhs.at(indexLHS)) + carry;
            if(numLHS == 10 && indexLHS >= 1)
			{
				numLHS %= 10;
				answer.insert(0, std::to_string(numLHS));
			}
			else if (indexLHS == 0)
			{
				indexLHS--;
			    answer.insert(0, std::to_string(numLHS));	
			}
			else
			{
			    carry = 0;
				answer.insert(0, std::to_string(numLHS));
			}
        }
        else
        {
            numLHS = digit_to_decimal(lhs.at(indexLHS));
            answer.insert(0, std::to_string(numLHS));   
        }
        indexLHS--;
    }
	
    while(indexRHS >= 0)
    {
        if(carry == 1)
        {
            numRHS = digit_to_decimal(rhs.at(indexRHS)) + carry;
            if(numRHS == 10 && indexRHS >= 1)
			{
				numRHS %= 10;
				answer.insert(0, std::to_string(numRHS));
			}
			else if (indexRHS == 0)
			{
				indexRHS--;
			    answer.insert(0, std::to_string(numRHS));	
			}
			else
			{
				carry = 0;
				answer.insert(0, std::to_string(numRHS));
			}
        }
        else
        {
            numRHS = digit_to_decimal(rhs.at(indexRHS));
            answer.insert(0, std::to_string(numRHS));   
        }
        indexRHS--;
    }
	
    if(negative)
	{    
		answer.insert(0, "-");
	}
	
	return answer;
}

string multiply(string lhs, string rhs) {
    
	string answer = "0", inter;
	int count = 0;
	bool negativeLHS = false;
	bool negativeRHS = false;
	
	if(lhs.at(0) == '-')
    {
        lhs = lhs.substr(1);
        negativeLHS = true;
    }
	
	if(rhs.at(0) == '-')
    {
        rhs = rhs.substr(1);
        negativeRHS = true;
    }
	
	for (int x = lhs.size() - 1; x >= 0; x--)
	{
		int carry = 0;
		inter = "";
			for(int y = rhs.size() - 1; y >= 0; y--)
			{
				int product = digit_to_decimal(rhs.at(y)) * digit_to_decimal(lhs.at(x)) + carry;
				carry = product / 10;
				product %= 10;
				inter.insert(0, std::to_string(product));
			}
			inter = decimal_to_digit(carry) + inter;
			for(int z = 0; z < count; z++)
			{
				inter = inter + '0';
			}
			count++;
			answer = add(answer, inter);
	}
	
	if((negativeLHS == false && negativeRHS == true) || (negativeLHS == true && negativeRHS == false))
	{
		answer.insert(0, "-");
	}
    return trim_leading_zeros(answer);
}
