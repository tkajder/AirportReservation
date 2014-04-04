#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Date_Time.h"
#include "FlightNode.h"
#include "User.h"

using namespace std;

//Forward Declares
ReservationList* getPossibleReservations(HubNode*, HubNode*, Date_Time*, Date_Time*);
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
void debugPhoenixToLA();
void debugPhoenixToHonolulu();

HubNode* head = new HubNode();
User* user = new User();

int main(){
	int selection;
	populateHubs();		//populates hubs and flights
	populateFlights();
	
	cout << endl << "Welcome to the Airport Reservation Extravaganza!!" << endl << endl;
	do {		//main menu
		cout << "----------------------------------------------------------" << endl;
		cout << "\t\t\tMain Menu" << endl << "----------------------------------------------------------" << endl;
		cout << "1) Make a Reservation" << endl;
		cout << "2) Cancel a Reservation" << endl;
		cout << "3) Print Itinerary" << endl;
		cout << "4) Schedule of all Flights" << endl;
		cout << "5) Debug Phoenix to Los Angeles" << endl;
		cout << "6) Debug Phoenix to Honolulu" << endl;
		cout << "7) Quit" << endl;
		cout << "Enter the number for which option you wish to select: ";
		cin >> selection;
		if (selection > 0 && selection < 8){
			selectionBranch(selection);
		}
		else{
			cout << "ERROR: Invalid entry.  Please enter an integer." << endl << endl;
		}
	} while (selection != 7);
	
	freeData();
	return 0;
}

void selectionBranch(int selection){		//secondary menu
	int selectSrc = -1;
	int selectDest = -1;
	string startDate = "";
	string endDate = "";
	int numOfBags = -1;
	ReservationList *res;
	ReservationList *posRes;
	char route;
	char confirm;
	Date_Time *departDate;
	Date_Time *arriveDate;
	int pos;
	int ppos = -1;
	int day, month, year;
	HubNode* src;
	HubNode* dest;
	
	switch (selection){
	case 1:
		// gets source hub
		while (selectSrc == -1){
			cout << endl << "----------------------------------------------------------" << endl;
			cout << "\t\t   Make a Reservation" << endl << "----------------------------------------------------------" << endl;
			cout << "Where are you flying from?" << endl << "---------------------------" << endl;
			printHubs();
			cout << endl << "Enter the number of where you are flying from: ";
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
			cout << "----------------------------------------------------------" << endl;
			cout << "\t\t   Make a Reservation" << endl << "----------------------------------------------------------" << endl;
			cout << "Where do you want to fly to?" << endl << "-----------------------------" << endl;
			printHubs();
			cout << endl << "Enter the number of where you are flying to: ";
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
		while(startDate == ""){
			try{
				pos = 0;
				ppos = -1;
				cout << "----------------------------------------------------------" << endl;				
				cout << "\t\t   Make a Reservation" << endl << "----------------------------------------------------------" << endl;
				cout << "What is the eariest date you would like to depart?" << endl << "Enter date (DD/MM/YYYY): ";
				cin >> startDate;
				cout << endl;
				// parse
				pos = startDate.find("/");
				month = atoi(startDate.substr(ppos + 1, pos).c_str());	//atoi used to convert string to int
				ppos = pos;
				pos = startDate.find("/", ppos + 1);
				day = atoi(startDate.substr(ppos + 1, pos).c_str());
				year = atoi(startDate.substr(pos + 1).c_str());
			
				// new Date_Time
				departDate = new Date_Time();
				departDate->setDate_Time(month, day, year, 0, 0);
			}
			catch(...){		//catch all 
				cout << "Invalid input.  Please enter date as MM/DD/YYYY" << endl << endl;
				startDate = ""; 
			}
		}
		
		// gets date user wants to arrive
		while(endDate == ""){
			try{
				pos = 0;
				ppos = -1;
				cout << "What is the latest date that you would like to arrive?" << endl << "Enter date (DD/MM/YYYY): ";
				cin >> endDate;
				cout << endl;
				// parse
				pos = endDate.find("/");
				month = atoi(endDate.substr(ppos + 1, pos).c_str());
				ppos = pos;
				pos = endDate.find("/", ppos + 1);
				day = atoi(endDate.substr(ppos + 1, pos).c_str());
				year = atoi(endDate.substr(pos + 1).c_str());
			
				// new Date_Time
				arriveDate = new Date_Time();
				arriveDate->setDate_Time(month, day, year, 23, 59);
			}
			catch(...){
				cout << "Invalid input.  Please enter date as DD/MM/YYYY" << endl << endl;
				endDate = ""; 	//to ensure it continues looping
			}
		}
		
		// gets number of bags
		while (numOfBags == -1){
			cout << "Enter the number of bags that will be checked: ";
			cin >> numOfBags;
			if (!(numOfBags >= 0)){
				cout << "Error: Invalid entry. Please enter an integer";
				numOfBags = -1;		//to continue loop
			}
			cout << endl;
		}
	
		posRes = getPossibleReservations(src, dest, departDate, arriveDate);	

		if (!posRes) {
			cout << "No reservations found for specified airports and times." << endl << endl;
			break;
		}
		cout << "----------------------------------------------------------" << endl;
		cout << "\t\t   Available Reservations" << endl << "----------------------------------------------------------" << endl;
		debugReservations(posRes, numOfBags);

		// asks for shortest or cheapest reservation
		while (route != 's' || route != 'c'){
			cout << "Would you like the shortest route or the cheapest route" << endl;
			cout << "s: Shortest" << endl;
			cout << "c: Cheapest" << endl;
			cout << "Enter you selection: ";
			cin >> route;
			if (route == 's'){
				res = getShortestReservation(posRes);	//grabs shortest reservation
				res->setBagNum(numOfBags);		//sets number of bags
				cout << endl << endl;
				cout << "----------------------------------------------------------" << endl;
				cout << "\t\tShortest Route Reservation" << endl << "----------------------------------------------------------" << endl;
				break;
			} else if (route == 'c'){
				res = getCheapestReservation(posRes);
				res->setBagNum(numOfBags);
				cout << endl << endl;
				cout << "----------------------------------------------------------" << endl;
				cout << "\t\tCheapest Route Reservation" << endl << "----------------------------------------------------------" << endl;
				break;
			} 
			else{
				cout << "Invalid input.  Please enter 's' or 'c'" << endl;
			}
		}
		
		while (confirm != 'y' || confirm != 'n'){		
			debugReservations(res, numOfBags);
			cout << "Would you like to book this flight?" << endl << "y: YES" << endl << "n: NO" << endl << "Enter selection: ";
			cin >> confirm;
			cout << endl;
			if (confirm == 'y'){
				user->setReservation(res);	// adds reservation to user
				cout << "--------------------------------------------------------------------------------" << endl;
				cout << "\t\t\t\tConfirmation" << endl << "--------------------------------------------------------------------------------" << endl;
				user->printItinerary();		//print users itinerary
				break;
			}
			else if (confirm == 'n'){
				cout << "Reservation not booked" << endl << endl;
				break;
			}
			else{
				cout << "ERROR: Invalid input.";
			}
		}
		break;
		
	case 2:
		// Cancel a Reservation
		if (user->getReservationHead()){
			user->setReservation(NULL);		//sets users reservation head to null (works with 1 reservation)
			cout << endl << "Your reservation has been cancelled." << endl << endl;
		}
		else{
			cout << endl << "Reservation not found." << endl;
		}
		break;
		
	case 3:
		//print itinerary
		if (user->getReservationHead()){
			cout << endl;
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t\tBooked Flight" << endl << "--------------------------------------------------------------------------------" << endl;
			user->printItinerary();
		}
		else{
			cout << endl << "Itinerary not found." << endl << endl;
		}
		break;

	case 4:
		// Print schedule of all flights
		cout << endl << "----------------------------------------------------------" << endl;
		cout << "\t\t  Schedule of Flights" << endl << "----------------------------------------------------------" << endl;
		debug();
		break;
		
	case 5:
		//debug phoenix to la
		debugPhoenixToLA();
		break;
		
	case 6:
		//debug phoenix to honolulu
		debugPhoenixToHonolulu();
		break;	
		
	case 7:
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
	ReservationList* reservationHead;
	FlightPath* path;
	FlightPath* temp;
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
	reservationHead = user->getReservationHead();	//loops for reservations
	if (reservationHead) {
		path = reservationHead->getFlights();
		while (path) {
			temp = path->Next();
			delete path->getFlight();
			delete path;
			path = temp;
		}
		delete reservationHead;
	}
	delete user;		//cleans up user
}

ReservationList* getCheapestReservation(ReservationList* head) {		//grabs cheapest reservation
	ReservationList* reservation = head;
	ReservationList* cheapest = head;
	ReservationList* temp;
	reservation = reservation->Next();
	while (reservation) {		//loops for reservations
		if (reservation->getPrice() < cheapest->getPrice()) {		//checks price against current cheapest
			cheapest = reservation;		//if current is cheaper, sets to cheapest
			reservation = reservation->Next();
			cheapest->setNext(NULL);	//since next is supposed to be NULL
		} else {
			temp = reservation;
			reservation = reservation->Next();
		}
	}
	return cheapest;
}

ReservationList* getShortestReservation(ReservationList* head) {
	ReservationList* reservation = head;
	ReservationList* shortest = head;		//same as above
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

ReservationList* getPossibleReservations(HubNode* src, HubNode* dest, Date_Time* start, Date_Time* end) {
	FlightNode* flight1 = src->getFlights();
	FlightNode* flight2;
	FlightPath* path;
	ReservationList* head = NULL;
	ReservationList* current = NULL;
	ReservationList* reservation;
	while (flight1) {		//loops for flights
		if (flight1->getDestination() == dest && start->lessThan(flight1->getDeparture())) {	//direct flights
			if (flight1->getArrival()->lessThan(end)) {	//ensures time is good
				path = new FlightPath(flight1);
				reservation = new ReservationList(path);
				if (current) {	//if not null
					current->setNext(reservation);
					current = reservation;
				} else {
					head = reservation;	//sets reservation
					current = reservation;
				}
			}
		}

		flight2 = flight1->getDestination()->getFlights();		//second hop
		while (flight2) {
			if (flight2->getDestination() == dest && flight1->getArrival()->lessThan(flight2->getDeparture())){
				if (flight2->getArrival()->lessThan(end)) {
					path = new FlightPath(flight1);
					path->setNext(new FlightPath(flight2));
					reservation = new ReservationList(path);
					if (current) {
						current->setNext(reservation);	//sets second step in the reservation
						current = reservation;
					} else {
						head = reservation;
						current = reservation;
					}
				}
			}
			flight2 = flight2->Next();
		}
		flight1 = flight1->Next();
	}
	return head;//returns head of reservation path.  This will be one or two in length
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

void printHubs(){	//prints out a numbered list of hubs for use in select arrival and departure points
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
	int i = 1;		//selection from a list of hubs
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

void debugReservations(ReservationList* res, int numOfBags) {	//prints out a list of reservations
	FlightPath* path;
	while (res) {		//loop for reservations
		res->setBagNum(numOfBags);		//sets number of bags into the temp reservation object
		path = res->getFlights();		//grabs flights
		while (path) {
			cout << "Flight Number: " << path->getFlight()->getFlightNumber() << endl;
			cout << "Source: " << path->getFlight()->getSource()->getName() << endl;
			cout << "Destination: " << path->getDestination()->getName() << endl;
			cout << "Departure: " << path->getFlight()->getDeparture()->toString() << endl;
			cout << "Arrival: " << path->getFlight()->getArrival()->toString() << endl;
			path = path->Next();	//iterate
		}
		cout << endl << "Total Price: " << res->getPrice() << endl;	
		cout << "Total Time: " << res->getTime() << endl << "----------------------------------------------------------" << endl << endl;
		res = res->Next();
	}
}

void debugPhoenixToLA() {	//debugging class 
	char confirm;
	ReservationList* res;
	HubNode* from = getHub("Phoenix Sky Harbor International Airport");
	HubNode* to = getHub("Los Angeles International Airport");		//sets airports
	Date_Time* start = new Date_Time();
	Date_Time* end = new Date_Time();		//instantiate times
	int numOfBags = 3;
	end->setDate_Time(12,18,2013,23,59);		//set dates
	start->setDate_Time(12,16,2013,0,0);

	res = getPossibleReservations(from, to, start, end);		//grabs path
	res = getCheapestReservation(res);
	res->setBagNum(numOfBags);
	
	while (confirm != 'y' || confirm != 'n'){		
		cout << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "\t\t   Available Reservations" << endl << "----------------------------------------------------------" << endl;
		debugReservations(res, numOfBags);
		cout << "Would you like to book this flight?" << endl << "y: YES" << endl << "n: NO" << endl << "Enter selection: ";
		cin >> confirm;
		cout << endl;
		if (confirm == 'y'){
			user->setReservation(res);	// adds reservation to user
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t\tConfirmation" << endl << "--------------------------------------------------------------------------------" << endl;
			user->printItinerary();		//print users itinerary
			break;
		}
		else if (confirm == 'n'){
			cout << "Reservation not booked" << endl << endl;
			break;
		}
		else{
			cout << "ERROR: Invalid input.";
		}
	}
}

void debugPhoenixToHonolulu() {
	char confirm;
	ReservationList* res;
	HubNode* from = getHub("Phoenix Sky Harbor International Airport");
	HubNode* to = getHub("Honolulu International Airport");
	Date_Time* start = new Date_Time();
	Date_Time* end = new Date_Time();
	int numOfBags = 5;
	end->setDate_Time(12,19,2013,23,59);
	start->setDate_Time(12,16,2013,0,0);

	res = getPossibleReservations(from, to, start, end);
	res = getShortestReservation(res);
	res->setBagNum(numOfBags);

	while (confirm != 'y' || confirm != 'n'){		
		cout << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "\t\t   Available Reservations" << endl << "----------------------------------------------------------" << endl;
		debugReservations(res, numOfBags);
		cout << "Would you like to book this flight?" << endl << "y: YES" << endl << "n: NO" << endl << "Enter selection: ";
		cin >> confirm;
		cout << endl;
		if (confirm == 'y'){
			user->setReservation(res);	// adds reservation to user
			cout << "--------------------------------------------------------------------------------" << endl;
			cout << "\t\t\t\tConfirmation" << endl << "--------------------------------------------------------------------------------" << endl;
			user->printItinerary();			//print users itinerary
			break;
		}
		else if (confirm == 'n'){
			cout << "Reservation not booked" << endl << endl;
			break;
		}
		else{
			cout << "ERROR: Invalid input.";
		}
	}
}
