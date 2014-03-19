#ifndef DATETIME_H
#define DATETIME_H

using namespace std;
class Date_Time{

	int month, day, year, hours, minutes;	// hours should be entered as military time
	public:
	Date_Time(){}; // Needs transition to pointer use like Hub and Flight
	
	Date_Time(string input) {
		int pos, ppos;
		ppos = -1;
		pos = input.find("/");
		minutes = atoi(input.substr(ppos + 1, pos).c_str());
		ppos = pos;
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
		month = (mon >= 0 && mon < 12) ? mon : 0;
		day = (d >= 0 && d < 31) ? d : 0;
		year	= (y >= 0) ? y : 0;
		hours = (h >= 0 && h < 24) ? h : 0;
		minutes = (min >= 0 && min < 60) ? min : 0;
	}

	void AddMinutes(int numOfMin){
		if (numOfMin >= 0)
			minutes += numOfMin;
		else
			throw "Please enter a positive number of minutes to add\n";
	}

	string toString(){
		string dateTime;
		char temp[80];
		if (hours > 10){
			sprintf(temp, "%d/%d/%d  %d : %d", month, day, year, hours, minutes);
			string dateTime(temp);
	//		dateTime = toString(month) + "/" + toString(day) + "/" + toString(year) + " " + toString(hours) + ":" + toString(minutes);  
			return dateTime;
		}
		else{
			sprintf(temp, "%d/%d/%d 0%d : %d", month, day, year, hours, minutes);
			string dateTime(temp);
			//dateTime = toString(month) + "/" + toString(day) + "/" + toString(year) + " 0" + toString(hours) + ":" + toString(minutes);
			return dateTime;
		}
	}
};

#endif
