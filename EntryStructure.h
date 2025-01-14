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

    int keyTime;                                            /*chiave della entry evento*/
    string element;                                         /*nome del device soggetto dellévento*/
    bool on;                                                /*tipo di entry (true = accensione, false = spegnimento)*/
    double power;                                           /*energia usata/prodotta dal dispositivo*/
    int id_element;                                         /*id identificativo dellévento*/
    bool always_on;                                         /*tipo di dispositivo (true = always on, false = normale)*/
    
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
    
    /*FUNZIONI GET*/
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
    
    
    /*funzione per copiare le entry*/
    EntryStructure copy (EntryStructure vecchio)
    {
        EntryStructure nuovo (vecchio.entry_get_keyTime(), vecchio.entry_get_element(), vecchio.entry_get_status(), vecchio.entry_get_power(), vecchio.entry_get_id_element(), vecchio.entry_is_always_on());
        return nuovo;
    };
};

/*classe usata per il vettore dei dispositivi accesi in questo momento*/
class EntryAccesi
{
private:
    
    string name;                                            /*nome del dispositivo a cui e'collegato lévento*/
    int id_element;                                         /*id del dispositivo a cui eçollegato lévento*/
    int power;                                              /*potenza del dispositivo a cui eçollegato lévento*/
        
public:
    
    EntryAccesi(string nome_dispositivo, int potenza, int ID)
    {
        name = nome_dispositivo;
        power = potenza;
        id_element = ID;
    };
    
    
    /*FUNZIONI GET*/
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
