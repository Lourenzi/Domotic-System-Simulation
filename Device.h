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
        /*costruttore vuoto setta tutte le variabili nel loro stato di default*/
    };
    
    /*costruttore utilizzabile da tutti i dispositivi*/
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
    
    /*costruttore utilizzabile da quelli automatici*/
    Device (string name_device, double consume_device, int ciclo, int id_device, bool is_always_on)
    {
        if (is_always_on && ciclo != 0)
        {
            cout<<"non e possibile creare il dispositivo \" "<< name_device << " \" perche automatico e allo stesso tempo sempre attivo" << endl;
            cout<<"verra' creato un oggetto device di default con:"<< endl;
            cout<< "nome: " << name_device << endl << "consumo: " << consume_device << endl << "id Device: " << id_device << endl << "automatic: " << false << endl << "always on: false" << endl;
            Device (name_device, consume_device, id_device, false);
        }
        else
        {
            name = name_device;
            consume = consume_device;
            ID = id_device;
            durata_ciclo = ciclo;
            
            /*start e end vengono settati automatiamente a zero*/
            
            always_on = is_always_on;
            status = false;
            automatic = true;
        }
    }
    
    
    /*FUNZIONI GET*/
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
    
    
private:
    
    string name;
    double consume;
    int ID;
    int start;
    int end;
    int timeOn;
    int durata_ciclo;
    bool status;
    bool always_on;
    bool automatic;
};

#endif
