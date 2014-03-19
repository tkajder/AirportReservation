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
	printMain();
	debug();
	return 0;
}



void printMain(){	
	cout << "Welcome to the Airport Reservation Extravaganza!!" << endl << endl << "Please select from the following options:" << endl;
}

void printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice, Date_Time Arrive_DateTime, Date_Time Depart_DateTime){
	TotalPrice = NumOfBags * Price;

	cout << FlightNum << "\t" << Company << "\t" << SourceLocation << "\t" << Depart_DateTime.toString() << endl << "\t\t" << DestinationLocation << "\t" << Arrive_DateTime.toString() << endl << Price << "=" << TotalPrice << endl; 
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
	string line, flightNumber, flightCompany;
	HubNode *source, *destination;
	double price;
	Date_Time departure;
	int pos, ppos, duration;
	FlightNode* current;
	ifstream flight_file;
	flight_file.open("Flight.csv");

	if (!flight_file) {
		throw "File Flight.csv could not be opened.";
	}
		
	// Skip the header labels
	getline(flight_file, line);

	while (getline(flight_file, line)) {
		// Parse line
		pos = line.find(",");
		flightNumber = line.substr(0, pos);
		ppos = pos;
		pos = line.find(",", pos + 1);
		price = atof(line.substr(ppos + 1, pos - ppos - 1).c_str());
		ppos = pos;
		pos = line.find(",", pos + 1);
		source = getHub(line.substr(ppos + 1, pos - ppos - 1));
		ppos = pos;
		pos = line.find(",", pos + 1);
		destination = getHub(line.substr(ppos + 1, pos - ppos - 1));
		ppos = pos;
		pos = line.find(",", pos + 1);
		departure = Date_Time(line.substr(ppos + 1, pos - ppos - 1));
		ppos = pos;
		pos = line.find(",", pos + 1);
		duration = atoi(line.substr(ppos + 1, pos - ppos - 1).c_str());
		// Account for 'extra' \r character
		flightCompany = line.substr(pos + 1, line.length() - pos - 2);

		if (flightCompany.compare("USAirway") == 0) { 
			current = new FlightUSAirway(flightNumber, price, source, destination, departure, duration);
		} else if (flightCompany.compare("SouthWest") == 0) {
			current = new FlightSouthWest(flightNumber, price, source, destination, departure, duration);
		} else if (flightCompany.compare("Delta") == 0) {
			current = new FlightDelta(flightNumber, price, source, destination, departure, duration);
		} else {
			throw "Invalid airlines company.\n";
		}

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
	while (current != NULL) {		//loops for hubs
		FlightNode* flight = current->getFlights();
		while (flight != NULL) {		//loops for flight per hub
			cout << "Flight Number: " << flight->getFlightNumber() << endl << "Price: " << flight->getPrice() << endl << "Flight Company: " << flight->getFlightCompany() << endl << "Source Airport: " << flight->getSource()->getName() << endl << "Destination Airport: " << flight->getDestination()->getName() << endl << endl;
			flight = flight->Next();
		}
		current = current->Next();
	}
}
