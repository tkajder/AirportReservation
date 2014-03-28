using namespace std;
#include <string>
#include "FlightPath.h"

class ReservationList{
	FlightPath *flight = NULL;
	ReservationList *next = NULL;
	double price;
	int time;
	int numOfBags;
	Date_Time* start;
	Date_Time* end;
	
	public:
	ReservationList(FlightPath* in){
		this->flight = in;
		start = in->getFlight()->getDeparture;
		calculatePrice();
		calculateTime();
	}
	FlightNode* getFlights(){return this->flight;}
	
	void setFlight(FlightNode* in){
		this->flight = in;
	}
	double getPrice(){return this->price;}
	
	int getTime(){return this->time;}
	
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
				this->price += (temp->getFlight())->getBaggageFees(this->numOfBags){
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
			while (temp->next != NULL){
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




