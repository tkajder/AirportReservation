#ifndef USER_H
#define USER_H

#include "ReservationList.h"

class User{
	ReservationList* reservationHead;
	public:
	User(){
		reservationHead = NULL;
	}
	
	~User() {
		delete reservationHead;		//destructor
	}

	ReservationList* getReservationHead() {
		return this->reservationHead;
	}
	/* ADD WHEN WE HAVE MULTIPLE RESERVATIONS
	void addReservation(ReservationList* reservation){
		ReservationList* temp;
		if (reservationHead) {
			temp = reservationHead;
			while (temp->Next()) {
				temp = temp->Next();
			}
			temp->setNext(reservation);
		} else {
			reservationHead = reservation;
		}
	}
	*/
	void setReservation(ReservationList* reservation) {	//used to set the reservation head
		reservationHead = reservation;
	}
	
	ReservationList* cheapestRoute(){		//grabs cheapest route
		ReservationList* temp = reservationHead;
		ReservationList* cheapest = temp;
		if (cheapest == NULL)		//return NULL if list is empty
			return NULL;
		while (temp->Next() != NULL){	//loops for linked list
			temp = temp->Next();
			if(temp->getPrice() < cheapest->getPrice())
				cheapest = temp;	//puts cheapest into here if the current tested one is less money
			
		}
		
		return cheapest;
	}
	
	ReservationList* shortestRoute(){
		ReservationList* temp = reservationHead;
		ReservationList* shortest = temp;
		if (shortest == NULL)		//return NULL if list is empty
			return NULL;
		while (temp->Next() != NULL){		//loops for list
			temp = temp->Next();
			if(temp->getTime() < shortest->getTime())
				shortest = temp;	//puts shortest in here if the tested one is shorter
		}
		
		return shortest;
	}
	
	void printItinerary() {
		FlightPath* path = this->reservationHead->getFlights();
		FlightNode* flight;
		int baggageFees;
		
		while (path) {	//loops for paths
			baggageFees = path->getFlight()->getBaggageFees(reservationHead->getBagNum());
			if (baggageFees){		//if there is baggage fees
				flight = path->getFlight();
				cout << flight->getFlightNumber() << "\t" << flight->getFlightCompany() << "\t" << flight->getSource()->getLocation() << "\t" << flight->getDeparture()->toString() << endl;
				cout << "\t\t\t" << flight->getDestination()->getLocation() << "\t" << flight->getArrival()->toString() << endl;
				cout << "\t\t\t" << "$" << flight->getPrice() << " base price" << " + $" << baggageFees << " Baggage Fee" << " = " << "$" << flight->getPrice() + baggageFees <<  endl; 
				path = path->Next();	//iterates path (flight)
			}else{
				flight = path->getFlight();
				cout << flight->getFlightNumber() << "\t" << flight->getFlightCompany() << "\t" << flight->getSource()->getLocation() << "\t" << flight->getDeparture()->toString() << endl;
				cout << "\t\t\t" << flight->getDestination()->getLocation() << "\t" << flight->getArrival()->toString() << endl;
				cout << "\t\t\t" << "$" << flight->getPrice() << " base price" << " = " << "$" << flight->getPrice() <<  endl; 
				path = path->Next();
			}	
		}
		cout << endl << "Check-in " << reservationHead->getBagNum() << " Bags" << endl;
		cout << "Grand Total: $" << reservationHead->getPrice() << endl << endl;
	}
};

#endif
