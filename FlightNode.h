using namespace std;

#ifndef FLIGHTNODE_H
#define FLIGHTNODE_H

#include "Date_Time.h"
#include "HubNode.h"

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
	HubNode* getSource() {
		return source;
	};
	HubNode* getDestination() {
		return destination;
	};
	FlightNode* Next() {
		return next;
	};
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




