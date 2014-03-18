#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstdio>
#include "Nodes.h"
//#include "Date_Time.h"
using namespace std;


HubNode* hub = NULL;

void printMain(){	
		printf("Welcome to the Airport Reservation Extravaganza!!\n\n");
		printf("Please select from the following options:\n");
}


int main(){
	//do stuff here
	printMain();
	return 0;
}




void printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice){
	TotalPrice = NumOfBags * Price;

	//printf("%s\t%s\t%s\t%s\n\t\t%s\t%s\n%f=%f",FlightNum, Company, SourceLocation, Depart_DateTime, DestinationLocation, Arrive_DateTime, Price, TotalPrice); 
}


void debug(HubNode* hub){
	HubNode* current = hub;
	while (current != NULL){		//loops for hubs
		FlightNode* flight = current->getFlights();
		while (flight != NULL){		//loops for flight per hub
			FlightNode* source = flight->getSource();
			FlightNode* dest = flight->getDestination();
			//printf("%d : %d : %s : %s : %s\n", flight->getFlightNumber(), flight->getPrice(), flight->getFlightCompany(), source->getName(), dest->getName());
			flight = flight->Next();
		}
		current = current->Next();
	}
}
