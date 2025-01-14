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
    Device ()
    {
        
    };
    
    Device (string name_device, double consume_device, int id_device, bool is_always_on)
    {
        name = name_device;
        consume = consume_device;
        /*start e end vengono settati automatiamente vuoti*/
        ID = id_device;
        
        always_on = is_always_on;
        status = false;
        
        automatic = false;
        durata_ciclo = -1;
    };
    
    Device (string name_device, double consume_device, int ciclo, int id_device, bool is_always_on)
    {
        name = name_device;
        consume = consume_device;
        /*start e end vengono settati automatiamente vuoti*/
        ID = id_device;
        
        always_on = is_always_on;
        status = false;
        
        automatic = true;
        durata_ciclo = ciclo;
    }
    
    
    
    string get_device_name ()
    {
        return name;
    };
    void modify_device_name(string newName)
    {
        name = newName;
    };
    
    
    
    double get_device_consume ()
    {
        return consume;
    };
    void modify_device_consume(double newConsume)
    {
        consume = newConsume;
    };
    
    
    
    int get_device_start ()
    {
        return start;
    };
    void modify_device_start(int newStart)
    {
        start = newStart;
    };
    
    
    
    int get_device_end ()
    {
        return end;
    };
    void modify_device_end(int newEnd)
    {
        end = newEnd;
    };
    
    
    
    int get_device_timeOn()
    {
        return timeOn;
    };
    void modify_device_timeOn(int newTime)
    {
        timeOn = newTime;
    };
    
    
    int get_device_ID()
    {
        return ID;
    };
    
    
    
    bool is_device_on ()
    {
        return status;
    };
    void modify_device_status(bool newStatus)
    {
        status = newStatus;
    };
    
    
    
    bool is_device_alwaysOn()
    {
        return always_on;
    };
    
    
    
    bool is_device_automatic()
    {
        return automatic;
    };
    
    
    
    int get_device_timer()
    {
        return durata_ciclo;
    };
    
    
/*DEBUG*/ void knowAll()
    {
        cout << "nome del dispositivo " << name << endl << "id del dispositivo " << ID << endl;
        cout << "orario di accensione " << start << " e orario di spegnimento " << end << endl;
        cout << "status attuale " << status << endl;
    }
    
private:
    string name; /*viene assegnato con il costruttore (main)*/
    double consume; /*viene assegnato con il costruttore (main)*/
    int ID;
    int start; //vettore dove sono salvate tutti i minutaggi in cui si accende
    int end; //vettore in cui sono salvati tutti i minutaggi in cui si spegne
    int timeOn;
    bool status;
    
    bool always_on;
    
    bool automatic;
    int durata_ciclo;
};

#endif
