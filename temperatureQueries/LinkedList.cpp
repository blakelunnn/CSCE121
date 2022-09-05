#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList(): head(nullptr), tail(nullptr) {}

LinkedList::~LinkedList()
{
	this->clear();
}

LinkedList::LinkedList(const LinkedList& source)
{
	Node* tempNode = source.head;
	Node* tempTail = nullptr;
	while(tempNode != nullptr)
	{
		Node* node = new Node(*tempNode);
		if(head == nullptr)
			head = node;
		else if(tempTail != nullptr)
			tempTail->next = node;
		
		tempNode = tempNode->next;
		tempTail = node;
	}
	
	tail = tempTail;
}

LinkedList& LinkedList::operator=(const LinkedList& source)
{
	if(this != &source)
	{
		Node* tempNode = source.head;
		Node* tempTail = nullptr;
		while(tempNode != nullptr)
		{
			Node* node = new Node(*tempNode);
			if(head == nullptr)
				head = node;
			else if(tempTail != nullptr)
				tempTail->next = node;
			
			tempNode = tempNode->next;
			tempTail = node;
		}
	
		tail = tempTail;
	}
	
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature)
{
	Node* node = new Node(location, year, month, temperature);
	bool done = false;
	// no nodes exist yet, set first node
	if(head == nullptr && tail == nullptr)
	{
		node->next = nullptr;
		head = node;
		tail = node;
		cout << "empty list" << endl;
		done = true;
	}
	Node* currentNode = head;
	int index = 0;
	while(!done)
	{
		if(node->data < currentNode->data) // check if new node is less than nodes starting from first node
		{
			if(currentNode == head) // if first check, new node becomes first
			{
				node->next = head;
				if(head == tail)
				{
					currentNode->next = nullptr;
					tail = currentNode;
				}
				head = node;
				cout << "head node" << endl;
				done = true;
			}
			else if(index >= 2)
			{
				Node* temp = head;
				for(int x = 0; x < index - 1; x++) // only goes here if the spot for new node hasn't been found and there's more then 2 nodes
					temp = temp->next; // keep going until gets to the spot that needs to point to the new node
				node->next = temp->next; // sets pointer of new node to point to node after the spot it's being placed into
				temp->next = node; // sets the pointer of the node before the new node to point to the new node
				cout << "body node with index: " << index << endl;
				done = true;
			}
			else if(currentNode->next == nullptr) // if node wasn't greater than any node, put it as the tail node
			{
				node->next = nullptr;
				currentNode->next = node;
				tail = node;
				cout << "put node at the end" << endl;
				done = true;
			}
		}
		else if(currentNode->next == nullptr) // if node wasn't greater than any node, put it as the tail node
		{
			node->next = nullptr;
			currentNode->next = node;
			tail = node;
			cout << "put node at the end" << endl;
			done = true;
		}
		else // if spot wasn't found, move check to the next node
		{
			index++;
			currentNode = currentNode->next;
		}
	}
}

void LinkedList::clear()
{
	Node* tempNode = head;
	while(tempNode != nullptr)
	{
		Node* nodeToDelete = tempNode;
		tempNode = head->next;
		delete nodeToDelete;
	}
	head = nullptr;
	tail = nullptr;
	delete tempNode;
}

Node* LinkedList::getHead() const
{
	return head;
}

string LinkedList::print() const
{
	string outputString;
	ostringstream oss;
	Node* tempNode = head;
	while(tempNode != nullptr)
	{
		oss << tempNode->data.id << " ";
		oss << tempNode->data.year << " ";
		oss << tempNode->data.month << " ";
		oss << tempNode->data.temperature << endl;
		tempNode = tempNode->next;
	}
	outputString = oss.str();
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
