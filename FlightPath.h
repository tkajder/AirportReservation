using namespace std;

class FlightPath{
	FlightNode* flight= NULL;
	FlightPath* next = NULL;
	
	public:
	
	FlightPath(FlightNode* new){
		this->flight = new;
	}
	FlightPath* next(){return this->next;}
}
