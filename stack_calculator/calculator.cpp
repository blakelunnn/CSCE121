#include <iostream>
#include <string>
#include <sstream>
#include "functions.h"
using std::cin, std::cout, std::endl, std::string, std::istringstream;

int main() {
  // prompt user input
  cout << "Type RPN expression (end with '=')." << endl;
  cout << "> ";
  
  //TODO: create a command-line interface for calculator GUI
	Stack userStack{};
	string userInput;
	cin >> userInput;
	
	while(userInput != "=")
	{
		if(userInput == "+")
		{
			int rightOperand = pop(userStack);
			int leftOperand = pop(userStack);
			int result = leftOperand + rightOperand;
			push(userStack, result);
		}
		else if(userInput == "-")
		{
			int rightOperand = pop(userStack);
			int leftOperand = pop(userStack);
			int result = leftOperand - rightOperand;
			push(userStack, result);
		}
		else if(userInput == "*")
		{
			int rightOperand = pop(userStack);
			int leftOperand = pop(userStack);
			int result = leftOperand * rightOperand;
			push(userStack, result);
		}
		else if(userInput == "/")
		{
			int rightOperand = pop(userStack);
			int leftOperand = pop(userStack);
			int result = leftOperand / rightOperand;
			push(userStack, result);
		}
		else if(userInput == "^")
		{
			int rightOperand = pop(userStack);
			int leftOperand = pop(userStack);
			int result = 1;
			for(int x = 0; x < rightOperand; x++)
				result *= leftOperand;
			push(userStack, result);
		}
		else
			push(userStack, std::stoi(userInput));
		
		cin >> userInput;
	}
	
	cout << "Ans: " << pop(userStack) << endl;
	delete[] userStack.numbers;
	return 0;
}