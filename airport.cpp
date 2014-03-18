#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include "Nodes.h"
#include "Date_Time.h"
using namespace std;


/*


class Date_Time{
	short int minutes;
	short int hours;
	short int day;
	short int month;
	short int year;
}


*/

HubNode* hub = new hub;


void main(){
	//do stuff here
	printMain();
}

void printMain(){	
		printf("Welcome to the Airport Reservation Extravaganza!!\n\n");
		printf("Please select from the following options:\n");
}


void printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice){
	TotalPrice = NumOfBags * Price

	printf("%s\t%s\t%s\t%s\n\t\t%s\t%s\n%f=%f",FlightNum, Company, SourceLocation, Depart_DateTime, DestinationLocation, Arrive_DateTime, Price, TotalPrice); 
}


void debug(HubNode* hub){
	HubNode* current = hub;
	while (current != NULL){		//loops for hubs
		FlightNode* flight = current->flights;
		while (flight != NULL){		//loops for flight per hub
			printf("%d : %d : %s : %s : %s\n", flight->getFlightNumber(), flight->getPrice, flight->getFlightCompany, flight->getSource->name, flight->getDestination->name);
			flight = flight->next();
		}
		current = current->next();
	}
}
