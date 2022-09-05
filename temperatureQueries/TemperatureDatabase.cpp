#include "TemperatureDatabase.h"

#include <fstream>
#include <sstream>
using namespace std;

const int currentYear = 2021;
// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	ifstream ifs;
	ifs.open(filename);
	if(!ifs.is_open())
		cout << "Error: Unable to open " << filename << ".dat" << endl;
	else
	{
	string line;
	while(getline(ifs, line))
	{
		istringstream iss(line);
		string id;
		int year;
		int month;
		double temperature;
		if(!iss.eof())
			iss >> id;
		else
			id = "invalid";
		if(!iss.eof())
		{
			iss >> year;
			if(iss.fail())
				year = -1;
		}
		else
			year = -1;
		if(!iss.eof())
		{
			iss >> month;
			if(iss.fail())
				month = -1;
		}
		else
			month = -1;
		if(!iss.eof())
		{
			iss >> temperature;
			if(iss.fail())
				temperature = -150.0;
		}
		else
			temperature = -150.0;
		
		if(id == "invalid" || year == -1 || month == -1 || temperature == -150.0)
			cout << "Error: Other invalid input" << endl;
		else if((temperature < -50.0 || temperature > 50.0) && temperature != -99.99)
			cout << "Error: Invalid temperature " << temperature << endl;
		else if(year < 1800 || year > currentYear)
			cout << "Error: Invalid year " << year << endl;
		else if(month < 1 || month > 12)
			cout << "Error: Invalid month " << month << endl;
		else if(temperature != -99.99)
			records.insert(id, year, month, temperature);
	}
	}
}

// Do not modify
void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function for part 2
	//  Leave it blank for part 1
}
