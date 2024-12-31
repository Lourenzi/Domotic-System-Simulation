//
//  DataStructure.cpp
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//

#include <iostream>
#include <string>
#include <vector>
#include "DataStructure.h"

#include <stdexcept>

using namespace std;

DataStructure::DataStructure(){}; /*vector degli elementi e gia vuoto*/

void DataStructure::sort(EntryStructure entry) /*riordinare il vettore in base al tempo che caratterizza ogni elemento*/
{
    int timeEntry = entry.get_keyTime();
    int counter = 0;
    for (int i =0; i<eventi.size(); i++)
    {
        if (eventi[i].get_keyTime()>timeEntry)
        {
            counter = i;
            break;
        }
    }
    eventi.insert(eventi.begin() + counter, entry);
}

void DataStructure::set(bool status, int time)
{
    if (status) /*caso in cui lo debba accendere*/
    {
        if (on) throw invalid_argument("oggetto gia acceso");
        else
        {
            EntryStructure entryInizio (time, name, status);
            EntryStructure entryFine (60*24, name, !status);
            sort (entryInizio);
            eventi.insert(eventi.begin() + eventi.size(), entryFine);
        }
    }
    else /*caso in cui lo debba spegnere*/
    {
        if (!on) throw invalid_argument("oggetto gia spento");
        else /*devo spegnerlo prima del previsto*/
        {
            for (int i =time; i<eventi.size(); i++) /*cerco quando avrei dovuto spegnerlo*/
            {
                if (eventi[i].get_element() == name && eventi[i].get_status() == true) /*trovo il momento*/
                {
                    for (int f = i; f<eventi.size()-1; f++) eventi[f] = eventi[f+1]; /*slitto di uno a sinistra per eliminarlo*/
                    eventi.pop_back(); /*tolgo lútima che si sara duplicato*/
                }
            }
            EntryStructure entry (time, name, status); /*creo lo spegnimento corretto*/
            sort (entry);
        }
    }
}

void DataStructure::set (int start_device, int stop_device)
{
    
}
