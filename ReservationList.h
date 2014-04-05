#ifndef RESERVATIONLIST_H
#define RESERVATIONLIST_H

using namespace std;

#include <cstring>
#include "FlightPath.h"

//This class has the entire path passed in, so we can handle all the calculations at its instanciation

class ReservationList{
	FlightPath *flight;		//flight head (linked list)
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
		start = path->getFlight()->getDeparture();	//grabs date_time of departing flight
		calculateTime();			//calculates total time of trip
		this->next = NULL;
	}
	~ReservationList() {		//destructor
		//delete flight;
		delete next;
		delete start;
		delete end;
	}
	
	FlightPath* getFlights(){return this->flight;}

	double getPrice(){return this->price;}
	
	int getTime(){return this->time;}		//getters

	Date_Time* getStart() {return this->start;}

	Date_Time* getEnd() {return this->end;}

	int getBagNum(){return this->numOfBags;}
	
	void setBagNum(int numOfBags) {
		this->numOfBags = numOfBags;
		calculatePrice();
	}

	ReservationList* Next(){return this->next;}
	
	void setNext(ReservationList* ReservationList) {		//setters
		this->next = ReservationList;
	}
	void calculatePrice() {
		FlightPath* temp;
		this->price = 0;
		if (this->flight == NULL){		//loops for flights
			return;
		} else {
			temp = this->flight;
			while (temp){
				this->price += (temp->getFlight())->getPrice();		//adds price of each flight to this object
				this->price += (temp->getFlight())->getBaggageFees(this->numOfBags);  //adds price of baggage to object
				temp = temp->Next();	//iterator
			}
		}
	}
	void calculateTime(){
		FlightPath* first = NULL;
		FlightPath* temp = NULL;
		FlightPath* last = NULL;
		this->time = 0;
		if (this->flight == NULL) {
			return;
		} else {
			first = this->flight;
			temp = this->flight;		//loops for flights
			while (temp){
				last = temp;
				temp = temp->Next();
			}
			// last arrival - first departure
			time = first->getFlight()->getDeparture()->timeDifferential(last->getFlight()->getArrival());
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
