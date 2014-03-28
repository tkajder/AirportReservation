using namespace std;

#ifndef FLIGHTNODE_H
#define FLIGHTNODE_H

#include "HubNode.h"

class FlightNode{	
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time* departure;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode* next = NULL;

	public:
	// Constructor
	FlightNode(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time* departure, int duration) {
		this->flightNumber = flightNumber;
		this->price = price;
		this->source = source;
		this->destination = destination;
		this->departure = departure;
		this->duration = duration;
	}  				
	
	// Destructor
	~FlightNode() {
		delete this->departure;
	}

	// Setters
	void setFlightNumber(string flightNumber) { 
		this->flightNumber = flightNumber;
	};
	void setPrice(double price) {
		this->price = price;
	};
	void setFlightCompany(string flightCompany) {
		this->flightCompany = flightCompany;
	};
	void setDeparture(Date_Time* departure) {
		this->departure = departure;
	};
	void setDuration(int duration) {
		this->duration = duration;
	};
	void setSource(HubNode* source) {
		this->source = source;
	};
	void setDestination(HubNode* destination) {
		this->destination = destination;
	};
	void setNext(FlightNode* next) {
		this->next = next;
	};
	
	// Getters
	string getFlightNumber() {
		return flightNumber;
	};
	double getPrice() {
		return price;
	};
	string getFlightCompany() {
		return flightCompany;
	};
	int getDuration() {
		return duration;
	};			
	Date_Time* getDeparture() {
		return departure;
	}
	HubNode* getSource() {
		return source;
	};
	HubNode* getDestination() {
		return destination;
	};
	FlightNode* Next() {
		return next;			// used to indirectly access private variable next
	};
};


//children clases
class FlightSouthWest : public FlightNode {		
	public:
	FlightSouthWest(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time* departure, int duration) : FlightNode(flightNumber, price, source, destination, departure, duration) {	// constructor calls super constructor
		this->setFlightCompany("SouthWest");
	}
	float getBaggageFees(int numOfBags){
		return 25 * numOfBags;
	}
	int getDelay(){
		if (this->departure->getHour() >= 7 && this->departure->getHour() <= 17){
			if (this->departure->getHour() == 17 && this->departure->getMinute() > 0)
				return 0;
			return 30;
		}else{
			return 0;
		}	/*7am - 5pm, 30 minute;  5:01 - 6:59, no delay*/
	};
};
class FlightDelta : public FlightNode {
	public:
	FlightDelta(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time* departure, int duration) : FlightNode(flightNumber, price, source, destination, departure, duration) {	// constructor calls super constructor
		this->setFlightCompany("Delta");
	}
	float getBaggageFees(int numOfBags){
		return 0;
	}
	int getDelay(){
		return 20;
		/*20 minutes always*/
	};
};
class FlightUSAirway : public FlightNode {
	public:
	FlightUSAirway(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time* departure, int duration) : FlightNode(flightNumber, price, source, destination, departure, duration) {	// constructor calls super constructor
		this->setFlightCompany("USAirway");
	}
	float getBaggageFees(int numOfBags){
		return 25 * (numOfBags - 1);
	}
	int getDelay(){
		if (this->departure->getHour() >= 7 && this->departure->getHour() <= 17({
			if (this->departure->getHour() == 17 && this->departure->getMinute() > 0)
				return 15;
			return 10;
		}else if(this->departure->getHour() >= 17 && this->departure->getHour() <= 24 || this->departure->getHour() >= 0 && this->departure->getHour() <= 1){
			if (this->departure->getHour() == 1 && this->departure->getMinute() > 0)
				return 0;
			return 15;
		}else{
			return 0;
		}
		
		/*7am -> 5pm, 10 minutes.  5:01 -> 1am, 15 mins.  1:01am->6:59am (no delay)*/
	};
};

#endif




