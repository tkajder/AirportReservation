#ifndef FLIGHTPATH_H
#define FLIGHTPATH_H
#include "FlightNode.h"
using namespace std;

class FlightPath{
	FlightNode* flight= NULL;
	FlightPath* next = NULL;
	
	public:
	
	FlightPath(FlightNode* newFlight){
		this->flight = newFlight;
	}
	HubNode* getDestination(){return this->flight->getDestination();}
	FlightNode* getFlight(){return this->flight;}
	FlightPath* Next(){return this->next;}
	void setNext (FlightPath* FlightPath) {
		this->next = FlightPath;
	}
};
#endif
