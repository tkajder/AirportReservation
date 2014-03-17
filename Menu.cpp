#include <string>
#include <iostream>
#include <cstdio>
using namespace std;


class Menu{
public:
	void printMain();
	void printItinerary(string, string, string, string, double, int, double);
};


void printMain(){	
		printf("Welcome to the Airport Reservation Extravaganza!!\n\n");
		printf("Please select from the following options:\n");
}

void Menu::printItinerary(string FlightNum, string Company, string SourceLocation, string DestinationLocation, double Price, int NumOfBags, double TotalPrice){
	TotalPrice = NumOfBags * Price

	printf("%s\t%s\t%s\t%s\n\t\t%s\t%s\n%f=%f",FlightNum, Company, SourceLocation, Depart_DateTime, DestinationLocation, Arrive_DateTime, Price, TotalPrice); 
}


