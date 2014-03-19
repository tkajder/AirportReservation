#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include "FlightNode.h"
//#include "Date_Time.h"
using namespace std;



void debug();
void printMain();
void populateHubs();
void populateFlights();
HubNode* getHub(string);
void printItinerary(string, string, string, string, double, int, double, Date_Time*, Date_Time*);

HubNode* head = new HubNode();



int main(){
	//do stuff here
	printMain();
	debug(head);
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
	ifstream hub_file("Hub.csv")

	if (!hub_file) {
		throw new Exception("File Hub.csv could not be opened.");
	}
		
	// Skip the header labels
	getline(hub_file, line);
		
	// Initialize head hub node
	getline(hub_file, line);
	current = head;
	pos = line.find(",");
	current->name = line.substr(0, pos)
	current->location = hub_stream.getline(pos + 1);

	// Initialize rest of hubs
	while (getline(hub_file, line)) {
		HubNode* node = new HubNode();
		pos = line.find(",");
		node->name = line.substr(0, pos)
		node->location = hub_stream.getline(pos + 1);
		node->next = NULL;
		current->next = node;
		current = node
	}
}

void populateFlights() {
	string line;
	int pos, ppos;
	FlightNode* current;
	ifstream flight_file("Flight.csv")

	if (!flight_file) {
		throw new Exception("File Flight.csv could not be opened.");
	}
		
	// Skip the header labels
	getline(flight_file, line);

	while (getline(flight_file, line)) {
		current = new FlightNode();

		// Populate FlightNode from line
		ppos = -1;
		pos = line.find(",");
		current->flightNumber = line.substr(ppos + 1, pos);
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->price = line.substr(ppos + 1, pos); // TODO: toDouble
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->source = getHub(line.substr(ppos + 1, pos));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->destination = getHub(line.substr(ppos + 1, pos));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->departure = new DateTime(line.substr(ppos + 1, pos));
		ppos = pos;
		pos = line.find(",", pos + 1);
		current->duration = line.substr(ppos + 1, pos); // TODO: toInt
		current->flightCompany = line.substr(pos + 1);
		current->next = NULL;

		// Add flight to hub
		if (current->source->headFlights) {
			current->next = current->source->headFlights;
			current->source->headFlights = current;
		} else {
			current->source->headFlights = current;
		}
	}
}

HubNode* getHub(string name) {
	HubNode* current = head;
	while(name != current->name) {
		current = current->next;
		if (!current) {
			throw new Exception("Hub not found.");
		}
	}
	return current;
}

void debug(){
	HubNode* current = head;
	while (current != NULL){		//loops for hubs
		FlightNode* flight = current->getFlights();
		while (flight != NULL){		//loops for flight per hub
			HubNode* source = flight->getSource();
			HubNode* dest = flight->getDestination();
			printf("%s : %f : %s : %s : %s\n", flight->getFlightNumber().c_str(), flight->getPrice(), flight->getFlightCompany().c_str(), source->getName().c_str(), dest->getName().c_str());
			flight = flight->Next();
		}
		current = current->Next();
	}
}
