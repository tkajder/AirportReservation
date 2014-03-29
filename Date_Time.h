#ifndef DATETIME_H
#define DATETIME_H
#include <cmath>
#include <math.h>

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
	
	Date_Time(string input) {
		int pos, ppos;
		ppos = -1;	// trails behind pos
		pos = input.find("/");		//searches for /
		minutes = atoi(input.substr(ppos + 1, pos).c_str()); //places that information into minutes
		ppos = pos;	//moves ppos up
		pos = input.find("/");
		hours = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/");
		days = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/");
		months = atoi(input.substr(ppos + 1, pos).c_str());
		years = atoi(input.substr(pos + 1).c_str());

	}
	
	
	int getMonths(){return months;}
	int getDays(){return days;}
	int getYears(){return years;}
	int getHours(){return hours;}
	int getMinutes(){return minutes;}
	
	void setMonths(int input){this->months = input;}
	void setDays(int input){this->days = input;}
	void setYears(int input){this->years = input;}
	void setHours(int input){this->hours = input;}
	void setMinutes(int input){this->minutes = input;}

	void setDate_Time(int mon, int d, int y, int h, int min){
		months = (mon > 0 && mon <= 12) ? mon : throw "Improper month format.\n";
		days = (d >= 0 && d < 31) ? d : throw "Improper day format.\n";
		years	= (y >= 0) ? y : throw "Improper year format.\n";		//formats raw time data into readable 
		hours = (h >= 0 && h < 24) ? h : throw "Improper hour format.\n";
		minutes = (min >= 0 && min < 60) ? min : throw "Improper minutes format.\n";
	}

	void addMinutes(int numOfMin){		//recursion, weeeeeeeeeee
		if (numOfMin == 0)
			return;
		if (numOfMin + this->minutes < 60){
			this->minutes += numOfMin;
			return;	
		}else if(floor(numOfMin/60) + this->hours < 24){
			this->hours += floor(numOfMin/60);
			addMinutes(numOfMin - (floor(numOfMin/60) * 60));
		}else{
			this->days += floor(numOfMin/1440);
			addMinutes(numOfMin - (floor(numOfMin/1440) * 60));
		}
	}
	
	Date_Time* getEndTime(int delta){
		Date_Time* ret = new Date_Time();
		ret->months = this->getMonths();
		ret->days = this->getDays();
		ret->years = this->getYears();
		ret->hours = this->getHours();
		ret->minutes = this->getMinutes();
		ret->addMinutes(delta);
		return ret;			
	}
	
	int getElapsedMinutes(){
		return this->hours * 60 + this->minutes;
	}

	string toString(){
		string dateTime;
		char temp[80];	//creates temp char array to use in sprintg
		if (hours > 10){
			sprintf(temp, "%d/%d/%d  %d : %d", months, days, years, hours, minutes);
			string dateTime(temp);	//converts char array into string
			return dateTime;		//returns string
		}
		else{
			sprintf(temp, "%d/%d/%d 0%d : %d", months, days, years, hours, minutes);
			string dateTime(temp);
			return dateTime;
		}
	}
};

#endif

