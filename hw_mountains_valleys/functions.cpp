#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	if (a >= 10 && b < 10000 && a <= b)
		return true;
	else
		return false;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	int temp = 0;
	int hundredthousand;
	int tenthousand;
	int thousand;
	int hundred;
	int tens;
	int ones;
	if (number / 100000 >= 1)
		{
			hundredthousand = number / 100000;
			temp = number % 100000;
			tenthousand = temp / 10000;
			temp = number % 10000;
			thousand = temp / 1000;
			temp = number % 1000;
			hundred = temp / 100;
			temp = temp % 100;
			tens = temp / 10;
			temp = temp % 10;
			ones = temp;
			if (hundredthousand < tenthousand && tenthousand > thousand && thousand < hundred && hundred > tens && tens < ones)
				return 'M';
			if (hundredthousand > tenthousand && tenthousand < thousand && thousand > hundred && hundred < tens && tens > ones)
				return 'V';
		}
	else if (number / 10000 >= 1)
		{
			tenthousand = number / 10000;
			temp = number % 10000;
			thousand = temp / 1000;
			temp = number % 1000;
			hundred = temp / 100;
			temp = temp % 100;
			tens = temp / 10;
			temp = temp % 10;
			ones = temp;
			if (tenthousand < thousand && thousand > hundred && hundred < tens && tens > ones)
				return 'M';
			if (tenthousand > thousand && thousand < hundred && hundred > tens && tens < ones)
				return 'V';
		}
	if (number / 1000 >= 1)
		{
			thousand = number / 1000;
			temp = number % 1000;
			hundred = temp / 100;
			temp = temp % 100;
			tens = temp / 10;
			temp = temp % 10;
			ones = temp;
			if (thousand < hundred && hundred > tens && tens < ones)
				return 'M';
			if (thousand > hundred && hundred < tens && tens > ones)
				return 'V';
		}
	else if (number / 100 >= 1)
		{
			hundred = number / 100;
			temp = number % 100;
			tens = temp / 10;
			temp = temp % 10;
			ones = temp;
			if (hundred < tens && tens > ones)
				return 'M';
			if (hundred > tens && tens < ones)
				return 'V';
		}
	else if (number / 10 >= 1)
		{
			tens = number / 10;
			temp = number % 10;
			ones = temp;
			if (tens < ones)
				return 'M';
			if (tens > ones)
				return 'V';
		}
	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int countM = 0;
	int countV = 0;
	int intervalA = a;
	
	while (a <= b)
	{
		if (classify_mv_range_type(a) == 'M')
			countM++;
		else if (classify_mv_range_type(a) == 'V')
			countV++;
		a++;
	}
	
	cout << "There are " << countM << " mountain ranges and " << countV << " valley ranges between " << intervalA << " and " << b << "." << endl;
}