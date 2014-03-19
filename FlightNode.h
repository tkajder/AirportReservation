using namespace std;

#ifndef FLIGHTNODE_H
#define FLIGHTNODE_H

//#include "Date_Time.h"
#include "HubNode.h"

class FlightNode{	
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode* next = NULL;
	
	public:
	FlightNode(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time departure, int duration) {
		this->setFlightNumber(flightNumber);
		this->setPrice(price);
		this->setSource(source);
		this->setDestination(destination);
		this->setDeparture(departure);
		this->setDuration(duration);
	}  	//constructor

	// I don't think a parent declaration is necessary
	//for children classes
	//float getBaggageFees();
	//int getDelay();				
	
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
	void setDeparture(Date_Time departure) {
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
	Date_Time getDeparture() {
		return departure;
	}
	HubNode* getSource() {
		return source;
	};
	HubNode* getDestination() {
		return destination;
	};
	FlightNode* Next() {
		return next;			//used to indirectly access private variable next
	};
};


//children clases
class FlightSouthWest : public FlightNode {		
	public:
	FlightSouthWest(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time departure, int duration) : FlightNode(flightNumber, price, source, destination, departure, duration) {	//constructor
		this->setFlightCompany("SouthWest");
	}
	float getBaggageFees(int numOfBags){
		return 25 * numOfBags;
	}
	int getDelay(){/*stuff*/};
};
class FlightDelta : public FlightNode {
	public:
	FlightDelta(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time departure, int duration) : FlightNode(flightNumber, price, source, destination, departure, duration) {	//constructor
		this->setFlightCompany("Delta");
	}
	float getBaggageFees(int numOfBags){
		return 0;
	}
	int getDelay(){/*stuff*/};
};
class FlightUSAirway : public FlightNode {
	public:
	FlightUSAirway(string flightNumber, double price, HubNode* source, HubNode* destination, Date_Time departure, int duration) : FlightNode(flightNumber, price, source, destination, departure, duration) {	//constructor
		this->setFlightCompany("USAirway");
	}
	float getBaggageFees(int numOfBags){
		return 25 * (numOfBags - 1);
	}
	int getDelay(){/*stuff*/};
};

#endif




