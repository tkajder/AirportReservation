#ifndef DATETIME_H
#define DATETIME_H
#include <cmath>

using namespace std;
class Date_Time{

	int month, day, year, hours, minutes;	// hours should be entered as military time
	public:
	Date_Time() {};
	
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
		day = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
		pos = input.find("/");
		month = atoi(input.substr(ppos + 1, pos).c_str());
		year = atoi(input.substr(pos + 1).c_str());
	}
	

	void setDate_Time(int mon, int d, int y, int h, int min){
		month = (mon > 0 && mon <= 12) ? mon : throw "Improper month format.\n";
		day = (d >= 0 && d < 31) ? d : throw "Improper day format.\n";
		year	= (y >= 0) ? y : throw "Improper year format.\n";		//formats raw time data into readable 
		hours = (h >= 0 && h < 24) ? h : throw "Improper hour format.\n";
		minutes = (min >= 0 && min < 60) ? min : throw "Improper minutes format.\n";
	}
	
	void setMinutes(int min){
		minutes = min;
	}
	
	void setHours(int h){
		hours = h;
	}
	
	void setMonth(int mon){
		month = mon;
	}	
	
	void setDay(int d){
		day = d;
	}	
	
	void setYear(int y){
		year = y;
	}

	void AddMinutes(int numOfMin){
		
		if (numOfMin >= 0 && numOfMin <= 59){
			minutes += numOfMin;		//adds # to minutes
		}
		else if (numOfMin > 59){
			hours += floor(numOfMin/60);	// finds the number of hours to add if minutes to add is over 59 minutes
			minutes += numOfMin % 60;	// find the remainder minutes after hours is calculated
		}
		else{
			throw "Positive number of minutes required\n";
		}
	}

	string toString(){
		string dateTime;
		char temp[80];	//creates temp char array to use in sprintg
		if (hours > 10){
			sprintf(temp, "%d/%d/%d  %d : %d", month, day, year, hours, minutes);
			string dateTime(temp);	//converts char array into string
			return dateTime;		//returns string
		}
		else{
			sprintf(temp, "%d/%d/%d 0%d : %d", month, day, year, hours, minutes);
			string dateTime(temp);
			return dateTime;
		}
	}
};

#endif
