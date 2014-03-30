#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Date_Time.h"
#include "FlightNode.h"
#include "User.h"

using namespace std;

ReservationList* getPossibleReservations(HubNode*, HubNode*, Date_Time*);
void debug();
void populateHubs();
void populateFlights();
void freeData();
HubNode* getHub(string);
ReservationList* getCheapestReservation(ReservationList*);
ReservationList* getShortestReservation(ReservationList*);
void printHubs();
HubNode* selectHubs(int);
void selectionBranch(int);
bool isLegal(Date_Time*, Date_Time*);
void debugReservations(ReservationList*,int);

HubNode* head = new HubNode();
User* user = new User();

int main(){
	int selection;
	populateHubs();
	populateFlights();
	
	cout << endl << "Welcome to the Airport Reservation Extravaganza!!" << endl << endl;
	do {
		cout << "\t\t\tMain Menu" << endl << "----------------------------------------------------------" << endl;
		cout << "1) Make a Reservation" << endl;
		cout << "2) Cancel a Reservation" << endl;
		cout << "3) Print Itinerary" << endl;
		cout << "4) Schedule of all Flights" << endl;
		cout << "5) Quit" << endl;
		cout << "Enter the number for which option you wish to select: ";
		cin >> selection;
		if (selection > 0 && selection < 6){
			selectionBranch(selection);
		}
		else{
			cout << "ERROR: Invalid entry.  Please enter an integer." << endl << endl;
		}
	} while (selection != 5);
	
	freeData();
	return 0;
}

void selectionBranch(int selection){
	int selectSrc = -1;
	int selectDest = -1;
	string enterDate = "";
	int numOfBags = -1;
	ReservationList *res;
	ReservationList *posRes;
	char route;
	Date_Time *departDate;
	int pos;
	int ppos = -1;
	int day, month, year;
	HubNode* src;
	HubNode* dest;
	
	switch (selection){
	case 1:
		// gets source hub
		while (selectSrc == -1){
			cout << endl << "\t\tMake a Reservation" << endl << "----------------------------------------------------------" << endl;
			cout << "Where are you flying from?" << endl;
			printHubs();
			cout << "Enter the number of where you are flying from: ";
			cin >> selectSrc; 
			cout << endl;
			if (selectSrc >= 1 && selectSrc <= 15){
				src = selectHubs(selectSrc);
			}
			else{
				cout << "ERROR: Invalid entry. Please enter an integer between 1 and 14 corresponding to the Hub you wish to fly from." << endl;
				selectSrc = -1;
			} 
		}
		
		// gets destination hub
		while (selectDest == -1){
			cout << "\t\tMake a Reservation" << endl << "----------------------------------------------------------" << endl;
			cout << "Where do you want to fly to?" << endl;
			printHubs();
			cout << "Enter the number of where you are flying to: ";
			cin >> selectDest;
			cout << endl;
			if (selectDest >= 1 && selectDest <= 15){
				dest = selectHubs(selectDest);
			}
			else{
				cout << "ERROR: Invalid entry. Please enter an integer between 1 and 14 corresponding to the Hub you wish to fly to." << endl;
				selectDest = -1;
			}
		}
		
		// gets date user want to fly out
		while(enterDate == ""){
			try{
				cout << "\t\tMake a Reservation" << endl << "----------------------------------------------------------" << endl;
				cout << "What day would you like to fly out?" << endl << "Enter date (DD/MM/YYYY): ";
				cin >> enterDate;
				cout << endl << endl;
				// parse
				pos = enterDate.find("/");
				day = atoi(enterDate.substr(ppos + 1, pos).c_str());
				ppos = pos;
				pos = enterDate.find("/", ppos + 1);
				month = atoi(enterDate.substr(ppos + 1, pos).c_str());
				year = atoi(enterDate.substr(pos + 1).c_str());
			
				// new Date_Time
				departDate = new Date_Time();
				departDate->setDate_Time(month, day, year, 0, 0);
			}
			catch(...){
				cout << "Invalid input.  Please enter date as DD/MM/YYYY" << endl << endl;
				enterDate = ""; 
				pos = 0;
				ppos = -1;
			}
		}

		// gets number of bags
		while (numOfBags == -1){
			cout << "Enter the number of bags that will be checked: ";
			cin >> numOfBags;
			if (!(numOfBags >= 0)){
				cout << "Error: Invalid entry. Please enter an integer";
				numOfBags = -1;
			}
			cout << endl << endl;
		}

		posRes = getPossibleReservations(src, dest, departDate);	
		debugReservations(posRes, numOfBags);

		// asks for shortest or cheapest reservation
		while (route != 'q'){
			cout << "Would you like the shortest route or the cheapest route" << endl;
			cout << "s: Shortest" << endl;
			cout << "c: Cheapest" << endl;
			cout << "Enter you selection: ";
			cin >> route;
			if (route == 's'){
				res = getShortestReservation(posRes);
				res->setBagNum(numOfBags);
				user->setReservation(res);
				break;
			} else if (route == 'c'){
				res = getCheapestReservation(posRes);
				res->setBagNum(numOfBags);
				user->setReservation(res);
				break;
			} else{
				cout << "Invalid input.  Please enter 's' or 'c'" << endl;
			}
		}
		cout << endl;
		user->printItinerary();
		break;
		
	case 2:
		// Cancel a Reservation
		if (user->getReservationHead()){
			user->setReservation(NULL);
			cout << endl << "Your reservation has been cancelled." << endl << endl;
		}
		else{
			cout << endl << "Reservation not found." << endl;
		}
		break;
		
	case 3:
		if (user->getReservationHead()){
			cout << endl;
			user->printItinerary();
		}
		else{
			cout << endl << "Itinerary not found." << endl << endl;
		}
		break;

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
			cheapest = reservation;
			reservation = reservation->Next();
			cheapest->setNext(NULL);
		} else {
			temp = reservation;
			reservation = reservation->Next();
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
		if (reservation->getTime() < shortest->getTime()) {
			shortest = reservation;
			reservation = reservation->Next();
			shortest->setNext(NULL);
		} else {
			temp = reservation;
			reservation = reservation->Next();
		}
	}
	return shortest;
}

ReservationList* getPossibleReservations(HubNode* src, HubNode* dest, Date_Time* start){
	FlightNode* flight1 = src->getFlights();
	FlightNode* flight2;
	FlightPath* path;
	ReservationList* head = NULL;
	ReservationList* current = NULL;
	ReservationList* reservation;
	while (flight1) {
		if (flight1->getDestination() == dest && start->lessThan(flight1->getDeparture())) {
			path = new FlightPath(flight1);
			reservation = new ReservationList(path);
			if (current) {
				current->setNext(reservation);
				current = reservation;
			} else {
				head = reservation;
				current = reservation;
			}
		}

		flight2 = flight1->getDestination()->getFlights();
		while (flight2) {
			if (flight2->getDestination() == dest && flight1->getArrival()->lessThan(flight2->getDeparture())){
				path = new FlightPath(flight1);
				path->setNext(new FlightPath(flight2));
				reservation = new ReservationList(path);
				if (current) {
					current->setNext(reservation);
					current = reservation;
				} else {
					head = reservation;
					current = reservation;
				}
			}
			flight2 = flight2->Next();
		}
		flight1 = flight1->Next();
	}
	return head;	
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
	current->setLocation(line.substr(pos + 1, (line.length() - pos - 2)));	//moves position to last pull + 1

	// Initialize rest of hubs
	while (getline(hub_file, line)) {	// loops for line locations
		HubNode* node = new HubNode();	//makes new temp node in heap
		pos = line.find(",");
		node->setName(line.substr(0, pos));	//sets information
		node->setLocation(line.substr(pos + 1, (line.length() - pos - 2))); //Accounts for \r
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
	while (temp){
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
			cout << "Departure Time: " << flight->getDeparture()->toString() << endl;
			cout << "Price: " << flight->getPrice() << endl << endl;
			flight = flight->Next();
		}
		current = current->Next();
	}
}

void debugReservations(ReservationList* res, int numOfBags) {
	FlightPath* path;
	while (res) {
		cout << "Reservation" << endl;
		res->setBagNum(numOfBags);
		path = res->getFlights();
		while (path) {
			cout << "Flight Number: " << path->getFlight()->getFlightNumber() << endl;
			cout << "Source: " << path->getFlight()->getSource()->getName() << endl;
			cout << "Destination: " << path->getDestination()->getName() << endl;
			cout << "Departure: " << path->getFlight()->getDeparture()->toString() << endl;
			cout << "Arrival: " << path->getFlight()->getArrival()->toString() << endl;
			path = path->Next();
		}
		cout << endl << "Total Price: " << res->getPrice() << endl;	
		cout << "Total Time: " << res->getTime() << endl << endl;
		res = res->Next();
	}
}
