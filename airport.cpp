#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
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
void main() {
	HubNode head = new HubNode()

	load_hubs()
	load_flights()
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
