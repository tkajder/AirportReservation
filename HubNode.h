#ifndef HUBNODE_H
#define HUBNODE_H

#include "FlightNode.h"
using namespace std;


class FlightNode;
class HubNode {
	string name;
	string location;
	HubNode* next = NULL;
	FlightNode* headFlights;

	public:
	HubNode() {};			//constructor

	// Setters
	void setName(string name) {
		this->name = name;
	}
	void setLocation(string location) {
		this->location = location;
	}
	void setNext(HubNode* next) {
		this->next = next;
	}
	void setHeadFlights(FlightNode* headFlights) {
		this->headFlights = headFlights;
	}

	// Getters
	HubNode* Next() {
		return next;		//used to indirectly access private variable next
	};
	string getName() {
		return name;
	};
	string getLocation() {
		return location;
	};
	FlightNode* getFlights() {
		return headFlights;
	};
};

#endif
