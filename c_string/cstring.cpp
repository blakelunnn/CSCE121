#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  
  int count = 0; 
    while (str[count]) {
        count++; 
    }
   return count;
}

unsigned int find(char str[], char character) {
  int len = length(str);
  for(int x = 0; x < len; x++)
	if(str[x] == character)
		return x;
  return len;
}

bool equalStr(char str1[], char str2[]) {
  // returns true if they are equal and false if they are not
  return true;
}