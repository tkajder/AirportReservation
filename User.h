#include "FlightPath.h"
using namespace std;


class User{
	FlightPath* pathHead = NULL;
	User* next = NULL;
	
	public:
	User(){	
	}
	
	User* Next (){return this->next;}
};
