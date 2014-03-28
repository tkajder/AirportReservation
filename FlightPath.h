using namespace std;
#include <string.h>

class FlightPath{
	FlightNode *flight = NULL;
	FlightPath *next = NULL;
	
	public:
	FlightPath(FlightNode* in){
		this->flight = in;
	}
	string getFlight(){return this->flight;}
	void setFlight(FlightNode* in){
		this->flight = in;
	}

};
