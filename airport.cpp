#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include "hubNode.h"
//#include "flightNode.h"
using namespace std;


/*

class HubNode {
	string name;
	string location;	 
	HubNode* next = NULL;
	FlightNode* headFlights = NULL;
}

class FlightNode{		//not the real thing, just here for testing of whatever, I dunno.
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HobNode* source;
	HubNode* destination;
	FlightHub *next;
}

class Date_Time{
	short int minutes;
	short int hours;
	short int day;
	short int month;
	short int year;
}


*/
void main(){
	//do stuff here
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