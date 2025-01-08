//Created by Lorenzo

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>
#include "DataStructure.h"
#include "Interface.h"
using namespace std;

Interface::Interface(){};

int Interface::calculateTime(string time_format){ 
	int time_min;
	string hours = time_format.substr(0,2);
	string mins = time_format.substr(3,2);
	time_min = stoi(hours)*60 + stoi(mins); //conversione da time formato hh:mm a time in minuti dalle 00:00 
	return time_min;
}

void Interface::setTime(string time_format){ 
	cout<<time_format<<endl;

}

void Interface::setStatus(string device_name, string status){ 
	cout<<"setStatus " + status + " - " + device_name<<endl;
}

void Interface::setStatus(string device_name, string time_start, string time_stop){
	cout<<"setStatus ON - "<<device_name<<" "<<time_start<<" "<<time_stop<<endl;
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

void Interface::parseCommand(string cmd, ofstream& log){ //funzione di estrapolazione dei parametri del comando da terminale
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
						setTime(parameters.at(2));	
					}
					else{ cout<<"--Formato dell'orario errato--"<<endl; }
				}
				else{ cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }
			}
			else{   //se è un comando set ${DEVICENAME}, trattato nelle sue due versioni
				if(parameters.size() <= 4 && parameters.size() > 2){
					if(parameters.size() == 4){
						if(isTimeFormatValid(parameters.at(2)) && isTimeFormatValid(parameters.at(3))){
							setStatus(parameters.at(1), parameters.at(2), parameters.at(3));
						}
						else{ cout<<"--Formato dell'orario errato--"<<endl; } 
					}
					else{
						if(isStatusValid(parameters.at(2))) {
							setStatus(parameters.at(1), parameters.at(2));
						}
						else{ cout<<"--Status non settabile--"<<endl; }
					}
				}
				else{ cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }
			}
		}

		if(cmd_type == "show"){
			if(parameters.size() <= 2){
				if(parameters.size() == 2){  //se è un comando show ${DEVICENAME}
					showConsumption(parameters.at(1));
				}
				else{  //comando show complessivo
					showConsumption();
				}	
			}
			else { cout<<"--Eccessivi o insufficienti parametri immessi--"<<endl; }	
		}

		if(cmd_type == "rm"){
			if(parameters.size() == 2){
				removeDevice(parameters.at(1));	
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
		//throw invalid_argument("--- Tipo di comando inesistente ---");
	}
}
