using namespace std;
#include <string.h>

class Reservation{
	FlightNode *flight = NULL;
	Reservation *next = NULL;
	double price;
	int time;
<<<<<<< HEAD
	
=======
>>>>>>> master
	
	public:
	Reservation(FlightNode* in){
		this->flight = in;
	}
	FlightNode* getFlight(){return this->flight;}
	
	void setFlight(FlightNode* in){
		this->flight = in;
	}
	
	Reservation* Next (){return this->next;}
	
<<<<<<< HEAD
	FlightNode* nextFlight() {return this->flight;}f
	
	void setNext(Reservation* reservation){
		this->next = reservation
	}
=======
	void setNext(Reservation* reservation) {
		this->next = reservation;
	}
	
	void addFlightPathNode(Reservation* reservation) {
		Reservation* curr = this->reservationHead;
		if(curr) {
			while(curr->Next()) {
				curr = curr->Next();
			}
			curr->setNext() = reservation;
		}
		else {
			this->reservationHead = reservation;
		}
	}

>>>>>>> master
};






