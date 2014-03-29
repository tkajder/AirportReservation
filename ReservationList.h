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
		this->flight = path;
		start = path->getFlight()->getDeparture();
		//calculatePrice();
		//calculateTime();
		this->next = NULL;
	}

	FlightPath* getFlights(){return this->flight;}

	double getPrice(){return this->price;}
	
	int getTime(){return this->time;}

	Date_Time* getStart() {return this->start;}

	Date_Time* getEnd() {return this->end;}

	int getBags() {return this->numOfBags;}

	ReservationList* Next(){return this->next;}
	
	void setNext(ReservationList* ReservationList) {
		this->next = ReservationList;
	}
	void calculatePrice(){
		if (this->flight == NULL){
			this->price = 0;
			return;
		}else{
			FlightPath* temp = this->flight;
			while (temp->Next() != NULL){
				this->price += (temp->getFlight())->getPrice();
				this->price += (temp->getFlight())->getBaggageFees(this->numOfBags);
				temp = temp->Next();
			}
		}
	}
	void calculateTime(){
		if (this->flight == NULL){
			this->price = 0;
			return;
		}else{
			FlightPath* temp = this->flight;
			while (temp->Next() != NULL){
				this->time += (temp->getFlight())->getDuration();
				temp = temp->Next();
			}
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
