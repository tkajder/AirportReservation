using namespace std;
#include "Date_Time.h"
//#include "HubNode.h"

class FlightNode{	
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode *next = NULL;
	public:
	
	FlightNode() {};		//default constructor
	float getBaggageFees();
	int getDelay();
	string getName();
	
	string getFlightNumber(){return flightNumber;};
	double getPrice(){return price;};
	string getflightCompany(){return flightCompany;};
	int getDuration(){return duration;};
	HubNode* getSource(){return source;};
	HubNode* getDestination(){return destination;};
	
	FlightNode* next() {return next; };
};

class FlightSouthWest : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 25 * numOfBags;
	}
	string getName(){ return "SouthWest";};
};
class FlightDelta : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 0;
	}
	string getName(){ return "Delta";};
};
class FlightUSAirway : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 25 * (numOfBags - 1);
	}
	string getName(){ return "US Airway";};
};






//#include "FlightNode.h"
//using namespace std;

class HubNode {
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights = NULL;
	
	public:
	
	HubNode() {};
	HubNode* next() {return next; };
};
