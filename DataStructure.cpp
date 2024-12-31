//
//  DataStructure.cpp
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//

#include <iostream>
#include <string>
#include <array>
#include "DataStructure.h"

using namespace std;

DataStructure::DataStructure() {}; /*variabili private gia settate di deafault*/

void DataStructure::set(bool status)
{
    if (ID == -1) /*gli devo dare uh ID valido*/
    {
        for (int i =0; i<name_id.size(); i++) if (name_id[i] == "") { name_id[i] = name; ID = i; }
        /*inserisco nellárray id_nome il nome del device e mi salvo in ID la posizione*/
    }
    for (int i = tempo; i< data.size(); i++) data[ID][i] = status; /*spento -> status = false, acceso -> status = true*/
    if (status)
    {
        start = tempo; /*inizzializzzione variabili del DEVICE*/
        end = (int)data.size()-1; /*inizzializzzione variabili del DEVICE*/
    }
    else end = tempo;
    
}

void DataStructure::set(int start_device, int stop_device)
{
    if (ID == -1) /*gli devo dare uh ID valido*/
    {
        for (int i =0; i<name_id.size(); i++) if (name_id[i] == "") { name_id[i] = name; ID = i; }
        /*inserisco nellárray id_nome il nome del device e mi salvo in ID la posizione*/
    }
    for (int i = start_device; i<= stop_device; i++) data[ID][i] = true;
    start = start_device; /*inizzializzzione variabili del DEVICE*/
    end = stop_device; /*inizzializzzione variabili del DEVICE*/
}

void DataStructure::rm(string name)
{
    if (!automatic)
    {
        for (int i = end; i<data.size(); i++) data[ID][i] = true; /*togliendo il timer */
        end = (int)data.size()-1;
    }
}
