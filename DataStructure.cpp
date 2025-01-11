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

Time get_Time()
{
    return tempo;
}

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
    eventi.insert(eventi.begin() + counter, entry); /*aggiunge una locazione nel vettore pirma di quello che accadrebbe subito dopo*/
}

vector<EntryAccesi> DataStructure::get_device_in_order()
{
    vector<EntryAccesi> accensioni;
    int limite = 0;
    for (int i=0; i<eventi.size(); i++)
    {
        if (eventi[i].get_keyTime()<= tempo.get_currentTime())
        {
            limite++;
        }
    }

    for (int i =0; i< limite; i++)
    {
        if (eventi[i].get_status() == true)
        {
            EntryAccesi info (eventi[i].get_element(), eventi[i].get_power());
            accensioni.insert(accensioni.begin(), info);
        }
        else
        {
            for (int f=0; f<accensioni.size(); f++)
            {
                if (accensioni[f].get_Name() == eventi[i].get_element())
                {
                    for (int j = f; j<accensioni.size()-1; j++)
                    {
                        accensioni[j]  = accensioni[j+1];
                    }
                }
            }
        }
    }
    return accensioni;
}

void DataStructure::elimina (int f)
{
    for (int i = f; i < eventi.size()-1; i++)
    {
        eventi[i] = eventi[i+1];
    }
    eventi.pop_back();
}

void DataStructure::set(Device device, bool on)  /*viene settato un dispositivo on o off*/   /*ho bisogno di time perche non so quando siamo*/
{
    if (on) /*caso in cui lo debba accendere*/
    {
        if (device.is_device_on()) throw invalid_argument("oggetto gia acceso");   /*se e gia acceso non posso accenderlo*/
        else    /*seno*/
        {
            EntryStructure entryInizio (tempo.get_currentTime(), device.get_device_name(), true/*accendo*/, device.get_device_consume()); /*creo lévento accensione dispositivo*/
            
            /*cambio le informazioni dellóggetto*/
            device.modify_device_start(tempo.get_currentTime());
            device.modify_device_status(true); /*current time = momento in cui si accende il dispositivo*/
            
            /*debug*/ cout<< "orario collegato con láccensione del dispositivo: " << entryInizio.get_keyTime() << endl;
            
            if (device.is_device_automatic())
            {
/*CONTROLLO*/   /*devo controllare che in questo intervallo io non abbia programmao láccnesione del dispositivo in precedenza*/
                for (int i=0; i<eventi.size(); i++)
                {
                    if (eventi[i].get_keyTime()>tempo.get_currentTime() && eventi[i].get_keyTime()<(tempo.get_currentTime()+device.get_device_timer())) /*trovo un accensione del dispositivo*/
                        /*devo eliminare questa programmazione sia accensione che spegnimento*/
                    {
                        elimina (i);
                        
                        for (int f=i; f<eventi.size(); f++)
                        {
                            /*se ce accensione ce anche spegnimento -> cerco acnhe spegnimento*/
                            if (eventi[f].get_element() == device.get_device_name() && eventi[f].get_status() == false) /*trovo*/
                            {
                                elimina (f);
                            }
                        }
                    }
                }
                
                cout << "durata ciclo dispositivo: " << device.get_device_timer() << endl;
                EntryStructure entryFine (tempo.get_currentTime() + device.get_device_timer(), device.get_device_name(), false, device.get_device_consume());
                
                /*aggiorno le informazioni del device*/
                device.modify_device_end(tempo.get_currentTime() + device.get_device_timer());
                
                /*debug*/ cout<< "orario a cui e collegato lo spegnimetno del dispositivo: " << entryFine.get_keyTime() << endl;
                
                sort (entryInizio); /*metto nellórdine corretto la entry iniziale*/
                sort (entryFine);   /*so che spengo il dispositivo a mezzanotte*/
            }
            else
            {
/*CONTROLLO*/   for (int i =0; i<eventi.size(); i++)
                {
                    if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_keyTime()>tempo.get_currentTime())
                    {
                        elimina (i);
                        
                        for (int f=i; f<eventi.size(); f++)
                        {
                            /*se ce accensione ce anche spegnimento -> cerco acnhe spegnimento*/
                            if (eventi[f].get_element() == device.get_device_name() && eventi[f].get_status() == false) /*trovo*/
                            {
                                elimina (f);
                                break;
                            }
                        }
                    }
                }
                
                EntryStructure entryFine ((60*24)+1, device.get_device_name(), false/*spengo*/, device.get_device_consume());    /*creo lévento spegnimento dispositivo*/
                
                device.modify_device_end((60*24)+1);
                
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
            EntryStructure entryFine (tempo.get_currentTime(), device.get_device_name(), false/*spengo*/, device.get_device_consume()); /*spegno il dispositivo in un determinato momento (ora)*/
            
            device.modify_device_end(tempo.get_currentTime()); /*modifico lo spegnimetno dell dispositivo a ora*/
            
            /*debug*/ cout << "orario collegato allo psegnimetno del dispositivo: " << entryFine.get_keyTime() << endl;
            
            sort (entryFine);   /*deve essere riordinato allínterno dello storico eventi*/
        }
    }
}

void DataStructure::set (Device device, int moment) /*accesione programmata*/
{
    if (moment < tempo.get_currentTime()) throw invalid_argument("non si puo aplicare una pianificazion al passato");
    
    if (device.is_device_automatic())
    {
        int posizione_inizio = 0;
        int posizione_fine = 0;
        for (int i =0; i< eventi.size(); i++)
        {
            if (eventi[i].get_keyTime() <= moment)
            {
                posizione_inizio ++;
            }
            if (eventi[i].get_keyTime() <= moment + device.get_device_timer())
            {
                posizione_fine ++;
            }
        }
        
        //posso avere sia la fine che linizio di una programmazione allínterno del mio intervallo
        //intanto vediamo se ce una delle due
        bool entrato = false;
        for (int i = posizione_inizio; i <= posizione_fine; i++) //controllo che non ci fosse gia una pianificazione impostata
        {
            if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_keyTime() > moment)
            {
                //ce una programmazione prevista per dopo il momento che ho detto io
                //e una programmazione di accensione o spegnimento?
                if (eventi[i].get_status()) //programmazione di accensione
                {
                    for (int f = i; f < eventi.size()-1; f++)
                    {
                        eventi[f] = eventi[f+1];
                    }
                    //devo cercare dopo la entry di spegnimento e toglierla
                    for (int f = i; f < eventi.size(); f++)
                    {
                        if (eventi[f].get_element() == device.get_device_name())
                        {
                            for (int j = f; j < eventi.size()-1; j++)
                            {
                                eventi[j] = eventi[j+1];
                            }
                        }
                    }
                }
                else //programmazione di spegnimento
                {
                    //devo cercare la entry di accensione ma devo fare attenzione che sia dopo current time
                    //prima di togliere le entry
                    bool cancellare = true;
                    int posizione_iniziale = 0;
                    for (int f = i; f > 0; f--)
                    {
                        if (eventi[f].get_element() == device.get_device_name())
                        {
                            posizione_iniziale = f;
                            if (eventi[f].get_keyTime() >= tempo.get_currentTime())
                            {
                                cancellare = false;
                                throw invalid_argument("si sta posizionando una programmazione prima che quella precedente finisca");
                            }
                        }
                    }
                    //posso cancellare entrambe le entry
                    for (int f = i; f < eventi.size()-1; f++)
                    {
                        eventi[f] = eventi[f+1];
                    }
                    eventi.pop_back();
                    
                    for (int f = posizione_iniziale; f < eventi.size()-1; f++)
                    {
                        eventi[f] = eventi[f+1];
                    }
                    eventi.pop_back();
                }
                
            }
        }
        
        EntryStructure entryInizio (moment, device.get_device_name(), true, device.get_device_consume());
        sort (entryInizio);
        EntryStructure entryFine ((60*24)+1, device.get_device_name(), false, device.get_device_consume());
        sort (entryFine);
    }
    else
    {
        int posizione = 0;
        for (int i = 0; i < eventi.size(); i++)
        {
            if (eventi[i].get_keyTime() <= moment) posizione ++;
        }
        //controllo che non ci siano entry con lo stesso nome che si chiudono o si aprono e chiiudono all interno dellíntervallo
        bool trovato = false;
        for (int i = posizione; i < eventi.size(); i ++)
        {
            if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == true) //e pianificata un accensione
            {
                for (int f = i; f < eventi.size(); f++)
                {
                    if (eventi[f].get_element() == device.get_device_name() && eventi[i].get_status() == false)
                    {
                        //elimino questa entry
                        eventi.erase(f);
                    }
                }
            }
        }
    }
}

void DataStructure::set (Device device, int start_device, int stop_device) /*setto accensione e spegnimento*/
{
    /*modifico informazioni di accensione e spegnimento del dispositivo*/
    device.modify_device_start(start_device);
    device.modify_device_end(stop_device);
    
    if (device.is_device_automatic()) throw invalid_argument("ha un tempo prefissato");

    EntryStructure entryInizio (start_device, device.get_device_name(), true, device.get_device_consume()); /*creo la entry che mi rapprsenta láccensione*/
    EntryStructure entryFine (stop_device, device.get_device_name(), false, device.get_device_consume()); /*creo la entry che mi rappresenta lo spegnimento*/
    
    int time1 = -1;
    int time2 = -1;   /*salvo il momento (potevo salvarmi anche solamente la posizione ma chill)*/
    int position_time1 = 0;
    int position_time2 = 0; /*cosi so da dove ho preso le informazioni*/
    
    bool entrato1 = false;
    bool entrato2 = false;
    
    for (int i =0; i<eventi.size(); i++)
    {
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == true)
        {
            time1 = eventi[i].get_keyTime();
            position_time1 = i;
            entrato1 = true;
        }
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false)
        {
            time2 = eventi[i].get_keyTime();
            position_time2 = i;
            entrato2 = true;
        }
        
        if (entrato1 && entrato2)
        {
            if (!(start_device<time1 && stop_device<time1) && !(start_device>time2 && stop_device>time2))
            {
                for (int i = position_time2; i<eventi.size()-1; i++)
                {
                    eventi[i] = eventi[i+1];
                }
                
                eventi.pop_back();
                
                for (int i = position_time1; i<eventi.size()-1; i++)
                {
                    eventi[i] = eventi[i+1];
                }
                
                eventi.pop_back();
                break;
            }
            else {entrato1 = false; entrato2 = false;}
        }
    }
    /*se non sono in uno dei tre casi sopra vuol dire che il dispositivo non fa nulla in questo frangente di tempo*/
    sort(entryInizio); /*butto dentro e riordino*/
    sort(entryFine);
}

void DataStructure::rm (Device device) /*devo mettere now seno potrei togliere uno spegnimento passato e non ha senso*/
{
    device.modify_device_end((60*24)+1);
    
    for (int i = tempo.get_currentTime(); i< eventi.size(); i++)    /*cerco in cio che accadra da now in poi*/
    {
        if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == false && eventi[i].get_keyTime()!=(60*24)+1)
            /*se il time della entry a quel valore vuol dire che non si spegne in questa giornata*/
        {
            for (int j = i; j<eventi.size()-1; j++)
            {
                eventi[j] = eventi[j+1];
            }
            eventi.pop_back();
            break;
        }
    }
    EntryStructure entryFine ((60*24)+1, device.get_device_name(), false, device.get_device_consume());
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


