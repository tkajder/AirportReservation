#include "Reservation.h"
using namespace std;

class User{
	Reservation* reservationHead = NULL;
	
	public:
	User(){	
	}
	
	Reservation* getReservationHead() {
		return this->reservationHead;
	}

	
};
