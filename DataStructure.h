//
//  DataStructure.h
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//

#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H


#include <iostream>
#include <string>
#include <vector>

#include "Device.h"
#include "EntryStructure.h"
#include "time.h"

using namespace std;
class DataStructure
{
private:
    vector<EntryStructure> eventi;
public:
    DataStructure(); /*viene creato allínizio quando non ci sono eventi ancora eseguiti*/
    
    void set (Device device, bool status, int time);
    void set (Device device, int start_device, int stop_device);
    void rm (Device device, string name,int now);
    
    void stampa ();
    
    void sort(EntryStructure entry);
};

#endif
