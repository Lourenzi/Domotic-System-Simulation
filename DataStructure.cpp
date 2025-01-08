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
#include "ListaDevice.h"
#include "Device.h"

#include <stdexcept>

using namespace std;

Time tempo;
ListaDevice lista;

DataStructure::DataStructure() {}; /*creo la linea temporale*/  /*vector degli elementi e gia vuoto*/

void DataStructure::sort(EntryStructure entry) /*riordinare il vettore in base al tempo che caratterizza ogni evento*/
{
    int timeEntry = entry.get_keyTime();    /*momento di quel evento*/
    int counter = 0;
    for (int i =0; i<eventi.size(); i++)
    {
        if (eventi[i].get_keyTime()>=timeEntry) /*prende il primo piu grande perche poi brekka*/
        {
            counter = i;
            break;
        }
    }
    eventi.insert(eventi.begin() + counter, entry); /*aggiunge una locazione nel vettore pirma di quello che accadrebbe ubito dopo*/
}

void DataStructure::set(Device device, bool on)  /*viene settato un dispositivo on o off*/   /*ho bisogno di time perche non so quando siamo*/
{
    device.get_schedaTecnica();
    if (on) /*caso in cui lo debba accendere*/
    {
        if (device.is_device_on()) throw invalid_argument("oggetto gia acceso");   /*se e gia acceso non posso accenderlo*/
        else    /*seno*/
        {
            EntryStructure entryInizio (tempo.get_currentTime(), device.get_device_name(), true/*accendo*/); /*creo lévento accensione dispositivo*/
            
            /*cambio le informazioni dellóggetto*/
            device.modify_device_start(tempo.get_currentTime());
            device.modify_device_status(true); /*current time = momento in cui si accende il dispositivo*/
            
            /*debug*/ cout<< "orario collegato con láccensione del dispositivo: " << entryInizio.get_keyTime() << endl;
            
            if (device.is_device_automatic())
            {
                device.modify_device_end(tempo.get_currentTime() + device.get_device_timer());
                
                cout << "durata ciclo dispositivo: " << device.get_device_timer() << endl;
                EntryStructure entryFine (tempo.get_currentTime() + device.get_device_timer(), device.get_device_name(), false);
                
                /*debug*/ cout<< "orario a cui e collegato lo spegnimetno del dispositivo: " << entryFine.get_keyTime() << endl;
                
                sort (entryInizio); /*metto nellórdine corretto la entry iniziale*/
                sort (entryFine);   /*so che spengo il dispositivo a mezzanotte*/
            }
            else
            {
                device.modify_device_end((60*24)+1);
                
                EntryStructure entryFine ((60*24)+1, device.get_device_name(), false/*spengo*/);    /*creo lévento spegnimento dispositivo*/
                
                /*debug*/ cout << "orario a cui e collegato lo spegnimetno del dispositivo: " << entryFine.get_keyTime() << endl;
                /*debug*/ cout << "nome del dispositivo: " << entryFine.get_element() << endl;
                
                sort (entryInizio); /*metto nellórdine corretto la entry iniziale*/
                eventi.insert(eventi.begin() + eventi.size(), entryFine);   /*so che spengo il dispositivo a mezzanotte*/
            }
        }
    }
    else /*caso in cui lo debba spegnere*/
    {
        if (!device.is_device_on()) throw invalid_argument("oggetto gia spento");  /*se e gia spento non posso spegnerlo*/
        else /*devo spegnerlo prima del previsto*/
        {
            for (int i = tempo.get_currentTime(); i<eventi.size(); i++) /*cerco quando avrei dovuto spegnerlo*/
            /*ogni volta che qualcosa si accende devo avere anche línformazione di quando si spegne*/
            {
                if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false/*spengo*/) /*trovo il momento*/
                {
                    for (int f = i; f<eventi.size()-1; f++) eventi[f] = eventi[f+1]; /*slitto di uno a sinistra per eliminarlo*/
                    /*slitto tutto perche non e detto che fosse a mezzanotte, poteva pure essere impostato come spegnimetno*/
                    eventi.pop_back(); /*tolgo lútima che si sara duplicato*/
                    break;
                }
            }
            EntryStructure entry (tempo.get_currentTime(), device.get_device_name(), false/*spengo*/); /*spegno il dispositivo in un determinato momento (ora)*/
            
            device.modify_device_end(tempo.get_currentTime()); /*modifico lo spegnimetno dell dispositivo a ora*/
            
            /*debug*/ cout << "orario collegato allo psegnimetno del dispositivo: " << entry.get_keyTime() << endl;
            
            sort (entry);   /*deve essere riordinato allínterno dello storico eventi*/
        }
    }
    device.get_schedaTecnica();
}

void DataStructure::set (Device device, int moment) /*accesione programmata*/
{
    if (device.is_device_automatic())
    {
        EntryStructure entryInizio (moment, device.get_device_name(), true);
        sort (entryInizio);
    }
    else
    {
        if (device.is_device_on()) /*sto programmando lo psegnimento*/
        {
            
        }
        else /*sto programmando láccensione*/
        {
            set (device, moment, (60*24)+1); /*fa tutto lui*/
        }
    }
}

void DataStructure::set (Device device, int start_device, int stop_device) /*setto accensione e spegnimento*/
{
    device.get_schedaTecnica();
    
    /*modifico informazioni di accensione e spegnimento del dispositivo*/
    device.modify_device_start(start_device);
    device.modify_device_end(stop_device);
    
    if (device.is_device_automatic()) throw invalid_argument("ha un tempo prefissato");

    EntryStructure entryInizio (start_device, device.get_device_name(), true); /*creo la entry che mi rapprsenta láccensione*/
    EntryStructure entryFine (stop_device, device.get_device_name(), false); /*creo la entry che mi rappresenta lo spegnimento*/
    
    int time1 = -1; int time2 = -1;   /*salvo il momento (potevo salvarmi anche solamente la posizione ma chill)*/
    int position_time1 = 0; int position_time2 = 0; /*cosi so da dove ho preso le informazioni*/
    
    bool entrato1 = false;  bool entrato2 = false;
    for (int i =0; i<eventi.size(); i++)
    {
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == true)
        {time1 = eventi[i].get_keyTime(); position_time1 = i; entrato1 = true;}
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false)
        {time2 = eventi[i].get_keyTime(); position_time2 = i; entrato2 = true;}
        
        if (entrato1 && entrato2)
        {
            if (!(start_device<time1 && stop_device<time1) && !(start_device>time2 && stop_device>time2))
            {
                for (int i = position_time2; i<eventi.size()-1; i++) {eventi[i] = eventi[i+1];}
                eventi.pop_back();
                for (int i = position_time1; i<eventi.size()-1; i++) {eventi[i] = eventi[i+1];}
                eventi.pop_back();
                break;
            }
            else {entrato1 = false; entrato2 = false;}
        }
    }
    /*se non sono in uno dei tre casi sopra vuol dire che il dispositivo non fa nulla in questo frangente di tempo*/
    sort(entryInizio); /*butto dentro e riordino*/
    sort(entryFine);
    
    device.get_schedaTecnica();
}

void DataStructure::rm (Device device) /*devo mettere now seno potrei togliere uno spegnimento passato e non ha senso*/
{
    device.modify_device_end((60*24)+1);
    
    for (int i = tempo.get_currentTime(); i< eventi.size(); i++)    /*cerco in cio che accadra da now in poi*/
    {
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false && eventi[i].get_keyTime()!=(60*24)+1)
            /*se il time della entry a quel valore vuol dire che non si spegne in questa giornata*/
        {
            for (int j = i; j<eventi.size()-1; j++) eventi[j] = eventi[j+1];
            eventi.pop_back();
            break;
        }
    }
    EntryStructure entryFine ((60*24)+1, device.get_device_name(), false);
    /*metto (60*24)+1 perche non e un orario ma e lidea che resta acceso finche non lo spengo io*/
    sort(entryFine);
}

void DataStructure::stampa()
{
    for (int i =0; i<eventi.size(); i++)
    {
        int orario = eventi[i].get_keyTime();
        int ora = orario / 60;
        int minuti = orario % 60;
        
        if (ora == 24) {cout<< "[00:00]";}
        else cout<<"["<< ora << ":" << minuti << "]";
        
        string acceso;
        if (eventi[i].get_status() == true) acceso = " si e acceso ";
        else acceso = " si e spento ";
        
        cout<< " " << eventi[i].get_element() << acceso << endl;
    }
}


