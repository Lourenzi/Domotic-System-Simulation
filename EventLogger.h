//Created by Lorenzo

#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H


#include <iostream>
#include <fstream>
#include "ListaDevice.h"
#include "time.h"
#include "DataStructure.h"

class EventLogger{
	public:
		EventLogger();
	private:
		string format_time(int time_min){
			string time_formatted, mm, hh;
			int mins = time_min%60;
			int hours = time_min/60;
			if(mins < 10) {mm = "0" + to_string(mins);}
			else {mm = to_string(mins);}
			if(hours < 10) {hh = "0" + to_string(hours);}
			else {hh = to_string(hours);}
			time_formatted = hh + ":" + mm;
			return time_formatted;
		}

		void log_updateTime(Time& time, ofstream& log){
			string time_formatted = format_time(time.get_currentTime());
			cout<<"["<<time_formatted<<"] L'orario attuale è "<<time_formatted<<endl;
			log<<"["<<time_formatted<<"] L'orario attuale è "<<time_formatted;  
		}
		
		void log_updateStatus(ofstream& log);
		void log_updateTimer(ofstream& log);
		void log_removeTimer(ofstream& log);
		void log_showConsume(ofstream& log);
		void log_showConsumeTotal(ofstream& log);
		
}

#endif