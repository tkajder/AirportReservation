using namespace std;

class User{
	FlightPath* pathHead = NULL;

	public:
	User(){
	
	}
	
	User* Next (){return this->next;}
};
