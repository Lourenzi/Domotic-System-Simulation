//
//  EntryStructure.h
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//

#ifndef ENTRYSTRUCTURE_H
#define ENTRYSTRUCTURE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class EntryStructure
{
private:
    int keyTime;
    string element;
    bool on;
public:
    EntryStructure(int time, string name, bool onStatus) {keyTime = time; element = name; on = onStatus;};
    /*creo una tripletta momento evento-id elemtno-nuovo stato elemtno*/
    int get_keyTime() {return keyTime;};
    string get_element() {return element;};
    bool get_status() {return on;};
};
#endif

