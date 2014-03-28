using namespace std;

class FlightPath{
	FlightNode* flight= NULL;
	FlightPath* next = NULL;
	
	public:
	
	FlightPath(FlightNode* newFlight){
		this->flight = newFlight;
	}
	HubNode* getDestination(){return this->flight->getDestination();}
	FlightPath* getFlight(){return this->flight;}
	FlightPath* Next(){return this->next;}
}
