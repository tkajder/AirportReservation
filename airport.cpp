#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Date_Time.h"
#include "FlightNode.h"
#include "User.h"

using namespace std;

ReservationList* getPossibleReservations(HubNode*, HubNode*);
void debug();
void printIntro();
void populateHubs();
void populateFlights();
void freeData();
HubNode* getHub(string);
ReservationList* getCheapestReservation(ReservationList*);
ReservationList* getShortestReservation(ReservationList*);
void printItinerary(string, string, string, string, double, int, double, Date_Time*, Date_Time*);
void printHubs();

HubNode* head = new HubNode();
User* user = new User();

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
	} while (selection != 5);
	
	freeData();
	return 0;
}

void selectionBranch(int selection){	
	int selectSrc;
	int selectDest;
	string enterDate;
	int numOfBags;
	ReservationList *res;
	ReservationList *posRes;
	char route;
	Date_Time *departDate;
	int pos, ppos;
	int day, month, year;
	HubNode* src;
	HubNode* dest;
	
	switch (selection){
	case 1:
		// gets source hub
		while (selectSrc == NULL){
			cout << "\t\tMake a Reservation" << endl << "-----------------------" << endl;
			cout << "Where are you flying from?";
			printHubs();
			cout << "Enter the number of where you are flying from: ";
			cin >> selectSrc; 
			cout << endl << endl;
			src = selectHubs(selectSrc);
		}
		
		// gets destination hub
		while (selectDest == NULL){
			cout << "\t\tMake a Reservation" << endl << "-----------------------" << endl;
			cout << "Where do you want to fly to?";
			printHubs();
			cout << "Enter the number of where you are flying to: ";
			cin >> selectDest;
			cout << endl << endl;
			dest = selectHubs(selectDest);
		}
		
		// gets date user want to fly out
		while(enterDate == NULL){
			try{
				cout << "\t\tMake a Reservation" << endl << "-----------------------" << endl;
				cout << "What day would you like to fly out?" << endl << "Enter date (DD/MM/YYYY): ";
				cin >> enterDate;
				cout << endl << endl;
				
				// parse
				pos = input.find("/");
				day = atoi(input.substr(ppos + 1, pos).c_str());
				ppos = pos;
				pos = input.find("/");
				month = atoi(input.substr(ppos + 1, pos).c_str());
				year = atoi(input.substr(pos + 1).c_str());
				
				// new Date_Time
				departDate = new Date_Time();
				departDate->setDays(day);
				departDate->setMonths(month);
				departDate->setYears(year);
			}
			catch(int ex){
				departDate = NULL;
				cout << "Invalid input.  Please enter date as DD/MM/YYYY";
			}
		}

		// gets number of bags
		while (numOfBags == NULL){
			cout << "Enter the number of bags that will be checked: ";
			cin >> numOfBags;
			cout << endl << endl;
		}
		
		posRes = getPossibleReservations(src, dest, departureDate);
		
		// asks for shortest or cheapest reservation
		while (route != q){
			cout << "Would you like the shortest route or the cheapest route" << endl;
			cout << "s: Shortest" << endl;
			cout << "c: Cheapest" << endl;
			cout << "Enter you selection: ";
			cin >> route;
			if (route == 's'){
				res = getShortestReservation(posRes);
			}else if (route == 'c'){
				res = getCheapestReservation(posRes);
			}else{
				cout << "Invalid input.  Please enter 's' or 'c'" << endl;
			}
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

void printItinerary(ReservationList *res){
	FlightPath* flight = res->getFlights()->getFlight();
	
	while (flight) {
	cout << flight->getFlightNumber() << "\t" << flight->getFlightCompany << "\t" << flight->getSource() << "\t" << flight->getDeparture << endl;
	cout << "\t\t" << flight->getDestination() << "\t" << flight->getArrival() << endl;
	cout << "\t\t" << "$" << flight->getPrice() << ".00" << "base price" << " = " << "$" << res->getPrice() << ".00" << endl; 
		flight = flight->Next();
	}
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
	delete user;
}

ReservationList* getCheapestReservation(ReservationList* head) {
	ReservationList* reservation = head;
	ReservationList* cheapest = head;
	ReservationList* temp;
	reservation = reservation->Next();
	while (reservation) {
		if (reservation->getPrice() < cheapest->getPrice()) {
			delete cheapest;
			cheapest = reservation;
			reservation = reservation->Next();
			cheapest->setNext(NULL);
		} else {
			temp = reservation;
			reservation = reservation->Next();
			delete temp;
		}
	}
	return cheapest;
}

ReservationList* getShortestReservation(ReservationList* head) {
	ReservationList* reservation = head;
	ReservationList* shortest = head;
	ReservationList* temp;
	reservation = reservation->Next();
	while (reservation) {
		if (reservation->getTime() < cheapest->getTime()) {
			delete cheapest;
			shortest = reservation;
			reservation = reservation->Next();
			shortest->setNext(NULL);
		} else {
			temp = reservation;
			reservation = reservation->Next();
			delete temp;
		}
	}
	return shortest;
}

ReservationList* getPossibleReservations(HubNode* src, HubNode* dest){
	FlightNode* flight1 = src->getFlights();
	FlightNode* flight2;
	FlightPath* path;
	ReservationList* head = NULL;
	ReservationList* current = NULL;
	ReservationList* reservation;
	while (flight1) {
		if (flight1->getDestination() == dest) {
			path = new FlightPath(flight1);
			reservation = new ReservationList(path);
			if (head) {
				if (current) {
					current->setNext(reservation);
				} else {
					head = reservation;
				}
				current = reservation;
			}
		}

		flight2 = flight->getDestination()->getFlights();
		while (flight2) {
			if (flight2->getDestination() == dest and isLegal(flight1, flight2)){
				path = new FlightPath(flight1);
				path->setNext(flight2);
				reservation = new ReservationList(path);
				if (head) {
					if (current) {
						current->setNext(reservation);
					} else {
						head = reservation;
					}
					current = reservation;
				}
			}
			flight2 = flight2->Next();
		}
		flight1 = flight1->Next();
	}
	return head;	
}

bool isLegal(FlightNode* flight1, FlightNode* flight2){
	if (flight1->getArrival()->getDays() < flight2->getDeparture()->getDays())
		return 1;
	
	
	if (flight1->getArrival()->getDays() == flight2->getDeparture()->getDays())
		if (flight1->getArrival()->getElapsedMinutes() < flight2->getDeparture()->getElapsedMinutes())	//better run
			return 1;
	
	return 0;
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

HubNode* selectHubs(int selection){
	HubNode* temp = head;
	int i = 1;
	while (temp){
		if (i == selection){
			return temp;
		}
		else{
			temp = temp->Next();
			i++;
		}
	}
	throw ("Selection not in Hubs");
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
