//
//  DataStructure.h
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//
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
    
    void set (Device device, bool status);
    void set (Device device, int start_device, int stop_device);
    void set (Device device, int start_device);
    void rm (Device device);
    
    void stampa ();
    
    void sort(EntryStructure entry);
};
