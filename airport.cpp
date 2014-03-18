#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include "FlightNode.h"
//#include "Date_Time.h"
using namespace std;



void debug(HubNode*);
void printMain();
void populateHubs(HubNode*);
void populateFlights();
void printItinerary(string, string, string, string, double, int, double, Date_Time*, Date_Time*);

HubNode* hub = NULL;



int main(){
	//do stuff here
	printMain();
	debug(hub);
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

void populateHubs(HubNode*) {
	string line;
	int pos;
	HubNode current;
	ifstream hub_file("Hub.csv")

	if (hub_file) {
		// Skip the header labels
		getline(hub_file, line);
		
		// Initialize head hub node
		getline(hub_file, line);
		current = new HubNode();
		pos = line.find(",");
		current.name = line.substr(0, pos)
		current.location = hub_stream.getline(pos+1);

		while (getline(hub_file, line)) {
			HubNode node = new HubNode();
			pos = line.find(",");
			node.name = line.substr(0, pos)
			node.location = hub_stream.getline(pos+1);
			node.next = NULL;
			current.next = node;
			current = node
		}
	} else {
		cerr << "File Hub.csv could not be opened." << endl
		exit(1)
	}
}

void debug(HubNode* hub){
	HubNode* current = hub;
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
