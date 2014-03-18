#include <stdlib.h>
#include <string.h>
#include <iostream>
<<<<<<< HEAD
#include <fstream>
#include "HubNode.h"
#include "FlightNode.h"
=======
#include <cstdio>
#include "Nodes.h"
#include "Date_Time.h"
>>>>>>> origin/mike
using namespace std;


/*


class Date_Time{
	short int minutes;
	short int hours;
	short int day;
	short int month;
	short int year;
}


*/
<<<<<<< HEAD
void main() {
	HubNode head = new HubNode()

	load_hubs()
	load_flights()
=======
void main(){
	//do stuff here
	printMain();
}

void printMain(){	
		printf("Welcome to the Airport Reservation Extravaganza!!\n\n");
		printf("Please select from the following options:\n");
>>>>>>> origin/mike
}

void load_hubs() {
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

<<<<<<< HEAD
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
=======
void printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice){
	TotalPrice = NumOfBags * Price

	printf("%s\t%s\t%s\t%s\n\t\t%s\t%s\n%f=%f",FlightNum, Company, SourceLocation, Depart_DateTime, DestinationLocation, Arrive_DateTime, Price, TotalPrice); 
>>>>>>> origin/mike
}

void load_flights() {
	
}

void debug(hub){
	while (hub != NULL){		//loops for hubs
		FlightNode flight = hub.flights;
		while (flight != NULL){		//loops for flight per hub
			printf("%d : %d : %s : %s : %s\n", flight.flightNumber, flight.price, flight.flightCompany, flight.source.name, flight.destination.name);
			flight = flight.next;
		}
		hub = hub.next;
	}
}
