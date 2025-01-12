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
		EventLogger(){};

		void log_updateTime(Time& time, ofstream& log){
			string time_formatted = format_time(time.get_currentTime());
			cout<<"["<<time_formatted<<"] L'orario attuale è "<<time_formatted<<endl;
			log<<"["<<time_formatted<<"] L'orario attuale è "<<time_formatted<<endl;  
		}

		void log_updateStatus(Time& time, ofstream& log, string device_name, string status){
			string time_formatted = format_time(time.get_currentTime());
			if(status == "on"){
				cout<<"["<<time_formatted<<"] Il dispositivo "<<device_name<<" si e' acceso"<<endl;
				log<<"["<<time_formatted<<"] Il dispositivo "<<device_name<<" si e' acceso"<<endl;
			}
			else{
				cout<<"["<<time_formatted<<"] Il dispositivo '"<<device_name<<"' si e' spento"<<endl;
				log<<"["<<time_formatted<<"] Il dispositivo '"<<device_name<<"' si e' spento"<<endl;
			}
		}

		void log_updateTimer(Time& time, ofstream& log, string device_name, int end_time, int start_time){
			string time_formatted = format_time(time.get_currentTime());
			string end_time_formatted = format_time(end_time);
			string start_time_formatted = format_time(start_time);
			cout<<"["<<time_formatted<<"] Impostato un timer per il dispositivo '"<<device_name<<"' dalle "<<start_time_formatted<<" alle "<<end_time_formatted<<endl;
			log<<"["<<time_formatted<<"] Impostato un timer per il dispositivo '"<<device_name<<"' dalle "<<start_time_formatted<<" alle "<<end_time_formatted<<endl;
		}

		void log_removeTimer(Time& time, ofstream& log, string device_name){
			string time_formatted = format_time(time.get_currentTime());
			cout<<"["<<time_formatted<<"] Rimosso il timer dal dispositivo '"<<device_name<<"'"<<endl;
			log<<"["<<time_formatted<<"] Rimosso il timer dal dispositivo '"<<device_name<<"'"<<endl;
		}

		void log_showConsume(Time& time, ofstream& log, string device_name, double consume, int time_on){
			string time_formatted = format_time(time.get_currentTime());
			double total_consume = ((double)time_on/60)*consume + ((double)(time_on%60)/60)*consume;
			if(total_consume >= 0){
				cout<<"["<<time_formatted<<"] Il dispositivo ha attualmente consumato '"<<total_consume<<"' kWh"<<endl;
				log<<"["<<time_formatted<<"] Il dispositivo ha attualmente consumato '"<<total_consume<<"' kWh"<<endl;	
			}
			else{
				cout<<"["<<time_formatted<<"] Il dispositivo ha attualmente prodotto '"<<(-1)*total_consume<<"' kWh"<<endl;
				log<<"["<<time_formatted<<"] Il dispositivo ha attualmente prodotto '"<<(-1)*total_consume<<"' kWh"<<endl;	
			}
			
		}
		
		void log_showConsumeTotal(Time& time, ofstream& log, ListaDevice& lista){

		}

	private:
		string format_time(int time_min){ //funzione helper per formattare il tempo (da minuti dalle 00:00)
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
		
};

#endif
