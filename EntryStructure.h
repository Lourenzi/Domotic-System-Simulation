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
    int power;
    
public:
    
    EntryStructure(int time, string name, bool onStatus, int potenza)
    {
        keyTime = time;
        element = name;
        on = onStatus;
        power = potenza;
    };
    
    /*creo una tripletta momento evento-id elemtno-nuovo stato elemtno*/
    int get_keyTime()
    {
        return keyTime;
    };
    
    string get_element()
    {
        return element;
    };
    
    bool get_status()
    {
        return on;
    };
    
    int get_power()
    {
        return power;
    };
    
    EntryStructure copy (EntryStructure vecchio)
    {
        EntryStructure nuovo (vecchio.get_keyTime(), vecchio.get_element(), vecchio.get_status(), vecchio.get_power());
        return nuovo;
    };
};

class EntryAccesi
{
private:
    
    string name;
    int power;
    
public:
    
    EntryAccesi(string nome_dispositivo, int potenza)
    {
        name = nome_dispositivo;
        power = potenza;
    };
    
    string get_Name()
    {
        return name;
    };
    
    int get_Power()
    {
        return power;
    };
};

#endif
