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

using namespace std;
class DataStructure : public Device
{
private:
    vector<EntryStructure> eventi;
public:
    DataStructure(); /*viene creato allínizio quando non ci sono eventi ancora eseguiti*/
    void set (bool status, int time) override;
    void set (int start_device, int stop_device) override;
    void rm (string name) override;
    
    void sort(EntryStructure entry);
};
