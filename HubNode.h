//#include "FlightNode.h"
//using namespace std;


class FlightNode;
class HubNode {
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights;
	
	public:
	
	HubNode() {};
	HubNode* Next() {return next; };
	
	string getName(){return name;};
	string getLocation(){return location;};
	FlightNode* getFlights() { return headFlights;};
};
