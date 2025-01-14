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
#include <fstream>

#include "Device.h"
#include "EntryStructure.h"
#include "time.h"

using namespace std;
class DataStructure
{
private:
    
    vector<EntryStructure> eventi;                                      /*vettore in cui salvo le entry eventi*/
    
public:
    
    DataStructure();
    
    void set (Device &device, bool status);                             /*set riguardante tempo attuale*/
    void set (Device &device, int start_device, int stop_device);       /*set con accensione e spegnimento programmati*/
    void set (Device &device, int start_device);                        /*set con accensione programmata*/
    void rm (Device &device);                                           /*remove programmazione device*/
    
    vector<EntryAccesi> get_device_in_order ();                         /*riordina gli eventi dal meno recente al piu recente*/
    
    double getCurrentPower(void);                                       /*dice quanta energia stiamo usando*/
    void checkPower(void);                                              /*spegne i dispositivi se siamo sopra di energia*/
    void accender();                                                    /*accende e spegne i dispositivi*/
    
    void set_Time(int newTime);                                         /*cambia la variabile tempo*/
    Time get_Time();                                                    /*restituisce valore di tempo*/
    void sort(EntryStructure entry);                                    /*riordina le entry eventi*/
    void elimina(int i);                                                /*elimina un elemento da un vettore di entry*/
};

#endif
