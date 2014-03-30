#ifndef USER_H
#define USER_H

#include "ReservationList.h"

class User{
	ReservationList* reservationHead;
	public:
	User(){
		reservationHead = NULL;
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
	void addReservation(ReservationList* reservation) {
		reservationHead = reservation;
	}
	
	ReservationList* cheapestRoute(){
		ReservationList* temp = reservationHead;
		ReservationList* cheapest = temp;
		if (cheapest == NULL)
			return NULL;
		while (temp->Next() != NULL){
			temp = temp->Next();
			if(temp->getPrice() < cheapest->getPrice())
				cheapest = temp;
			
		}
		
		return cheapest;
	}
	
	ReservationList* shortestRoute(){
		ReservationList* temp = reservationHead;
		ReservationList* shortest = temp;
		if (shortest == NULL)
			return NULL;
		while (temp->Next() != NULL){
			temp = temp->Next();
			if(temp->getTime() < shortest->getTime())
				shortest = temp;
		}
		
		return shortest;
	}
	
	void printItinerary() {
		FlightPath* path = this->reservationHead->getFlights();
		FlightNode* flight;
	
		while (path) {
			flight = path->getFlight();
			cout << flight->getFlightNumber() << "\t" << flight->getFlightCompany() << "\t" << flight->getSource()->getLocation() << "\t" << flight->getDeparture()->toString() << endl;
			cout << "\t\t" << flight->getDestination()->getLocation() << "\t" << flight->getArrival()->toString() << endl;
			cout << "\t\t" << "$" << flight->getPrice() << " base price" << " = " << "$" << this->reservationHead->getPrice() <<  endl; 
			path = path->Next();
		}
	}
};

#endif
