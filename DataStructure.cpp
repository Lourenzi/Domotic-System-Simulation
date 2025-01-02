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
        if (eventi[i].get_keyTime()>timeEntry) /*prende il primo piu grande perche poi brekka*/
        {
            counter = i;
            break;
        }
    }
    eventi.insert(eventi.begin() + counter, entry); /*aggiunge una locazione nel vettore pirma di quello che accadrebbe ubito dopo*/
}

void DataStructure::set(Device device, bool on, int moment)  /*viene settato un dispositivo on o off*/   /*ho bisogno di time perche non so quando siamo*/
{
    /*controllo che non sia una azione nel passato*/
    if (tempo.get_currentTime() > moment) throw invalid_argument("non si puo cambiare il passato");
        
    if (on) /*caso in cui lo debba accendere*/
    {
        if (device.is_device_on()) throw invalid_argument("oggetto gia acceso");   /*se e gia acceso non posso accenderlo*/
        else    /*seno*/
        {
            EntryStructure entryInizio (moment, device.get_device_name(), true/*accendo*/);    /*creo lévento accensione dispositivo*/
            EntryStructure entryFine ((60*24)+1, device.get_device_name(), false/*spengo*/);    /*creo lévento spegnimento dispositivo*/
            sort (entryInizio); /*metto nellórdine corretto la entry iniziale*/
            eventi.insert(eventi.begin() + eventi.size(), entryFine);   /*so che spengo il dispositivo a mezzanotte*/
        }
    }
    else /*caso in cui lo debba spegnere*/
    {
        if (!device.is_device_on()) throw invalid_argument("oggetto gia spento");  /*se e gia spento non posso spegnerlo*/
        else /*devo spegnerlo prima del previsto*/
        {
            for (int i =moment; i<eventi.size(); i++) /*cerco quando avrei dovuto spegnerlo*/
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
            EntryStructure entry (moment, device.get_device_name(), false/*spengo*/); /*spegno il dispositivo in un determinato momento (ora)*/
            sort (entry);   /*deve essere riordinato allínterno dello storico eventi*/
        }
    }
}

void DataStructure::set (Device device, int start_device, int stop_device) /*setto accensione e spegnimento*/
{
    /*la programmazione penso che non possa essere presa se va in contrasto con una precedente...*/
    /*oppure se ci va in contrasto elimino quella precedente cosi risolvo il problema*/
    EntryStructure entryInizio (start_device, device.get_device_name(), true); /*creo la entry che mi rapprsenta láccensione*/
    EntryStructure entryFine (stop_device, device.get_device_name(), false); /*creo la entry che mi rappresenta lo spegnimento*/
    /*prima di inserire i due eventi allínterno dello storico verifico che abbia senso inserirli*/
    
    int time1 = 0; int time2 = 0;   /*salvo il momento (potevo salvarmi anche solamente la posizione ma chill)*/
    int position_time1 = 0; int position_time2 = 0; /*cosi so da dove ho preso le informazioni*/
    for (int i =0; i<eventi.size(); i++)
    {
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == true)
            {time1 = eventi[i].get_keyTime(); position_time1 = i;}
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false)
            {time2 = eventi[i].get_keyTime(); position_time2 = i;}
        
    }
        
    if (!(start_device<time1 && stop_device<time1) && !(start_device>time2 && stop_device>time2))
    { /*in questo caso vanno eliminate queste azioni e sostituite con le nuove*/
        for (int i = position_time2; i<eventi.size()-1; i++) {eventi[i] = eventi[i+1];}
        eventi.pop_back();
        for (int i = position_time1; i<eventi.size()-1; i++) {eventi[i] = eventi[i+1];}
        eventi.pop_back();
    }
    /*se non sono in uno dei tre casi sopra vuol dire che il dispositivo non fa nulla in questo frangente di tempo*/
    sort(entryInizio); /*butto dentro e riordino*/
    sort(entryFine);
}

void DataStructure::rm (Device device, string nameRemove, int now) /*devo mettere now seno potrei togliere uno spegnimento passato e non ha senso*/
{
    for (int i = now; i< eventi.size(); i++)    /*cerco in cio che accadra da now in poi*/
    {
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false && eventi[i].get_keyTime()!=(60*24)+1)
            /*se il time della entry a quel valore vuol dire che non si spegne in questa giornata*/
        {
            for (int j = i; j<eventi.size(); j++) eventi[j] = eventi[j+1];
            eventi.pop_back();
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
        cout<<"["<< ora << ":" << minuti << "]";
        cout<<" lóggetto " << eventi[i].get_element() << " si trova in uno stato " << eventi[i].get_status()<<endl;
    }
}


