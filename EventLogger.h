//Created by Lorenzo

#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H


#include <iostream>
#include <fstream>
#include "ListaDevice.h"
#include "time.h"

class EventLogger{
    public:
        EventLogger(){ logFile.open("eventLog.txt"); }

        void log_updateTime(Time& time){  //aggiornamento info sull'orario corrente
            string time_formatted = format_time(time.get_currentTime());
            cout<<"["<<time_formatted<<"] L'orario attuale e' "<<time_formatted<<endl;
            logFile<<"["<<time_formatted<<"] L'orario attuale e' "<<time_formatted<<endl;
        }

        void log_updateStatus(Time& time, string device_name, string status){  //aggiornamento info in caso di accensione o spegnimento di un device
            string time_formatted = format_time(time.get_currentTime());
            if(status == "on"){
                cout<<"["<<time_formatted<<"] Il dispositivo "<<device_name<<" si e' acceso"<<endl;
                logFile<<"["<<time_formatted<<"] Il dispositivo "<<device_name<<" si e' acceso"<<endl;
            }
            else{
                cout<<"["<<time_formatted<<"] Il dispositivo '"<<device_name<<"' si e' spento"<<endl;
                logFile<<"["<<time_formatted<<"] Il dispositivo '"<<device_name<<"' si e' spento"<<endl;
            }
        }
    
        void log_updateStatus(Time& time, string device_name, bool on){  //aggiornamento info in caso di accensione o spegnimento di un device (overloaded)
            string time_formatted = format_time(time.get_currentTime());
            if(on){
                cout<<"["<<time_formatted<<"] Il dispositivo "<<device_name<<" si e' acceso"<<endl;
                logFile<<"["<<time_formatted<<"] Il dispositivo "<<device_name<<" si e' acceso"<<endl;
            }
            else{
                cout<<"["<<time_formatted<<"] Il dispositivo '"<<device_name<<"' si e' spento"<<endl;
                logFile<<"["<<time_formatted<<"] Il dispositivo '"<<device_name<<"' si e' spento"<<endl;
            }
        }

        void log_updateTimer(Time& time, string device_name, int start_time, int end_time){  //aggiornamento info impostazione timer di funzionamento
            string time_formatted = format_time(time.get_currentTime());
            string end_time_formatted = format_time(end_time);
            string start_time_formatted = format_time(start_time);
            cout<<"["<<time_formatted<<"] Impostato un timer per il dispositivo '"<<device_name<<"' dalle "<<start_time_formatted<<" alle "<<end_time_formatted<<endl;
            logFile<<"["<<time_formatted<<"] Impostato un timer per il dispositivo '"<<device_name<<"' dalle "<<start_time_formatted<<" alle "<<end_time_formatted<<endl;
        }

        void log_removeTimer(Time& time, string device_name){  //aggiornamento info rimozione timer relativo ad un dispositivo
            string time_formatted = format_time(time.get_currentTime());
            cout<<"["<<time_formatted<<"] Rimosso il timer dal dispositivo '"<<device_name<<"'"<<endl;
            logFile<<"["<<time_formatted<<"] Rimosso il timer dal dispositivo '"<<device_name<<"'"<<endl;
        }

        void log_showConsume(Time& time, string device_name, double consume, int time_on){  //mostra consumo fino al tempo corrente di uno specifico dispositivo
            string time_formatted = format_time(time.get_currentTime());
            double total_consume = ((double)time_on/60)*consume + ((double)(time_on%60)/60)*consume;
            if(total_consume >= 0){
                cout<<"["<<time_formatted<<"] Il dispositivo ha attualmente consumato '"<<total_consume<<"' kWh"<<endl;
                logFile<<"["<<time_formatted<<"] Il dispositivo ha attualmente consumato '"<<total_consume<<"' kWh"<<endl;
            }
            else{
                cout<<"["<<time_formatted<<"] Il dispositivo ha attualmente prodotto '"<<(-1)*total_consume<<"' kWh"<<endl;
                logFile<<"["<<time_formatted<<"] Il dispositivo ha attualmente prodotto '"<<(-1)*total_consume<<"' kWh"<<endl;
            }
            
        }
        
        void log_showConsumeTotal(Time& time, ListaDevice& lista){  //mostra consumi fino al tempo corrente di tutti i dispositivi

        }

    private:
        ofstream logFile;
        string format_time(int time_min){ //funzione helper per formattare il tempo (da minuti dalle 00:00)
            string time_formatted, mm, hh;
            int mins = time_min%60;
            int hours = time_min/60;
            if(mins < 10) {mm = "0" + to_string(mins);}
            else {mm = to_string(mins);}
            if(hours < 10) {hh = "0" + to_string(hours);}
            else {hh = to_string(hours);}
            time_formatted = hh + ":" + mm;
            return time_formatted;
        }
        
};

#endif
