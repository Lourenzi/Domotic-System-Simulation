//
//  device.h
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//
#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>

#include <stdexcept>
using namespace std;

class Device
{
public:
    Device () { throw invalid_argument("non e possibile creare un oggetto con queste caratteristiche"); };
    
    Device (string name_device, double consume_device)
    {
        name = name_device;
        consume = consume_device;
        start = -1;
        end = -1;
        status = false;
        
        bool automatic = false;
        int durata_ciclo = -1;
    };
    
    Device (string name_device, double consume_device, int ciclo)
    {
        name = name_device;
        consume = consume_device;
        start = -1;
        end = -1;
        status = false;
        
        bool automatic = true;
        int durata_ciclo = ciclo;
    }
    
    string get_device_name () {return name;};     void modify_device_name(string newName) {name = newName;};
    double get_device_consume () {return consume;};     void modify_device_consume(double newConsume) {consume = newConsume;};
    int get_device_start () {return start;};    void modify_device_start(int newStart) {start = newStart;};
    int get_device_end () {return end;};    void modify_device_end(int newEnd) {end = newEnd;};
    bool is_device_on () {return status;};      void modify_device_status(bool newStatus) {status = newStatus;};
    
private:
    string name; /*viene assegnato con il costruttore (main)*/
    double consume; /*viene assegnato con il costruttore (main)*/
    int start;
    int end;
    bool status;
    
    bool automatic;
    int durata_ciclo;
};


/*class DeviceAutomatico
{
public:
    DeviceAutomatico () {throw invalid_argument("non e possibile creare un oggetto automatico con queste caratteristiche");};
    DeviceAutomatico (string name_device, double consume_device, int ciclo_device)
    {
        name = name_device;
        consume = consume_device;
        durata_ciclo = ciclo_device;
        start = -1;
        end = -1;
        status = false;
    };
private:
    int durata_ciclo;
};*/

#endif
