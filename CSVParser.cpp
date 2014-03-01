#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CSVParser {
	string hub_data, flight_data;
public:
	void load() {
		ifstream flight_file("Flight.csv")
		ifstream hub_file("Hub.csv");

		// If files exist, save their data
		if (flight_file) {		
			stringstream flight_stream;
			flight_stream << flight_file.rdbuf()
			flight_data = flight_stream.str()
		} else {
			cerr << "Flight.csv could not be opened.\n";
        		exit(1);
		}
		if (hub_file) {
			stringstream hub_stream;
			hub_stream << hub_file.rdbuf()
			hub_data = hub_stream.str()
		} else {
			cerr << "Hub.csv could not be opened.\n";
        		exit(1);
		}

		flight_file.close()
		hub_file.close()
	}
};
