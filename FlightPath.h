#ifndef FLIGHTPATH_H
#define FLIGHTPATH_H
#include "FlightNode.h"
using namespace std;

class FlightPath{
	FlightNode* flight;
	FlightPath* next;
	
	public:
	
	FlightPath(FlightNode* newFlight){
		this->flight = newFlight;
		this->next = NULL;
	}
	HubNode* getDestination(){return this->flight->getDestination();}
	FlightNode* getFlight(){return this->flight;}
	FlightPath* Next(){return this->next;}
	void setNext (FlightPath* next) {
		this->next = next;
	}
};
#endif
