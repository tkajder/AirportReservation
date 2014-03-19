using namespace std;

#ifndef FLIGHTNODE_H
#define FLIGHTNODE_H

#include "Date_Time.h"
#include "HubNode.h"

class FlightNode{	
	public:
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode* next;
	
	FlightNode() {};		//default constructor
	
	float getBaggageFees();
	int getDelay();				//for children classes
	string getName();
	
	string getFlightNumber(){return flightNumber;};
	double getPrice(){return price;};
	string getFlightCompany(){return flightCompany;};
	int getDuration(){return duration;};			// accessors
	HubNode* getSource(){return source;};
	HubNode* getDestination(){return destination;};
	
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

#endif




