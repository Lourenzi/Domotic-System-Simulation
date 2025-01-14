//Created by Lorenzo


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Interface.h"
#include "DataStructure.h"
using namespace std;

int main(){

	Interface terminal;
	string command = "";
	cout<<"||||| Sistema Domotico |||||\n\n"<<"Scrivere 'end' per terminare il programma\n\n";

	while(command != "end"){
		cout<<">> ";
		getline(cin, command);
		if(command != "end") { terminal.parseCommand(command); }
	}

	return 0;
}
