<<<<<<< HEAD
#ifndef DATETIME_H
#define DATETIME_H
#include <cmath>
=======
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Date_Time.h"
#include "FlightNode.h"
#include "User.h"
>>>>>>> origin/Tom

using namespace std;
class Date_Time{

	int months; 
	int days;
	int years; 
	int hours;
	int minutes;	// hours should be entered as military time
	public:
	Date_Time() {
		this->months = 0; 
		this->days = 0;
		this->years = 0; 
		this->hours = 0;
		this->minutes = 0;
	};
	
	Date_Time(string input) {
		int pos, ppos;
		ppos = -1;	// trails behind pos
		pos = input.find("/");		//searches for /
		minutes = atoi(input.substr(ppos + 1, pos).c_str()); //places that information into minutes
		ppos = pos;	//moves ppos up
		pos = input.find("/", ppos + 1);
		hours = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/", ppos + 1);
		days = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/", ppos + 1);
		months = atoi(input.substr(ppos + 1, pos).c_str());
		years = atoi(input.substr(pos + 1).c_str());

	}
	
<<<<<<< HEAD
=======
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
>>>>>>> origin/Tom
	
	int getMonths(){return this->months;}
	int getDays(){return this->days;}
	int getYears(){return this->years;}
	int getHours(){return this->hours;}
	int getMinutes(){return this->minutes;}
	
<<<<<<< HEAD
	void setMonths(int input){this->months = input;}
	void setDays(int input){this->days = input;}
	void setYears(int input){this->years = input;}
	void setHours(int input){this->hours = input;}
	void setMinutes(int input){this->minutes = input;}

	void setDate_Time(int mon, int d, int y, int h, int min){
		months = (mon > 0 && mon <= 12) ? mon : throw "Improper month format.\n";
		days = (d >= 0 && d < 31) ? d : throw "Improper day format.\n";
		years	= (y >= 0) ? y : throw "Improper year format.\n";		//formats raw time data into readable 
		hours = (h >= 0 && h < 24) ? h : throw "Improper hour format.\n";
		minutes = (min >= 0 && min < 60) ? min : throw "Improper minutes format.\n";
	}

	void addMinutes(int numOfMin){		//recursion, weeeeeeeeeee
		if (numOfMin <= 0)
			return;
		if (floor(numOfMin/1440) > 0){
			this->days += floor(numOfMin/1440);
			numOfMin -= floor(numOfMin/1440)* 1440;
		}
		if (floor(numOfMin/60) > 0){
			this->hours += floor(numOfMin/60);
			if (this->hours >= 24) {
				this->hours = this->hours % 24;
				this->days += 1;
=======
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
				break;
			}else if (route == 'c'){
				res = getCheapestReservation(posRes);
				res->setBagNum(numOfBags);
				break;
			}else{
				cout << "Invalid input.  Please enter 's' or 'c'" << endl;
>>>>>>> origin/Tom
			}
			numOfMin -= floor(numOfMin/60) * 60;
		}
		this->minutes += numOfMin;
		return;
		
	}
<<<<<<< HEAD
	
	bool lessThan(Date_Time* date){
		if (this->getDays() < date->getDays()) {
			return 1;
		}
	
		if (this->getDays() == date->getDays()) {
			if (this->getElapsedMinutes() < date->getElapsedMinutes()) {
				return 1;
=======
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
>>>>>>> origin/Tom
			}
		}
<<<<<<< HEAD
	
		return 0;
=======
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
>>>>>>> origin/Tom
	}

	Date_Time* getEndTime(int delta){
		Date_Time* ret = new Date_Time();
		ret->setMonths(this->getMonths());
		ret->setDays(this->getDays());
		ret->setYears(this->getYears());
		ret->setHours(this->getHours());
		ret->setMinutes(this->getMinutes()) ;
		ret->addMinutes(delta);
		return ret;			
	}
	
	int getElapsedMinutes(){
		return this->hours * 60 + this->minutes;
	}

	string toString(){
		string dateTime;
		char temp[80];	//creates temp char array to use in sprintg
		if (hours > 10){
			sprintf(temp, "%d/%d/%d  %d : %d", months, days, years, hours, minutes);
			string dateTime(temp);	//converts char array into string
			return dateTime;		//returns string
		}
		else{
			sprintf(temp, "%d/%d/%d 0%d : %d", months, days, years, hours, minutes);
			string dateTime(temp);
			return dateTime;
		}
	}
};

#endif

