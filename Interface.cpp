//Created by Lorenzo

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include "DataStructure.h"
#include "Interface.h"
#include "ListaDevice.h"
#include "EventLogger.h"
using namespace std;

EventLogger eventLog;
ListaDevice deviceList;
DataStructure dataStructure;
Time timeCurrent = dataStructure.get_Time();

Interface::Interface(){};

int Interface::calculateTime(string time_format){ 
	int time_min;
	string hours = time_format.substr(0,2);
	string mins = time_format.substr(3,2);
	time_min = stoi(hours)*60 + stoi(mins); //conversione da time formato hh:mm a time in minuti dalle 00:00 
	return time_min;
}

void Interface::setTime(string time_format){ 
	int time_min = calculateTime(time_format);
	timeCurrent.set_time(time_min);
	dataStructure.set_Time(time_min);
}

void Interface::setStatus(string device_name, string status){ 
	bool on = (status == "on") ? true : false; 
	Device d = deviceList.get_Device_by_name(device_name);
	dataStructure.set(d, on);
}

void Interface::setStatus(string device_name, string time_start, string time_stop){
	int start = calculateTime(time_start);
	int stop = calculateTime(time_stop);
	Device d = deviceList.get_Device_by_name(device_name);
	cout<<d.get_device_name()<<endl;
	dataStructure.set(d, start, stop);
}

void Interface::showConsumption(){ 
	cout<<"show all devices consumption"<<endl;
}

void Interface::showConsumption(string device_name){
 	cout<<"show consumption of "<<device_name<<endl;
}

void Interface::removeDevice(string device_name){
	cout<<"Device "<<device_name<<" has been removed"<<endl;
}

void Interface::resetTime(){
	cout<<"Reset time"<<endl;
}

void Interface::resetTimers(){
	cout<<"Reset timers"<<endl;
}

void Interface::resetAll(){
	cout<<"Reset all"<<endl;
}


bool Interface::isStatusValid(string status){
	bool statusValid = false;
	if(status == "on" || status == "off")
		statusValid = true;
	return statusValid;
}

bool Interface::isTimeFormatValid(string time_format){
	bool timeValid = false;
	bool hh_mmValid = false;
	if(std::count_if(time_format.begin(), time_format.end(), [](char c) { return std::isdigit(static_cast<unsigned char>(c)); }) == 4){
		hh_mmValid = true;
	}

	if(time_format.size() == 5 && time_format.find(":") == 2 && hh_mmValid){  //il formato dell'orario deve essere del tipo hh:mm
		int hours_i = stoi(time_format.substr(0,2));
		int mins_i = stoi(time_format.substr(3,2));
		if(hours_i < 24 && mins_i < 60){
			timeValid = true;
		}
	}
	return timeValid;
}

bool Interface::isDeviceNameValid(string device_name){
	bool deviceValid = false;
	vector<Device> devices = deviceList.get_vector();
	for(int i=0; i<devices.size(); i++){
		if(devices.at(i).get_device_name() == device_name){
			deviceValid = true;
		}
	}
	return deviceValid;
}



void Interface::parseCommand(string cmd){ //funzione di estrapolazione dei parametri del comando da terminale
	vector<string> parameters; //vector indicizzato cosi' : [tipo di comando] --> 0 , [nome device/time var] --> 1 , [status/ora start timer/ora set] --> 2 , [ora stop timer] --> 3
	int i_start = 0; // indice di inizio parola i-esima della stringa comando
	int i = 0;
	while(i < cmd.size()){
		if(cmd.at(i) == ' ' || i == cmd.size()-1){
			if (i == cmd.size() - 1 && cmd.at(i) != ' ') i++;
			parameters.push_back(cmd.substr(i_start, i - i_start));
			i_start = i + 1;
		}
		i++;
	}

	string cmd_type = parameters.at(0);  //tipologia del comando immesso
	vector<string> cmd_types = {"set", "show", "rm", "reset"};
	if(std::find(cmd_types.begin(), cmd_types.end(), cmd_type) != cmd_types.end()){
		if(cmd_type == "set"){
			if(parameters.at(1) == "time"){  //se è un comando set time
				if(parameters.size() == 3){
					if(isTimeFormatValid(parameters.at(2))){
						eventLog.log_updateTime(timeCurrent);
						setTime(parameters.at(2));
						eventLog.log_updateTime(timeCurrent);	
					
					}else{ cout<<"--Formato dell'orario errato--"<<endl; }
				}
				else{ cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }
			}
			else{   //se è un comando set ${DEVICENAME}, trattato nelle sue due versioni
				if(parameters.size() <= 4 && parameters.size() > 2){
					if(isDeviceNameValid(parameters.at(1))){	
						if(parameters.size() == 4){
							if(isTimeFormatValid(parameters.at(2)) && isTimeFormatValid(parameters.at(3))){
								Device d = deviceList.get_Device_by_name(parameters.at(1));
								int start = calculateTime(parameters.at(2));
								int end = calculateTime(parameters.at(3));
								cout<<d.get_device_name()<<start<<end<<endl;
								eventLog.log_updateTime(timeCurrent);
								setStatus(parameters.at(1), parameters.at(2), parameters.at(3));
								eventLog.log_updateTimer(timeCurrent,d.get_device_name(),calculateTime(parameters.at(2)),calculateTime(parameters.at(3)));
								eventLog.log_updateTime(timeCurrent);
							}
							else{ cout<<"--Formato dell'orario errato--"<<endl; } 
						}
						else{
							if(isStatusValid(parameters.at(2))) {
								Device d = deviceList.get_Device_by_name(parameters.at(1));
								eventLog.log_updateTime(timeCurrent);
								setStatus(parameters.at(1), parameters.at(2));
								eventLog.log_updateStatus(timeCurrent,d.get_device_name(),parameters.at(2));
								eventLog.log_updateTime(timeCurrent);
							}
							else{ cout<<"--Status non settabile--"<<endl; }
						}
					}
					else{ cout<<"--Nome dispositivo non riconosciuto--"<<endl;}
				}
				else{ cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }
			}
		}

		if(cmd_type == "show"){
			if(parameters.size() <= 2){
				if(parameters.size() == 2){  //se è un comando show ${DEVICENAME}
					if(isDeviceNameValid(parameters.at(1))){
						eventLog.log_updateTime(timeCurrent);
						showConsumption(parameters.at(1));
						eventLog.log_updateTime(timeCurrent);
					}
					else{cout<<"--Nome dispositivo non riconosciuto--"<<endl;}
				}
				else{  //comando show complessivo
					eventLog.log_updateTime(timeCurrent);
					showConsumption();
					eventLog.log_updateTime(timeCurrent);
				}	
			}
			else { cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }	
		}

		if(cmd_type == "rm"){
			if(parameters.size() == 2){
				if(isDeviceNameValid(parameters.at(1))){
					eventLog.log_updateTime(timeCurrent);
					removeDevice(parameters.at(1));	
					eventLog.log_updateTime(timeCurrent);
				}
				else{cout<<"--Nome dispositivo non riconosciuto--"<<endl;}
			}
			else{ cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }	
		}

		if(cmd_type == "reset"){
			if(parameters.size() == 2) { 
				if(parameters.at(1) == "time") { resetTime(); }
				if(parameters.at(1) == "timers") { resetTimers(); }
				if(parameters.at(1) == "all") { resetAll(); }
			}
			else{ cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl;}
		}
	}
	else{
		cout<<"--Tipo di comando inesistente--"<<endl;
	}
}
