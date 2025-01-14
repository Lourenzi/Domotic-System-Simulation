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
    int id_element;
    bool always_on;
    
public:
    
    EntryStructure(int time, string name, bool onStatus, int potenza, int ID, bool AO)
    {
        keyTime = time;
        element = name;
        on = onStatus;
        power = potenza;
        id_element = ID;
        always_on = AO;
    };
    
    /*creo una tripletta momento evento-id elemtno-nuovo stato elemtno*/
    int entry_get_keyTime()
    {
        return keyTime;
    };
    
    
    string entry_get_element()
    {
        return element;
    };
    
    
    bool entry_get_status()
    {
        return on;
    };
    
    
    int entry_get_power()
    {
        return power;
    };
    
    
    int entry_get_id_element()
    {
        return id_element;
    };
    
    
    bool entry_is_always_on()
    {
        return always_on;
    }
    
    
    EntryStructure copy (EntryStructure vecchio)
    {
        EntryStructure nuovo (vecchio.entry_get_keyTime(), vecchio.entry_get_element(), vecchio.entry_get_status(), vecchio.entry_get_power(), vecchio.entry_get_id_element(), vecchio.entry_is_always_on());
        return nuovo;
    };
};

class EntryAccesi
{
private:
    
    string name;
    int id_element;
    int power;
    
public:
    
    EntryAccesi(string nome_dispositivo, int potenza, int ID)
    {
        name = nome_dispositivo;
        power = potenza;
        id_element = ID;
    };
    
    
    string entryON_get_Name()
    {
        return name;
    };
    
    
    int entryON_get_Power()
    {
        return power;
    };
    
    
    int entryON_get_id_element()
    {
        return id_element;
    };
};

#endif
