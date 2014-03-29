#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H

using namespace std;

#include <cstring>
#include "FlightPath.h"

class ReservationList{
	FlightPath *flight;
	ReservationList *next;
	double price;
	int time;
	int numOfBags;
	Date_Time* start;
	Date_Time* end;
	
	public:
	ReservationList(FlightPath* path){
		this->numOfBags = 0;
		this->flight = path;
		start = path->getFlight()->getDeparture();
		calculateTime();
		this->next = NULL;
	}

	FlightPath* getFlights(){return this->flight;}

	double getPrice(){return this->price;}
	
	int getTime(){return this->time;}

	Date_Time* getStart() {return this->start;}

	Date_Time* getEnd() {return this->end;}

	int getBagNum(){return this->numOfBags;}
	
	void setBagNum(int numOfBags) {
		this->numOfBags = numOfBags;
		calculatePrice();
	}

	ReservationList* Next(){return this->next;}
	
	void setNext(ReservationList* ReservationList) {
		this->next = ReservationList;
	}
	void calculatePrice() {
		FlightPath* temp;
		this->price = 0;
		if (this->flight == NULL){
			return;
		} else {
			temp = this->flight;
			while (temp){
				this->price += (temp->getFlight())->getPrice();
				cout << this->price << endl;
				this->price += (temp->getFlight())->getBaggageFees(this->numOfBags);
				cout << this->price << endl;
				temp = temp->Next();
			}
		}
	}
	void calculateTime(){
		FlightPath* first;
		FlightPath* temp;
		FlightPath* last;
		this->time = 0;
		if (this->flight == NULL) {
			return;
		} else {
			first = this->flight;
			temp = this->flight;
			while (temp){
				last = temp;
				temp = temp->Next();
			}
			// last arrival - first departure
			cout << "BEGIN: " << first->getFlight()->getDeparture()->toString() << endl;
			cout << "END: " << last->getFlight()->getArrival()->toString() << endl;
		}
	}
	
/*	void addFlightPathNode(ReservationList* ReservationList) {
		ReservationList* curr = this->ReservationListHead;
		if(curr) {
			while(curr->Next()) {
				curr = curr->Next();
			}
			curr->setNext() = ReservationList;
		}
		else {
			this->ReservationListHead = ReservationList;
		}
	}
*/
};

#endif
