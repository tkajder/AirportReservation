#ifndef HUBNODE_H
#define HUBNODE_H

#include "FlightNode.h"
using namespace std;


class FlightNode;
class HubNode {
	public:
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights;
	
	HubNode() {};
	HubNode* Next() {return next; };
	
	string getName(){return name;};
	string getLocation(){return location;};
	FlightNode* getFlights() { return headFlights;};
};

#endif
