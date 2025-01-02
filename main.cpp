#include <iostream>
#include <string>
#include <vector>
#include "Interface.h"

using namespace std;

int main(){

	string command = "";

	while(command != "end"){
		getline(cin, command);
		parseCommand(command);
	}

	return 0;
}