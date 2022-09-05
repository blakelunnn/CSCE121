#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    cout << ">> ";
	
    string num1 = "";
	string num2 = "";
	char sign;
	
	while (num1 != "q" && num1 != "quit")
	{
		cin >> num1;
		if(num1 == "q" || num1 == "quit")
			break;
		cin >> sign;
		cin >> num2;
		if(sign == '+')
			cout << "ans =" << endl << endl << "    " << add(num1, num2) << endl << endl << ">> ";
		if(sign == '*')
			cout << "ans =" << endl << endl << "    " << multiply(num1, num2) << endl << endl << ">> ";
	}
	cout << "farvel!" << endl << endl;
}

