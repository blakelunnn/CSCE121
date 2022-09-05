#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node(): data(TemperatureData("", 0, 0, 0.0)), next(nullptr) {} // remember to initialize next to nullptr

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature): data(TemperatureData(id, year, month, temperature)), next(nullptr) {}
// remember to initialize next to nullptr

bool Node::operator<(const Node& b) {
	return this->data < b.data;
}
