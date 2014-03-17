using namespace std;
#include "Date_Time.h"
//#include "HubNode.h"

class FlightNode{		//not the real thing, just here for testing of whatever, I dunno.
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HobNode* source;
	HubNode* destination;
	FlightHub *next;
	public:

	float getBaggageFees();
	int getDelay();
}

class FlightSouthWest : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 25 * numOfBags;
	}
}
class FlightDelta : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 0;
	}
}
class FlightUSAirway : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 25 * (numOfBags - 1);
	}
}






//#include "FlightNode.h"
//using namespace std;

class HubNode {
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights = NULL;
}
