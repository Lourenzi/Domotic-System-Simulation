//Created by Lorenzo


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Interface.h"

using namespace std;

int main(){

	ofstream log_file;
	log_file.open("eventLog.txt");

	string command = "";
	while(command != "end"){
		getline(cin, command);
		parseCommand(command, log_file);
	}

	log_file.close();
	return 0;
}
