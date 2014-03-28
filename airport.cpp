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
		cout << "2) Cancel a Reservation" << endl;
		cout << "3) Print Itinerary" << endl;
		cout << "4) Schedule of all Flights" << endl;
		cout << "5) Quit" << endl;
		cout << "Enter the number for which option you wish to select: ";
		cin >> selection;
		SelectionBranch(selection);
	} while (input != 5);
	
	freeData();
	return 0;
}


void selectionBranch(int selection){	
	
	switch (selection){
	case 1:
		// Make a reservation
		int selectSrc;
		int selectDest;
		string enterDate;
		int numOfBags;
		ReservationList *res;
		char route;

		// gets source hub
		while (selectSrc == NULL){
			cout << "\t\tMake a Reservation" << endl << "-----------------------" << endl;
			cout << "Where are you flying from?";
			printHubs();
			cout << "Enter the number of where you are flying from: ";
			cin >> selectSrc; 
			cout << endl << endl;
		}
		
		// gets destination hub
		while (selectDest == NULL){
			cout << "\t\tMake a Reservation" << endl << "-----------------------" << endl;
			cout << "Where do you want to fly to?";
			printHubs();
			cout << "Enter the number of where you are flying to: ";
			cin >> selectDest;
			cout << endl << endl;
		}
		
		// gets date user want to fly out
		while(){
			cout << "\t\tMake a Reservation" << endl << "-----------------------" << endl;
			cout << "What day would you like to fly out?" << endl << "Enter date (DD/MM/YYYY): ";
			cin >> enterDate;
			cout << endl << endl;
		}

		// gets number of bags
		while (numOfBags == NULL){
			cout << "Enter the number of bags that will be checked: ";
			cin >> numOfBags;
			cout << endl << endl;
		}
		
		getPossibleReservations(/*add stuff*/);
			
		
		// asks for shortest or cheapest reservation
		while (route != q){
			cout << "Would you like the shortest route or the cheapest route" << endl;
			cout << "s: Shortest" << endl;
			cout << "c: Cheapest" << endl;
			cout << "Enter you selection: ";
			cin >> route;
			if (route == 's')
				res = getShortestReservation();
			else if (route == 'c')
				res = getCheapestReservation(res);
			else 
				cout << "Invalid input.  Please enter 's' or 'c'" << endl;
		}
		
		
		printIntinerary(res);
		break;
		
	case 2:
		// Cancel a Reservation
		
		break;
	case 3:
		// Print Itinerary
		if (){
			cout << flightNum << "\t" << company << "\t" << srcLoc << "\t" << Depart_DateTime.toString() << endl << "\t\t" << destLoc << "\t" << Arrive_DateTime.toString() << endl << price << "=" << totalPrice << endl; 
			break;
		}
		else{
			cout << "ERROR: You must make a reservation before you can view your itinerary." << endl << endl;
			break;
		}

	case 4:
		// Print schedule of all flights
		debug();
		break;
	case 5:
		// quit
		cout << endl << endl;
		break;	
	default:
		// if 1, 2, 3, 4, or 5 isn't entered (Invalid entry)
		cout << "ERROR: Invalid selection. Please Try Again." << endl << endl;
		break;
	}
}

void printItinerary(){

	
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

void getPossibleReservations(HubNode* src, HubNode * dest) {
	FlightNode* flight1 = src->getFlights();
	FlightNode* flight2;
	Reservation* reservation;
	while (flight) {
		if (flight->getDestination() == dest) {
			reservation = new Reservation(flight1);
			user->addReservation(reservation);
		}
		flight2 = flight->getDestination()->getFlights()
		if (flight2->getDestination() == dest) {
			reservation = new Reservation(flight1);
			reservation->setNext(new Reservation(flight2)); 
			user->addReservation(reservation);
		}
	}	
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

void printHubs(){
	HubNode* temp = head;
	int counter = 1;
	while (temp->Next() != NULL){
		cout << counter << ": " << temp->getName() << endl; 
		counter++;
		temp = temp->Next();
	}
}

HubNode* getHub(string name) {
	HubNode* current = head;
	while(name != current->getName()) {	//returns the hub location of the hub name passed
		current = current->Next();
		if (!current) {
			cout << name << endl;
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
			cout << "Flight Number: " << flight->getFlightNumber() << endl; 
			cout << "Flight Company: " << flight->getFlightCompany() << endl;
			cout << "Source Airport: " << flight->getSource()->getName() << endl;
			cout << "Destination Airport: " << flight->getDestination()->getName() << endl;
			cout << "Departure Time: " << flight->getDeparture() << endl;
			cout << "Price: " << flight->getPrice() << endl << endl;
			flight = flight->Next();
		}
		current = current->Next();
	}
}
