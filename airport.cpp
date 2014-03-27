ss#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Date_Time.h"
#include "FlightNode.h"

using namespace std;

void debug();
void SelectionBranch(int);
void populateHubs();
void populateFlights();
void freeData();
HubNode* getHub(string);
void printItinerary(string, string, string, string, double, int, double, Date_Time*, Date_Time*);

HubNode* head = new HubNode();

int main(){
	int selection;
	populateHubs();
	populateFlights();
	printIntro();
	
	cout << "Welcome to the Airport Reservation Extravaganza!!" << endl << endl;
	do {
		cout << "\t\t\tMain Menu" << endl << "-----------------------------------------" << endl;
		cout << "1) Make a Reservation" << endl;
		cout << "2) Quit" << endl;
		cout << "Enter the number for which option you wish to select: ";
		cin >> selection;
		SelectionBranch(selection);
	} while (input != "q");
	
	freeData();
	return 0;
}

void freeData() {		//handles memory cleanup after the program is complete
	HubNode *hCurrent, *hTemp;
	FlightNode *fCurrent, *fTemp;
	hCurrent = head;
	while (hCurrent) {	//loops for hubs
		fCurrent = hCurrent->getFlights();	//grabs flights in hub
		while (fCurrent) {		//loops for flights
			fTemp = fCurrent->Next();	//grabs next flight
			delete fCurrent;	//frees current flight
			fCurrent = fTemp;		//moves temp to current flight
		}
		hTemp = hCurrent->Next();
		delete hCurrent;		//deletes hub after all flights are free
		hCurrent = hTemp;
	}
}

void selectionBranch(int selection){	
	
	switch (selection){
	case 1:
		cout << "
		break;
/***************** FIX ***********************/
	case 2:
		if (){
			printItinerary(FlightNum, Company, SourceLocation, DestinationLocation, Price, NumOfBags, TotalPrice, Date, DepartTime, ArriveTime);
			break;
		}
		else{
			cout << "ERROR: You must make a reservation before you can view your itinerary." << endl << endl;
			break;
		}

	case 3:
		cout << endl << endl;
		break;
	default:
		cout << "ERROR: Invalid selection. Please Try Again." << endl << endl;
		break;
	}
}

/***************** FIX ***********************/
void printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice, Date_Time Arrive_DateTime, Date_Time Depart_DateTime){
	TotalPrice = NumOfBags * Price;

	cout << FlightNum << "\t" << Company << "\t" << SourceLocation << "\t" << Depart_DateTime.toString() << endl << "\t\t" << DestinationLocation << "\t" << Arrive_DateTime.toString() << endl << Price << "=" << TotalPrice << endl; 
}

void populateHubs() {
	string line;
	int pos;
	HubNode* current;
	ifstream hub_file;
	hub_file.open("Hub.csv");		//open hub file

	if (!hub_file) {
		throw "File Hub.csv could not be opened.";
	}
		
	// Skip the header labels
	getline(hub_file, line);
		
	// Initialize head hub node
	getline(hub_file, line);
	current = head;			//sets current to head
	pos = line.find(",");		//finds commas in csv
	current->setName(line.substr(0, pos));	//pulls string until comma position
	current->setLocation(line.substr(pos + 1));	//moves position to last pull + 1

	// Initialize rest of hubs
	while (getline(hub_file, line)) {	// loops for line locations
		HubNode* node = new HubNode();	//makes new temp node in heap
		pos = line.find(",");
		node->setName(line.substr(0, pos));	//sets information
		node->setLocation(line.substr(pos + 1));
		current->setNext(node);
		current = node;
	}
}

void populateFlights() {
	string line, flightNumber, flightCompany;
	HubNode *source, *destination;
	double price;
	Date_Time* departure;
	int pos, ppos, duration;
	FlightNode* current;
	ifstream flight_file;
	flight_file.open("Flight.csv");		//open flight file

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
		destination = getHub(line.substr(ppos + 1, pos - ppos - 1));		//this whole area parses information between commas
		ppos = pos;
		pos = line.find(",", pos + 1);
		departure = new Date_Time(line.substr(ppos + 1, pos - ppos - 1));
		ppos = pos;
		pos = line.find(",", pos + 1);
		duration = atoi(line.substr(ppos + 1, pos - ppos - 1).c_str());
		// Account for 'extra' \r character
		flightCompany = line.substr(pos + 1, line.length() - pos - 2);

		if (flightCompany.compare("USAirway") == 0) { 	//disseminates information above into their destination company class
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
	while(name != current->getName()) {	//returns the hub location of the hub name passed
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
}>Next();
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
