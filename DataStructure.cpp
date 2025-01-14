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
#include "EventLogger.h"

#include <stdexcept>

using namespace std;

/*creo gli oggetti che mi serviranno per límplementazione di DataStructure*/
Time tempo;                                         /*linea temporale*/
ListaDevice lista;
EventLogger logger;

DataStructure::DataStructure()                      /*costruttore oggeto DataStructure*/
{
    logger.log_updateStatus(tempo, "debug", false);     /*non ho bisogno di inizializzare nulla perche le variabili di stato vengono inizzializzate come voglio di default (vettore vuoto)*/
}

Time DataStructure::get_Time()                      /*permette accesso alla variabile time del oggetto tempo*/
{
    return tempo;
}

void DataStructure::set_Time(int newTime)           /*permette di modificare la variabile time dellóggetto tempo*/
{
    tempo.set_time(newTime);                        /*modifico current time dellóggetto*/
    
    for (int i =0; i< lista.size(); i++)            /*modifico parametri dei device AlwaysOn*/
    {
        if (lista[i].is_device_alwaysOn())
        {
            lista[i].modify_device_end(tempo.get_currentTime());
            lista[i].modify_device_timeOn(lista[i].get_device_end() - lista[i].get_device_start());
        }
    }

    accender();                                     /*accende i dispositivi programmati durante il salto teporale*/
    get_device_in_order();                          /*riordina i dispositivi in un vettore dallúltimo acceso al primo
                                                     (pop_back toglie dalla lista quello piu vecchio)*/
    checkPower();
}

void DataStructure::sort(EntryStructure entry) /*riordina il vettore eventi in base al momento in cui avviene un determinato evento*/
{
    int timeEntry = entry.entry_get_keyTime();                /*momento di quel evento*/
    
    int counter = 0;                                    /*variabile di appoggio in cui salvo dove inserire la entry evento*/
        
    for (int i =0; i<eventi.size(); i++)
    {
        if (timeEntry < eventi[i].entry_get_keyTime())        /*trova la prima entry con chiave maggiore*/
        {
            counter = i;                                /*salvo la posizione*/
            break;                                      /*esce dal ciclo*/
        }
        
        if (timeEntry >= eventi[i].entry_get_keyTime() && i == eventi.size()-1) /*se sta analizzando lúltimo ed e il maggiore allora va in ultima posizione*/
        {
            counter = (int)eventi.size();               /*salvo lúltimo indice del vettore*/
            break;                                      /*esco dal ciclo*/
        }
    }
    eventi.insert(eventi.begin() + counter, entry);    /*inserisco tra gli eventi quello attuale la posizione prima
                                                        di quello che accadrebbe subito dopo*/
    cout<<endl;
}

vector<EntryAccesi> DataStructure::get_device_in_order()    /*restituisce un vettore di ENTRY riferito ai device accesi ora*/
{
    vector<EntryAccesi> accensioni;                         /*creo la struttura*/
    
    for (int i=0; i<eventi.size(); i++)                     /*cerco dispositivi da inserire in base agli eventi accaduti*/
    {
        if (eventi[i].entry_get_keyTime()<= tempo.get_currentTime())  /*se un evento e accaduto prima di current time allora va analizzato*/
        {
            if (eventi[i].entry_get_status() == true)             /*se questo evento ha acceso qualcosa*/
            {
                /*allora va INSERITA una nuova entry nella lista*/
                EntryAccesi info (eventi[i].entry_get_element(), eventi[i].entry_get_power(), eventi[i].entry_get_id_element());
                accensioni.insert(accensioni.begin(), info);
            }
            else                              /*se questo evento ha spento un dispositivo devo togliere una entry*/
            {
                if (accensioni.size() != 1)          /*non ha senso fare questi passaggi per size = 1*/
                {
                    /*scorro tutti gli eventi per cercare láccensione associata a questo spegnimento
                    scorro il vettore da sx a dx perche gli eventi sono salvati dal piu recente al meno tecente
                    se scorressi al contrario rischierei di trovare un accensione legata a un altra programmazione*/
                    for (int f=0; f<accensioni.size(); f++)
                    {
                        if (accensioni[f].entryON_get_id_element() == eventi[i].entry_get_id_element())  /*trovo lévento*/
                        {
                            for (int j = f; j<accensioni.size()-1; j++)   /*lo sovrascrivo dal vettore*/
                            {
                                accensioni[j]  = accensioni[j+1];
                            }
                        }
                    }
                }
                accensioni.pop_back();  /*tolgo lúltimo perche e doppione*/
            }
        }
        else        /*inizio a trovare programmazioni che devono ancora avvenire*/
        {
            break;
        }
    }
    
    /*aggiungo come piu recenti i dispositivi sempre accesi
      in questo modo verranno spenti tutti quelli normali prima di qrrivare a questi*/
    for (int i =0; i<lista.size(); i++)
    {
        if (lista[i].is_device_alwaysOn())
        {
            EntryAccesi info (lista[i].get_device_name(), lista[i].get_device_consume(), lista[i].get_device_ID());
            accensioni.insert(accensioni.begin(), info);
        }
    }

    return accensioni;
}

void DataStructure::elimina (int f) /*funzione per eliminare un elemento di un elemtno DATASRTUCTURE*/
{
    for (int i = f; i < eventi.size()-1; i++)
    {
        eventi[i] = eventi[i+1];
    }
    eventi.pop_back();
}

void DataStructure::set(Device &device, bool on)  /*accendo o spengo un dispositivo in CURRENT TIME (adesso)*/
{
    if (device.is_device_alwaysOn())    /*se e' un dispositivo sempre acceso non può essere acceso nuovamente*/
    {
        cout<< device.get_device_name() << " e'un dispositivo sempre acceso, non puo avere pianificazioni di alcun tipo" << endl;
    }
    else if (on) /*caso in cui lo debba accendere*/
    {

        if (device.is_device_on())  /*se è già acceso non posso accenderlo*/
        {
            cout<<"--Dispositivo gia' acceso--"<<endl;
        }
        
        else    /*lo posso accendere*/
        {
            /*creo lévento accensione dispositivo*/
            EntryStructure entryInizio (tempo.get_currentTime(), device.get_device_name(), true/*accendo*/, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
            
            /*cambio le informazioni dellóggetto
              non hannp bisogno di accertamenti aggiuntivi per essere eseguiti*/
            device.modify_device_start(tempo.get_currentTime());
            device.modify_device_status(true);
            
            /*controllo la tipologia di dispositivo su cui applico la programmazione*/
            if (device.is_device_automatic())       /*e' automatico*/
            {
                /*devo controllare che in questo intervallo io non abbia altre programmazioni dello stesso*/
                for (int i=0; i<eventi.size(); i++)
                {
                    if (eventi[i].entry_get_id_element() == device.get_device_ID() &&
                        eventi[i].entry_get_keyTime()>tempo.get_currentTime() &&
                        eventi[i].entry_get_keyTime()<(tempo.get_currentTime()+device.get_device_timer()))
                    /*trovo un accensione del dispositivo
                     non puo essere uno spegnimento perche seno' essendo automatico o avrei trovat gia' acceso
                     devo eliminare questa programmazione sia accensione che spegnimento*/
                        
                    {
                        elimina (i);
                        
                        /*sara' lévento collegato con lo stesso dispositivo dopo lévento accensione
                         -> inizio a scorrere gli eventi da quello appena trovato (ecenti[i])*/
                        for (int f=i; f<eventi.size(); f++)
                        {
                            /*cerco entry spegnimento*/
                            if (eventi[f].entry_get_id_element() == device.get_device_ID() && eventi[f].entry_get_status() == false)/*trovo*/
                            {
                                elimina (f); /*elimino*/
                            }
                        }
                    }
                }
                
                /*creo lévento spegnimento dispositivo*/
                EntryStructure entryFine (tempo.get_currentTime() + device.get_device_timer(), device.get_device_name(), false, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
                
                /*modifico informazioni del dispositivo*/
                device.modify_device_end(tempo.get_currentTime() + device.get_device_timer());
                
                /*riordino le entry nel vettore eventi*/
                sort (entryInizio); /*entry accensione*/
                sort (entryFine);   /*entry spegnimento*/
            }
            else        /*device e di tipo MANUALE*/
            {
                /*cerco nella lista di eventi se ci sono programmazioni che vanno in conflitto*/
                for (int i =0; i<eventi.size(); i++)
                {
                    /*ne trovo una*/
                    if (eventi[i].entry_get_id_element() == device.get_device_ID() && eventi[i].entry_get_keyTime()>tempo.get_currentTime())
                    {
                        /*elimino questo evento*/
                        elimina (i);
                        
                        /*se ce accensione ce anche spegnimento -> cerco entry di spegnimento associata*/
                        for (int f=i; f<eventi.size(); f++)
                        {
                            if (eventi[f].entry_get_id_element() == device.get_device_ID() && eventi[f].entry_get_status() == false)/*trovo*/
                            {
                                elimina (f); /*elimin0*/
                                break;
                            }
                        }
                    }
                    /*non esco dal ciclo perche'non essendo automatico ce ne potrebbero essere altre*/
                }
                
                /*creo lévento spegnimento dispositivo*/
                EntryStructure entryFine ((60*24)+1, device.get_device_name(), false, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
                
                /*modifico informazioni del dispositivo*/
                device.modify_device_end((60*24)+1);
                
                /*riordino le entry nel vettore eventi*/
                sort (entryInizio); /*entry accensione*/
                eventi.insert(eventi.begin() + eventi.size(), entryFine); /*entry spegnimento*/
            }
        }
    }
    else /*caso in cui lo debba spegnere*/
    {
        if (!device.is_device_on())
        {
            cout<<"--Dispositivo gia' spento--"<<endl;  /*se e gia spento non posso spegnerlo*/
        }
        else /*caso in cui debba spegnerlo prima del previsto*/
        {
            /*cerco dove ci troviamo allínterno del vettore eventi*/
            int evento_attuale = 0;
            for (int i =0; i< eventi.size(); i++)
            {
                if (eventi[i].entry_get_keyTime() <= tempo.get_currentTime())
                {
                    evento_attuale = i;
                }
            }
            
            for (int i = evento_attuale; i<eventi.size(); i++) /*cerco quando avrei dovuto spegnerlo*/
            {
                if (eventi[i].entry_get_id_element() == device.get_device_ID() && eventi[i].entry_get_status() == false) /*trovo il momento*/
                {
                    elimina(i); /*elimino qeusto evento*/
                    break;
                    /*esco dal ciclo perche devo eliminare solo la fine della PRIMA programmazione che accade (quella in atto)
                      se dopo ci sono altre programmazioni non e un problema*/
                }
            }
            
            /*creo lévento spegnimento dispositivo*/
            EntryStructure entryFine (tempo.get_currentTime(), device.get_device_name(), false/*spengo*/, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn()); /*spegno il dispositivo in un determinato momento (ora)*/
            
            /*modifico informazioni del dispositivo*/
            device.modify_device_end(tempo.get_currentTime());
            
            /*riordino le entry nel vettore eventi*/
            sort (entryFine);
        }
    }
    
    accender(); /*serve per tenere aggiornati gli oggetti sul loro stato*/
    checkPower();   /*serve per tenere aggiornto power di quanto sto consumando*/
}

void DataStructure::set (Device &device, int moment) /*accesione programmata*/
{
    if (device.is_device_alwaysOn())    /*non posso programmare un accensione in quacosa sempre cceso*/
    {
        cout<<device.get_device_name()<<" e' un dispositivo sempre acceso, non puo avere pianificazioni di alcun tipo";
    }
    else if (moment < tempo.get_currentTime())   /*non posso applicare una programmazione nel passato*/
    {
        cout<<" non si puo aplicare una pianificazion al passato ";
    }
    
    /*divido i casi in bae al tipo di dispositivo*/
    else if (device.is_device_automatic())   /*caso dispositivo sia automatico*/
    {
        /*variabili di appogio: mi servono per individuare le locazini in cui mi troverei allínterno del vettore*/
        int posizione_inizio = 0;
        int posizione_fine = 0;
        
        for (int i =0; i< eventi.size(); i++)
        {
            /*salvo nelle variabili lúltima locazione prima di superare moment con entry.keyValue*/
            if (eventi[i].entry_get_keyTime() <= moment)
            {
                posizione_inizio ++;
            }
            
            if (eventi[i].entry_get_keyTime() <= moment + device.get_device_timer())
            {
                posizione_fine ++;
            }
        }
        
        /*controllo che non ci siano altre programmaioni in qeusto intervallo*/
        if (posizione_inizio != posizione_fine) /*vuol dire che ce qualcosa in mezzo*/
        {
            for (int i = posizione_inizio; i <= posizione_fine; i++)
            {
                if (eventi[i].entry_get_id_element() == device.get_device_ID() && eventi[i].entry_get_keyTime() > moment)
                    /*trovo una pianificazione gia presente dello stesso dispositivo*/
                {
                    /*divido i casi in base al tipo di programmazione*/
                    if (eventi[i].entry_get_status()) //programmazione di accensione
                    {
                        elimina(i);
                        
                        /*cerco la entry di spegnimento associata*/
                        for (int f = i; f < eventi.size(); f++)
                        {
                            if (eventi[f].entry_get_id_element() == device.get_device_ID()) /*trovo*/
                            {
                                elimina(f); /*elimino*/
                            }
                        }
                        
                        /*creo le entry*/
                        EntryStructure entryInizio (moment, device.get_device_name(), true, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
                        EntryStructure entryFine (moment + device.get_device_timer(), device.get_device_name(), false, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
                        
                        /*inserisco le entry*/
                        sort (entryInizio);
                        sort (entryFine);
                    }
                    else /*programmazione di spegnimento*/
                    {
                        /*cerco la entry di accensione associata
                          se di trova prima di current time devo lasciare la programmazione attuale*/
                        
                        /*variabili di appoggio*/
                        bool cancellare = true;
                        int posizione_iniziale = 0;
                        
                        for (int f = i; f > 0; f--)
                        {
                            if (eventi[f].entry_get_id_element() == device.get_device_ID())
                            {
                                posizione_iniziale = f;
                                if (eventi[f].entry_get_keyTime() >= tempo.get_currentTime())
                                {
                                    cancellare = false;
                                    cout<<"non e possibile creare una pianificazione per " << device.get_device_name() <<
                                    " perche una e gia in atto" << endl;
                                }
                            }
                        }
                        
                        if (cancellare) /*programmazione precedente non e'in atto*/
                        {
                            /*cancello entrambe le entry*/
                            elimina(i);
                            elimina(posizione_iniziale);
                            
                            /*creo le entry*/
                            EntryStructure entryInizio (moment, device.get_device_name(), true, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
                            EntryStructure entryFine (moment + device.get_device_timer(), device.get_device_name(), false, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
                            
                            /*inserisco le entry*/
                            sort (entryInizio);
                            sort (entryFine);
                        }
                    }
                }
            }
        }
    }
    else
    {
        /*creo le nuove ENTRY*/
        EntryStructure entryInizio (moment, device.get_device_name(), true, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
        
        EntryStructure entryFine ((60*24)+1, device.get_device_name(), false, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
        
        int posizione = 0;      /*variabile di appoggio = salvo indice dove salvare la ENTRY di accensione*/
        
        for (int i = 0; i < eventi.size(); i++)     /*trovo questa posizione*/
        {
            if (eventi[i].entry_get_keyTime() <= moment)
            {
                posizione ++;
            }
        }
        
        /*controllo che non ci siano gia delle programmazioni gia presenti*/
        if (posizione != eventi.size())
        /*se la programmazione di inizio si trova alla fine del vettore allora non ci sono altre programmazioni dopo*/
        {
            for (int i = posizione; i < eventi.size(); i++)
            {
                if (eventi[i].entry_get_id_element() == device.get_device_ID() && eventi[i].entry_get_status()) /*PIANIFICATA ACCENSIONE*/
                {
                    elimina(i);     /*elimino la pianificazione*/
                    for (int f = i; f<eventi.size(); f++)       /*cerco la pianificazione di spegnimento*/
                    {
                        if (eventi[f].entry_get_id_element() == device.get_device_ID()) /*trovo*/
                        {
                            /*elimino*/
                            elimina(f);
                            
                            /*inserisco le entry evento*/
                            sort(entryInizio);
                            sort(entryFine);
                        }
                    }
                    /*non esco dal ciclo perche ci possono essere piu di una pianificazione impostata*/
                }
                else
                {
                    if (eventi[i].entry_get_id_element() == device.get_device_ID() && !eventi[i].entry_get_status())
                    /*PIANIFICATO SPEGNIMENTO*/
                    {
                        /*non elimino la entry vecchie perche dipende se current time ha superato quella di accensione*/
                        for (int f = i; f>0; f--)   /*cerco la prima entry accensione associata*/
                        {
                            if (eventi[f].entry_get_id_element() == device.get_device_ID() && eventi[f].entry_get_keyTime() <= tempo.get_currentTime())
                            {
                                cout<<"non e possibile applicare questa pianificazione perche va in contrasto con quelle gia in corso"<<endl;
                                break;
                            }
                            else if (eventi[f].entry_get_id_element() == device.get_device_ID() && eventi[f].entry_get_keyTime() > tempo.get_currentTime())
                                /*pianificazione di accensione non e ancora in esecuzione*/
                            {
                                /*elimino le vecchie pianificazioni*/
                                elimina(i);
                                elimina(f);
                                
                                /*inserisco le nuove entry evento*/
                                sort(entryInizio);
                                sort(entryFine);
                            }
                        }
                        break;
                    }
                }
            }
        }
        else    /*se entrambe le entry evento hanno keyTime maggiore di tutte le entry nel vettore allora vanno inserite alla fine*/
        {
            /*inserisco le entry evento*/
            sort(entryInizio);
            sort(entryFine);
        }
    }
}

void DataStructure::set (Device &device, int start_device, int stop_device) /*setto accensione e spegnimento*/
{
    /*problemi possibili*/
    if (device.is_device_alwaysOn())
    {
        cout<< device.get_device_name() << " e' un dispositivo sempre acceso, non puo avere pianificazioni di alcun tipo"<<endl;
    }
    else if (device.is_device_automatic())
    {
        cout<<device.get_device_name() << " e un dispositivo automatico, non puo avere una pianificazione di spegnimento "<<endl;
    }
    else if (stop_device <= start_device)
    {
        cout << "non e possibile spegnere il dispositivo prima che si accendi: (start: " << start_device << " stop: " << stop_device<<" )" << endl;
    }
    else if (start_device < tempo.get_currentTime())
    {
        cout << "non e possibile applicare una programmazione nel passato (curent time: " << tempo.get_currentTime() << " )" << endl;
    }
    else
    {
        /*creo le entry evento*/
        EntryStructure entryInizio (start_device, device.get_device_name(), true, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());
        
        EntryStructure entryFine (stop_device, device.get_device_name(), false, device.get_device_consume(), device.get_device_ID(), device.is_device_alwaysOn());

        if (eventi.empty()) /*se non e'ancora successo nulla inserisoc le entry*/
        {
            /*inserisco le entry eventi*/
            sort(entryInizio);
            sort(entryFine);
        }
        else
        {
            /*inserisco le entry nel vettore*/
            sort(entryInizio);
            sort(entryFine);
            
            /*variabili di appoggio dove salvo in che posizione si trovano le entry nel vettore*/
            int position_start = 0;
            int position_end = 0;
            
            /*ciclo per trovare la posizione corretta*/
            for (int i =0; i<eventi.size(); i++)
            {
                if (eventi[i].entry_get_id_element() == device.get_device_ID() && eventi[i].entry_get_keyTime() == start_device)
                {
                    position_start = i;
                }
                
                if (eventi[i].entry_get_id_element() == device.get_device_ID() && eventi[i].entry_get_keyTime() == stop_device)
                {
                    position_end = i;
                }
            }
            
            /*controlllo se in mezzo a queste entry ci sono delle programmazioni dello stesso oggetto*/
            if (position_start+1 != position_end) /*ci sono programmazioni in mezzo*/
            {
                for (int i = position_start+1; i < position_end; i++)
                {
                    /*ce una programmazione per questo dispositivo?*/
                    if (eventi[i].entry_get_id_element() == device.get_device_ID()) /*SI*/
                    {
                        if (eventi[i].entry_get_status()) /*progrmmazione di accensione*/
                        {
                            /*cerco la programmazione di spegnimento associata*/
                            for (int f = i; f< eventi.size(); f++)
                            {
                                if (eventi[f].entry_get_id_element() == device.get_device_ID() && eventi[f].entry_get_status() == false)
                                {
                                    elimina(i);
                                    elimina(f);
                                }
                            }
                        }
                        else /*accensione prima della mia */
                        {
                            /*controllo che start non sia >= a current time*/
                            int x =0;
                            for (int f = 0; f<position_start; f++)
                            {
                                cout<<"cado in questo caso"<<endl;
                                if (eventi[f].entry_get_id_element() == device.get_device_ID() && eventi[f].entry_get_status() == true)
                                {
                                    x = f;
                                }
                            }
                            
                            if (eventi[x].entry_get_keyTime() > tempo.get_currentTime())
                            {
                                /*posso ancora togliere questa programmazione*/
                                elimina(i);
                                elimina(x);
                            }
                            else
                            {
                                /*programmazione e gia in corso, non posso aggiungere le programmazione corrente*/
                                cout<<"programmazione di "<<device.get_device_name()<<" non puo essere aggiunta perche in contrasto con quella delle: ";
                                cout<<eventi[x].entry_get_keyTime()<< " impostata fino alle "<<eventi[i].entry_get_keyTime()<<endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

void DataStructure::rm (Device &device) /*rimuove le pianificazioni impostate per un certo dispositivo*/
{
    if (device.is_device_alwaysOn())
    {
        cout<< device.get_device_name() << " e un dispositivo sempre acceso, non puo avere pianificazioni di alcun tipo";
    }
    else if (device.is_device_on())
    {
        cout<<"dispositivo " << device.get_device_name() << " rimane acceso " << endl;
    }
    else
    {
        /*cerco dove ci troviamo allínterno del vettore eventi*/
        int evento_attuale = 0;
        for (int i =0; i< eventi.size(); i++)
        {
            if (eventi[i].entry_get_keyTime() <= tempo.get_currentTime())
            {
                evento_attuale = i;
            }
        }
        
        /*elimino tutte le pianificazioni da qui in poi*/
        for (int i = evento_attuale; i< eventi.size(); i++)    /*cerco in cio che accadra da now in poi*/
        {
            if (eventi[i].entry_get_id_element() == device.get_device_ID()) /*trovo una pianificazioe di quel device*/
            {
                elimina(i);
                i--;
            }
        }
    }
}

/*funzione finalizzata a modificare gli stati dei dispositivi (accenderli se risultano accesi e viceversa)*/
void DataStructure::accender()
{
    /*trovo fino a quale indice ho controllato con la scorsa chiamata*/
    int fine_analisi_precedente = 0;
    for (int i =0; i< eventi.size(); i++)
    {
        if (eventi[i].entry_get_keyTime() > tempo.get_lastTime())
        {
            fine_analisi_precedente = i;
        }
    }

    /*analizzo solo le cose nuove*/
    for (int i = fine_analisi_precedente; i< eventi.size(); i++)
    {
        /*trovo una entry evento di accensione*/
        if (eventi[i].entry_get_keyTime() <= tempo.get_currentTime() && eventi[i].entry_get_status() == true)
        {
            for (int f =0; f<lista.size(); f++)
            {
                if (eventi[i].entry_get_id_element() == lista[f].get_device_ID() && lista[f].is_device_on() == false)
                {
                    /*modifico stato dispositivo*/
                    lista[f].modify_device_start(eventi[i].entry_get_keyTime());
                    lista[f].modify_device_end(-1);
                    lista[f].modify_device_status(true);
                }
            }
        }
        /*trovo una entry evento di spegnimento*/
        else if (eventi[i].entry_get_keyTime() <= tempo.get_currentTime() && eventi[i].entry_get_status() == false)
        {
            for (int f =0; f<lista.size(); f++)
            {
                if (eventi[i].entry_get_id_element() == lista[f].get_device_ID() && lista[f].is_device_on() == true)
                {
                    /*modifico stato dispositivo*/
                    lista[f].modify_device_status(false);
                    lista[f].modify_device_end(eventi[i].entry_get_keyTime());
                    lista[f].modify_device_timeOn(lista[f].get_device_end() - lista[f].get_device_start());
                }
            }
        }
    }
}

/*serve per dire quanta potenza stiamo usando*/
double DataStructure::getCurrentPower(void)
{
    vector<EntryAccesi> DeviceOn = get_device_in_order();   /*salvo i device accesi ORA in un vettore*/
    double currentPower = 0;

    /*calcolo current power*/
    for(int i = (int)DeviceOn.size()-1; i > -1; i--)
    {
        currentPower = currentPower + DeviceOn[i].entryON_get_Power();
    }

    return currentPower;
}

/*funzione che spegne dispositivi se ce bisogno*/
void DataStructure::checkPower(void)
{
    vector<EntryAccesi> DispositiviAccesi = get_device_in_order();  /*/*salvo i device accesi ORA in un vettore*/

    while(getCurrentPower()<-3.5) /*spengo i dispositivi*/
    {
        string dev_name = DispositiviAccesi.back().entryON_get_Name();
        DispositiviAccesi.pop_back();
        Device dev = lista.get_Device_by_name(dev_name);
        set(dev, false);
    }
}
