#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "FlightNode.h"
#include "Date_Time.h"
using namespace std;

void debug();
void printMain();
void populateHubs();
void populateFlights();
HubNode* getHub(string);
void printItinerary(string, string, string, string, double, int, double, Date_Time*, Date_Time*);

HubNode* head = new HubNode();

int main(){
	populateHubs();
	populateFlights();
	//do stuff here
	printMain();
	debug();
	return 0;
}



void printMain(){	
		printf("Welcome to the Airport Reservation Extravaganza!!\n\n");
		printf("Please select from the following options:\n");
}

void printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice, Date_Time* Arrive_DateTime, Date_Time* Depart_DateTime){
	TotalPrice = NumOfBags * Price;

	printf("%s\t%s\t%s\t%s\n\t\t%s\t%s\n%f=%f",FlightNum.c_str(), Company.c_str(), SourceLocation.c_str(), Depart_DateTime->toString().c_str(), DestinationLocation.c_str(), Arrive_DateTime->toString().c_str(), Price, TotalPrice); 
}

void populateHubs() {
	string line;
	int pos;
	HubNode* current;
	ifstream hub_file;
	hub_file.open("Hub.csv");

	if (!hub_file) {
		throw "File Hub.csv could not be opened.";
	}
		
	// Skip the header labels
	getline(hub_file, line);
		
	// Initialize head hub node
	getline(hub_file, line);
	current = head;
	pos = line.find(",");
	current->setName(line.substr(0, pos));
	current->setLocation(line.substr(pos + 1));

	// Initialize rest of hubs
	while (getline(hub_file, line)) {
		HubNode* node = new HubNode();
		pos = line.find(",");
		node->setName(line.substr(0, pos));
		node->setLocation(line.substr(pos + 1));
		node->setNext(NULL);
		current->setNext(node);
		current = node;
	}
}

void populateFlights() {
	string line;
	int pos, ppos;
	FlightNode* current;
	ifstream flight_file;
	flight_file.open("Flight.csv");

	if (!flight_file) {
		throw "File Flight.csv could not be opened.";
	}
		
	// Skip the header labels
	getline(flight_file, line);

	while (getline(flight_file, line)) {
		current = new FlightNode();
		// Populate FlightNode from line
		ppos = -1;
		pos = line.find(",");
		current->setFlightNumber(line.substr(ppos + 1, pos));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->setPrice(atof(line.substr(ppos + 1, pos - ppos - 1).c_str()));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->setSource(getHub(line.substr(ppos + 1, pos - ppos - 1)));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->setDestination(getHub(line.substr(ppos + 1, pos - ppos - 1)));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->setDeparture(Date_Time(line.substr(ppos + 1, pos - ppos - 1)));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->setDuration(atoi(line.substr(ppos + 1, pos - ppos - 1).c_str()));
		current->setFlightCompany(line.substr(pos + 1));
		current->setNext(NULL);

		// Add flight to hub
		if (current->getSource()->getFlights()) {
			current->setNext(current->getSource()->getFlights());
		}
		current->getSource()->setHeadFlights(current);
	}
}

HubNode* getHub(string name) {
	HubNode* current = head;
	while(name != current->getName()) {
		current = current->Next();
		if (!current) {
			printf(name.c_str());
			throw "Hub not found.";
		}
	}
	return current;
}

void debug(){
	HubNode* current = head;
	while (current != NULL){		//loops for hubs
		FlightNode* flight = current->getFlights();
		while (flight != NULL){		//loops for flight per hub
			printf("Flight Number: %s\nPrice: %f\nFlight Company: %s\nSource Airport: %s\nDestination Airport: %s\n\n", flight->getFlightNumber().c_str(), flight->getPrice(), flight->getFlightCompany().c_str(), flight->getSource()->getName().c_str(), flight->getDestination()->getName().c_str());
			flight = flight->Next();
		}
		current = current->Next();
	}
}
