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
		double baggageFees, tPrice;
		string bag, price, ttlPrice, outPrice;
		
		
		
		while (path) {	//loops for paths
			baggageFees = path->getFlight()->getBaggageFees(reservationHead->getBagNum());
			bag = static_cast<ostringstream*>( &(ostringstream() << path->getFlight()->getBaggageFees(reservationHead->getBagNum()) ) )->str();	// parses duration of flight to a string
			price = static_cast<ostringstream*>( &(ostringstream() << path->getFlight()->getPrice() ) )->str();	// parses duration of flight to a string
			
			if (baggageFees == 0){
				outPrice = "$" + price + " Base Price = $" + price; 
			}
			else{
				tPrice = path->getFlight()->getPrice() + baggageFees;
				ttlPrice = static_cast<ostringstream*>( &(ostringstream() << tPrice) )->str();	// parses duration of flight to a string
				outPrice = "$" + price + " Base Price + $" + bag + " Baggage Fee = $" + ttlPrice; 
			}

			flight = path->getFlight();
			cout << " " << setfill(' ') <<  setw(13) << left << flight->getFlightNumber() << setw(13) << left << flight->getFlightCompany() << setw(14) << left << flight->getSource()->getLocation() << flight->getDeparture()->toString() << endl;
			cout << " " <<  setw(26) << " " << setw(14) << left << flight->getDestination()->getLocation() << flight->getArrival()->toString() << endl;
			cout << setw(57) << right << outPrice << endl << endl; 
			path = path->Next();	//iterates path (flight)	
		}
		cout << " Check-in " << reservationHead->getBagNum() << " Bags" << endl;
		cout << " Grand Total: $" << reservationHead->getPrice() << endl << endl;
	}
};

#endif
