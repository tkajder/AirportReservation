class Date_Time{
public:
	Date_Time();						// default constructor
	void setDate_Time(int, int, int, int, int);	// setter
	void AddMinutes(int);				// add minutes
	string toString();					// creates a sring of the date and time
	
private:
	int month, day, year, hours, minutes;	// hours should be entered as military time
};

Date_Time::Date_Time(){
	month = day = year = hours = minutes = 0;
}

void Date_Time::setDate_Time(int mon, int d, int y, int h, int min){
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
		printf("Please enter a positive number of minutes to add\n");
}

string toString(){
	string dateTime;
	if (hour > 10){
		dateTime = toString(month) + "/" + toString(day) + "/" + toString(year) + " " + toString(hours) + ":" + toString(minutes);  
		return dateTime;
	}
	else{
		dateTime = toString(month) + "/" + toString(day) + "/" + toString(year) + " 0" + toString(hours) + ":" + toString(minutes);
		return dateTime;
	}
}

