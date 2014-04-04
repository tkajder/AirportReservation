#ifndef DATETIME_H
#define DATETIME_H
#include <cmath>
#include <sstream>

using namespace std;
class Date_Time{

	int months; 
	int days;
	int years; 
	int hours;
	int minutes;	// hours should be entered as military time
	public:
	Date_Time() {
		this->months = 0; 
		this->days = 0;
		this->years = 0; 
		this->hours = 0;
		this->minutes = 0;
	};
	
	// Constructor
	Date_Time(string input) {
		int pos, ppos;
		ppos = -1;	// trails behind pos
		pos = input.find("/");		//searches for /
		minutes = atoi(input.substr(ppos + 1, pos).c_str()); //places that information into minutes
		ppos = pos;	//moves ppos up
		pos = input.find("/", ppos + 1);
		hours = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/", ppos + 1);
		days = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/", ppos + 1);
		months = atoi(input.substr(ppos + 1, pos).c_str());
		years = atoi(input.substr(pos + 1).c_str());

	}
	
	//Getters
	int getMonths(){return this->months;}
	int getDays(){return this->days;}
	int getYears(){return this->years;}
	int getHours(){return this->hours;}
	int getMinutes(){return this->minutes;}
	
	
	//Sets the chunk at once
	void setDate_Time(int mon, int d, int y, int h, int min){
		bool isLeapYear = true;
		
		
		if (mon > 0 && mon <= 12){	// checks that the month entered is valid
			months = mon;	//sets month
			
			// Checks for leap year (if it is a leap year February has 29 days, if not it has 28 days)
			if (y % 4 != 0){
				isLeapYear = false;
			}
			else if (y % 100 != 0){
				isLeapYear = true;
			}
			else if (y % 400 == 0){
				isLeapYear = true;		
			}
			else{
				isLeapYear = false;
			}
		
			// If month entered is Jan, Mar, May, July, Aug, Oct, or Dec there are 31 days	
			if (months == 1 || months == 3 || months == 5 || months == 7 || months == 8 || months == 10 || months == 12){
				if (d >= 0 && d <= 31){
					days = d;
				}
				else{
					throw "Improper day format.\n";
				}
			}
			// if month entered is April, June, September, November it has 30 days
			if (months == 4 || months == 6 || months == 9 || months == 11){
				if (d >= 0 && d <= 30){
					days = d;
				}
				else{
					throw "Improper day format.\n";
				}
			}
			// if month is Feb and not a leap year, 28 days
			if (months == 2 && isLeapYear == false){
				if (d >= 0 && d <= 28){
					days = d;
				}
				else{
					throw "Improper day format.\n";
				}
			}
			// if month is Feb and is a leap year, 29 days
			if (months == 2 && isLeapYear == true){
				if (d >= 0 && d <= 29){
					days = d;
				}
				else{
					throw "Improper day format.\n";
				}
			}
		}
		else{
			throw "Improper month format.\n";
		}
		
		years = (y >= 0) ? y : throw "Improper year format.\n";		// years have to be greater than zero 
		hours = (h >= 0 && h < 24) ? h : throw "Improper hour format.\n";  // hours have to be between 1 and 23 inclusive (military time)
		minutes = (min >= 0 && min < 60) ? min : throw "Improper minutes format.\n";	// minutes have to be between 1 and 59 inclusive
	}

	void addMinutes(int numOfMin){
		this->minutes += numOfMin;		//adds numbers of minutes to minutes
		if (this->minutes >= 60) {		//checks if minutes is more than 59
			this->hours += floor(this->minutes / 60);
			this->minutes = this->minutes % 60;		//converts excess minutes to hours, throws in there, fixes minutes
		}
		if (this->hours >= 24) {		//checks if hours > 23
			this->days += floor(this->hours / 24);	
			this->hours = this->hours % 24; 	//converts excess hours into days, tosses rest into hours
		}
		return;
	}
	
	bool lessThan(Date_Time* date){		//ensures the given time is less than the time passed
		if (this->getDays() < date->getDays()) {
			return 1;			//used to make sure past flights cannot be added
		}
	
		if (this->getDays() == date->getDays()) {
			if (this->minutesSinceMidnight() < date->minutesSinceMidnight()) {
				return 1;
			}
		}
	
		return 0;
	}

	int timeDifferential(Date_Time* date) {		//pulls the time difference between two dates (this and passed)
		int numOfMin = 0;
		numOfMin += (date->getDays() - this->getDays()) * 1440;
		numOfMin += date->minutesSinceMidnight() - minutesSinceMidnight(); 
		return numOfMin;
	}
	// this is used to get the Date_Time of the flights arrival
	Date_Time* getEndTime(int delta){	//creates new Date_Time object
		Date_Time* ret = new Date_Time();
		ret->setDate_Time(this->getMonths(), this->getDays(), this->getYears(), this->getHours(), this->getMinutes());
		ret->addMinutes(delta);		//adds change in minutes to it
		return ret;			
	}
	
	int minutesSinceMidnight() {		//returns amount of minutes since midnight 
		return this->hours * 60 + this->minutes;
	}

	string toString(){
		string dateTime;
		// converts int to string for months, days, years, hours, and minutes
		string month = static_cast<ostringstream*>( &(ostringstream() << months) )->str();			
		string day = static_cast<ostringstream*>( &(ostringstream() << days) )->str();
		string year = static_cast<ostringstream*>( &(ostringstream() << years) )->str();
		string hour = static_cast<ostringstream*>( &(ostringstream() << hours) )->str();
		string minute = static_cast<ostringstream*>( &(ostringstream() << minutes) )->str();

		if (hours >= 10 && minutes >= 10){
			string dateTime = month + "/" + day + "/" + year + " " + hour + ":" + minute;
			return dateTime;		//returns string
		}
		else if (hours < 10 && minutes >= 10){
			string dateTime = month + "/" + day + "/" + year + " 0" + hour + ":" + minute;			
			return dateTime;		// returns string
		}
		else if (hours >= 10 && minutes < 10){
			string dateTime = month + "/" + day + "/" + year + " " + hour + ":0" + minute;		
			return dateTime;		// returns string
		}
		else {
			string dateTime = month + "/" + day + "/" + year + " 0" + hour + ":0" + minute;	
			return dateTime;		// returns string
		}
	}
};

#endif

