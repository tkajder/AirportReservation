using namespace std;
#include <string.h>

class Reservation{
	FlightNode *flight = NULL;
	Reservation *next = NULL;
	
	public:
	Reservation(FlightNode* in){
		this->flight = in;
	}
	FlightNode* getFlight(){return this->flight;}
	
	void setFlight(FlightNode* in){
		this->flight = in;
	}
	
	Reservation* Next (){return this->next;}

};




