#include "FlightNode.h"
using namespace std;

class HubNode {
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights = NULL;
}
