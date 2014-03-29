#ifndef USER_H
#define USER_H

#include "ReservationList.h"

class User{
	ReservationList* reservationHead;
	int numOfBags;
	public:
	User(){
		reservationHead = NULL;
		this->numOfBags = 0;
	}
	int getBagNum(){return this->numOfBags;}
	
	void setBagNum(int numOfBags) {this->numOfBags = numOfBags;}

	ReservationList* getReservationHead() {
		return this->reservationHead;
	}
	
	void addReservation(ReservationList* reservation){
		
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
	
	void printItinerary(){
		FlightPath* path = this->reservationHead->getFlights();
		FlightNode* flight = path->getFlight();
	
		while (flight) {
			cout << flight->getFlightNumber() << "\t" << flight->getFlightCompany() << "\t" << flight->getSource()->getName() << "\t" << flight->getDeparture()->toString() << endl;
			cout << "\t\t" << flight->getDestination()->getName() << "\t" << flight->getArrival()->toString() << endl;
			cout << "\t\t" << "$" << flight->getPrice() << " base price" << " = " << "$" << this->reservationHead->getPrice() <<  endl; 
			path = path->Next();
			flight = path->getFlight();
		}
	}
};

#endif
