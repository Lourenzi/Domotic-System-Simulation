//Created by Lorenzo


#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include "DataStructure.h"

using namespace std;

class Interface{
	public:
		Interface();
		void parseCommand(string cmd, ofstream& log);

	private:
		Time time;
		DataStructure data;
		int calculateTime(string time_format);
		void setTime(string time_format);
		void setStatus(string device_name, string status);
		void setStatus(string device_name, string time_start, string time_stop);
		void showConsumption();
		void showConsumption(string device_name);
		void removeDevice(string device_name);
		void resetTime();
		void resetTimers();
		void resetAll();
		bool isStatusValid(string status);
		bool isTimeFormatValid(string time_format);
		bool isDeviceNameValid(string device_name);

};


#endif
