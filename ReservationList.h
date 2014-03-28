using namespace std;
#include <string>
#include "FlightPath.h"

class ReservationList{
	FlightPath *flight = NULL;
	ReservationList *next = NULL;
	double price;
	int time;
	
	public:
	ReservationList(FlightPath* in){
		this->flight = in;
	}
	FlightNode* getFlight(){return this->flight;}
	
	void setFlight(FlightNode* in){
		this->flight = in;
	}
	
	ReservationList* Next (){return this->next;}
	
	void setNext(ReservationList* ReservationList) {
		this->next = ReservationList;
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




