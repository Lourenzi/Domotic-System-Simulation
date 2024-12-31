//
//  device.h
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//
#include <iostream>
#include <string>

using namespace std;

class Device
{
public:
    Device ();
    Device (string name_device, double consume_device, bool automatic_device)
    { name = name_device; consume = consume_device; automatic = automatic_device;};
    
    virtual void set (bool status) = 0;
    virtual void set (int start_device, int stop_device) = 0;
    virtual void rm (string name) = 0;
    virtual void show (string name) = 0;
    
protected:
    int ID = -1; /*viene assegnato durante DataStructure*/
    string name; /*viene assegnato con il costruttore (main)*/
    double consume; /*viene assegnato con il costruttore (main)*/
    bool automatic; /*viene assegnato con il costruttore (main)*/
    int start;
    int end;
    bool on;
};
