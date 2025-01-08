//Created by Lorenzo


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Interface.h"
#include "DataStructure.h"
using namespace std;

int main(){

	ofstream log_file;
	log_file.open("eventLog.txt");
	Interface terminal;
	string command = "";
	while(command != "end"){
		getline(cin, command);
		terminal.parseCommand(command, log_file);
	}

	log_file.close();
	return 0;
}
