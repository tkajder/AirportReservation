#ifndef USER_H
#define USER_H

#include "ReservationList.h"
//using namespace std;

class User{
	ReservationList* reservationHead = NULL;
	int numOfBags;
	public:
	User(){
		this->numOfBags = 0;
	}
	int getBagNum(){return this->numOfBags;}
	ReservationList* getReservationHead() {
		return this->reservationHead;
	}
	
	void addReservation(Reservation* reservation){
	
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
};

#endif
