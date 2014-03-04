#include "FlightNode.h"

class HubNode {
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights = NULL;
}
