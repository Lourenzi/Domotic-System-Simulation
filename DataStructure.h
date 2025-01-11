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
    //vector<string> accensioni;    /*salvo in ordine le accensioni che sono avvenute*/
    
public:
    
    DataStructure(); /*viene creato allínizio quando non ci sono eventi ancora eseguiti*/
    
    void set (Device device, bool status);
    void set (Device device, int start_device, int stop_device);
    void set (Device device, int start_device);
    void rm (Device device);
    
    vector<string> get_device_in_order ();
    
    void stampa ();
    
    void sort(EntryStructure entry);
    void elimina(int i);
};

#endif
