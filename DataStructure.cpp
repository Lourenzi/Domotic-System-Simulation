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
vector<Device> listone = lista.get_vector();

DataStructure::DataStructure() {}; /*creo la linea temporale*/  /*vector degli elementi e gia vuoto*/

Time DataStructure::get_Time()
{
    return tempo;
}

void DataStructure::set_Time(int newTime)
{
    cout<<endl;
    cout << "****************************** SALTO TEMPORALE A " << newTime << " ************************************" << endl;
    cout<<endl;
    
    tempo.set_time(newTime);

    accender();
    get_device_in_order();

    checkPower();
}

void DataStructure::sort(EntryStructure entry) /*riordinare il vettore in base al tempo che caratterizza ogni evento*/
{
    int timeEntry = entry.get_keyTime();    /*momento di quel evento*/
    if (entry.get_keyTime() == (60*24)+1)
    {
        eventi.insert(eventi.end(), entry);
    }
    else
    {
        int counter = 0;
        for (int i =0; i<eventi.size(); i++)
        {
            if (timeEntry < eventi[i].get_keyTime()) /*prende il primo piu grande perche poi brekka*/
            {
                counter = i;
                break;
            }
            
            if (timeEntry >= eventi[i].get_keyTime() && i == eventi.size()-1)
            {
                cout << "per riordinare " << entry.get_element() << " sono entrato qui " << endl;
                counter = (int)eventi.size();
                break;
            }
        }
        cout<<"posizione alla quale inserisco la entry " << counter<<endl;
        eventi.insert(eventi.begin() + counter, entry); /*aggiunge una locazione nel vettore pirma di quello che accadrebbe subito dopo*/
    }
    cout<<endl;
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
    //cout<<"-----------------------"<<limite<<endl;

    for (int i =0; i< limite; i++)
    {
        if (eventi[i].get_status() == true)
        {
            //cout<<"evento che sto aggiungendo alla lista e collegato all elemento " << eventi[i].get_element() <<endl;
            EntryAccesi info (eventi[i].get_element(), eventi[i].get_power());
            accensioni.insert(accensioni.begin(), info);
        }
        else
        {
            if (accensioni.size() == 1)
            {
                accensioni.pop_back();
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
                accensioni.pop_back();
            }
        }
    }
    
    for (int i =0; i< accensioni.size(); i++)
    {
        cout<<"dispositivo acceso in questo momento " << accensioni[i].get_Name() << endl;
    }
    
    return accensioni;
}

double DataStructure::getCurrentPower(void)
{
    vector<EntryAccesi> DeviceOn = get_device_in_order();
    double currentPower = 0;

    for(int i = DeviceOn.size()-1; i > -1; i--)
    {
        currentPower = currentPower + DeviceOn[i].get_Power();
    }

    return currentPower;
}

void DataStructure::checkPower(void) //vieni chiamata in set_time
{
	vector<EntryAccesi> DispositiviAccesi = get_device_in_order();

	while(getCurrentPower()>3.5) //spegne i dispositivi 
	{
			string dev_name = DispositiviAccesi.back().get_Name();
			DispositiviAccesi.pop_back();

            Device dev = lista.get_Device_by_name(dev_name);
            set(dev, false);

			//spegnere il dispotivo
	}
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
            
            if (device.is_device_automatic())
            {
/*CONTROLLO*/   /*devo controllare che in questo intervallo io non abbia programmao láccnesione del dispositivo in precedenza*/
                for (int i=0; i<eventi.size(); i++)
                {
                    if (eventi[i].get_element() == device.get_device_name() &&
                        eventi[i].get_keyTime()>tempo.get_currentTime() &&
                        eventi[i].get_keyTime()<(tempo.get_currentTime()+device.get_device_timer())) /*trovo un accensione del dispositivo*/
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

    checkPower();
}

void DataStructure::set (Device device, int moment) /*accesione programmata*/
{
    if (moment < tempo.get_currentTime()) throw invalid_argument("non si puo aplicare una pianificazion al passato");
    
    if (device.is_device_automatic())
    {
        cout<<"il dispositivo e automatico"<<endl;
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
        cout<<"posisizione inizio: " << posizione_inizio << " posizione fine: " << posizione_fine << endl;
        
        //posso avere sia la fine che linizio di una programmazione allínterno del mio intervallo
        //intanto vediamo se ce una delle due
        //bool entrato = false;
        if (posizione_inizio != posizione_fine)
        {
            for (int i = posizione_inizio; i <= posizione_fine; i++) //controllo che non ci fosse gia una pianificazione impostata
            {
                cout<<"giriamo in tondo"<<endl;
                if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_keyTime() > moment)
                {
                    cout<<"entro nellíf"<<endl;
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
        for (int i = posizione; i < eventi.size(); i ++)
        {
            if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_status() == true) //e pianificata un accensione
            {
                for (int f = i; f < eventi.size(); f++)
                {
                    if (eventi[f].get_element() == device.get_device_name() && eventi[i].get_status() == false)
                    {
                        //elimino questa entry
                        elimina(f);
                    }
                }
            }
        }
    }
}

void DataStructure::set (Device device, int start_device, int stop_device) /*setto accensione e spegnimento*/
{
    /*modifico informazioni di accensione e spegnimento del dispositivo*/
    
    if (device.is_device_automatic()) throw invalid_argument("ha un tempo prefissato");
    if (stop_device <= start_device) throw invalid_argument("non e possibile spegnere il dispositivo prima che si accendi");
    if (start_device < tempo.get_currentTime()) throw invalid_argument("programmazione nel passato non ha senso");

    EntryStructure entryInizio (start_device, device.get_device_name(), true, device.get_device_consume());
    /*creo la entry che mi rapprsenta láccensione*/
    EntryStructure entryFine (stop_device, device.get_device_name(), false, device.get_device_consume());
    /*creo la entry che mi rappresenta lo spegnimento*/

    if (eventi.empty())
    {
        sort(entryInizio);
        sort(entryFine);
    }
    else
    {
        /*inserisco le entry nel vettore*/
        sort(entryInizio);
        sort(entryFine);
        
        /*mi salvo dove si trovano nella lista*/
        int position_start = 0;
        int position_end = 0;
        
        for (int i =0; i<eventi.size(); i++)
        {
            if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_keyTime() == start_device)
            {
                position_start = i;
            }
            
            if (eventi[i].get_element() == device.get_device_name() && eventi[i].get_keyTime() == stop_device)
            {
                position_end = i;
            }
        }
        
/*debug*/cout<<"fino a qui tutto apposto"<<endl;
        
        /*controlllo se in mezzo a queste entry ci sono delle programmazioni dello stesso oggetto*/
        
        if (position_start+1 != position_end) /*ci sono programmazioni in mezzo*/
        {
            for (int i = position_start+1; i < position_end; i++)
            {
                /*ce una programmazione per questo dispositivo?*/
                if (eventi[i].get_element() == device.get_device_name()) /*SI*/
                {
                    if (eventi[i].get_status()) /*progrmmazione di accensione*/
                    {
                        for (int f = i; f< eventi.size(); f++)
                        {
                            if (eventi[f].get_element() == device.get_device_name() && eventi[f].get_status() == false)
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
                            if (eventi[f].get_element() == device.get_device_name() && eventi[f].get_status() == true)
                            {
                                x = f;
                            }
                        }
                        
                        if (eventi[x].get_keyTime() > tempo.get_currentTime())
                        {
                            /*posso ancora togliere questa programmazione*/
                            elimina(i);
                            elimina(x);
                        }
                        else
                        {
                            /*programmazione e gia in corso, non posso aggiungere le programmazione corrente*/
                            cout<<"programmazione di "<<device.get_device_name()<<" non puo essere aggiunta perche in contrasto con quella delle: ";
                            cout<<eventi[x].get_keyTime()<< " impostata fino alle "<<eventi[i].get_keyTime()<<endl;
                        }
                    }
                }
            }
        }
    }
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

void DataStructure::accender()
{
    //cout<<"sono dentro ACCENDER " << endl;
    for (int i = 0; i< eventi.size(); i++)
    {
        //if (eventi[i].get_keyTime() <= tempo.get_currentTime()) cout<<"prima vera"<<endl;
        //if (eventi[i].get_status() == true) cout<<"seconda vera"<<endl;
        
        //cout<< "tempo corrente: " << tempo.get_currentTime() << endl;
        //cout<< "momento in cui avviene lévento i" << tempo.get_currentTime() << endl;
        
        if (eventi[i].get_keyTime() <= tempo.get_currentTime() && eventi[i].get_status() == true)
        {
            //cout<<"-----ce qualcosa di acceso ed e " << eventi[i].get_element() <<endl;
            for (int f =0; f<listone.size(); f++)
            {
                if (eventi[i].get_element() == listone[f].get_device_name() && listone[f].is_device_on() == false)
                {
                    listone[f].modify_device_status(true);
                }
            }
        }
        else if (eventi[i].get_keyTime() <= tempo.get_currentTime() && eventi[i].get_status() == false)
        {
            for (int f =0; f<listone.size(); f++)
            {
                if (eventi[i].get_element() == listone[f].get_device_name() && listone[f].is_device_on() == true)
                {
                    listone[f].modify_device_status(false);
                }
            }
        }
    }
}

void DataStructure::stampa()
{
    cout<<"-------------------------------------tempo in cui mi trovo " << tempo.get_currentTime() << endl;
    cout<<"sono dentro stampa, eventi.size(): "<< eventi.size() << endl;
    for (int i =0; i<eventi.size(); i++)
    {
        int orario = eventi[i].get_keyTime();
        int ora = orario / 60;
        int minuti = orario % 60;
        
        cout<<"["<< ora << ":" << minuti << "]";
        
        string acceso;
        if (eventi[i].get_status() == true) acceso = " si e acceso ";
        else acceso = " si e spento ";
        
        cout<< " " << eventi[i].get_element() << acceso << endl;
    }
}
