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
	FlightNode* next;
	public:
	
	FlightNode() {};		//default constructor
	
	float getBaggageFees();
	int getDelay();				//for children classes
	string getName();
	
	string getFlightNumber(){return flightNumber;};
	double getPrice(){return price;};
	string getFlightCompany(){return flightCompany;};
	int getDuration(){return duration;};			// accessors
	FlightNode* getSource(){return source;};
	FlightNode* getDestination(){return destination;};
	
	FlightNode* Next() {return next; };		//returns next on singly ll
};

class FlightSouthWest : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 25 * numOfBags;
	}
	int getDelay(){/*stuff*/};
	string getName(){ return "SouthWest";};
};
class FlightDelta : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 0;
	}
	int getDelay(){/*stuff*/};
	string getName(){ return "Delta";};
};
class FlightUSAirway : public FlightNode{
	public:
	float getBaggageFees(int numOfBags){
		return 25 * (numOfBags - 1);
	}
	int getDelay(){/*stuff*/};
	string getName(){ return "US Airway";};
};






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
