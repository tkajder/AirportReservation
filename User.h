#include "ReservationList.h"
using namespace std;

class User{
	ReservationList* reservationHead = NULL;
	
	public:
	User(){	
	}
	
	Reservation* getReservationHead() {
		return this->reservationHead;
	}

	
};
