#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "HubNode.h"
#include "FlightNode.h"
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
