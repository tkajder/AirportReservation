//#include "FlightNode.h"
//using namespace std;

class HubNode {
	string name;
	string location;	 
	HubNode* next;
	FlightNode* headFlights;
	
	public:
	
	HubNode() {};
	HubNode* next() {return next; };
	
	string getName(){return name;};
	string getLocation(){return location;};
	HubNode* Next() { return next;};
	FlightNode* getFlights() { return headFlights;};
};
