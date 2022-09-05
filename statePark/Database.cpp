// Class file for Database class

#include "Database.h"

using std::string, std::vector;

// Constructor
// Constructor for Database class
// TODO(student): implement constructor using member initializer list
Database::Database(): stateParkList({}), camperList({})
{}
// Destructor
// DO NOT CHANGE, ALREADY IMPLEMENTED
Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

// Mandatory
// Dynamically creates a new state park and adds it to stateParkList
void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	StatePark* statePark = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(statePark);
}

// Mandatory
// Dynamically creates a new passport and adds it to camperList
void Database::addPassport(string camperName, bool isJuniorPassport) {
	Passport* passport = new Passport(camperName, isJuniorPassport);
	camperList.push_back(passport);
}

// Mandatory
// Searches for a passport and state park whose name matches the given parameters and
// adds the park to the passport
void Database::addParkToPassport(string camperName, string parkName) {
	bool camperExists = false;
	bool stateParkExists = false;
	int indexOfCamper = 0;
	for(long unsigned int x = 0; x < camperList.size(); x++)
		if(camperList[x]->getCamperName() == camperName)
		{
			indexOfCamper = x;
			camperExists = true;
			break;
		}
	
	int indexOfStatePark = 0;
	for(long unsigned int x = 0; x < stateParkList.size(); x++)
		if(stateParkList[x]->getParkName() == parkName)
		{
			indexOfStatePark = x;
			stateParkExists = true;
			break;
		}
	
	if(camperExists && stateParkExists)
		camperList[indexOfCamper]->addParkVisited(stateParkList[indexOfStatePark]);
	
}

// Option A
// Returns a vector of the names of all the parks whose revenue is between the parameters
// given (including the boundaries)
vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)
	// TODO(student): implement function
	return {};
}

// Option B
// Returns a vector of the names of all the campers who have reached at least the hiking
// level given by the parameter
vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)
	// TODO(student): implement function
	return {};
}