//
//  time.h
//  progetto_finale
//
//  Created by Eduardo on 02/01/25.
//
#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <stdexcept>

using namespace std;
class Time
{
private:
    
    int current_time;                                   /*tempo attuale*/
    int last_time;                                      /*tempo prima della chiamata set time*/
    
public:
    
    Time()
    {
        current_time = 0;
        last_time = 0;
    };
    
    /*cambio tempo attuale*/
    void set_time(int new_time)
    {
        if (new_time>current_time)
        {
            last_time = current_time;
            current_time = new_time;
        } /*viene fatto il salto*/
        else
        {
            if (new_time<current_time) cout << "salto temporale puo essere fatto solo avanti nel tempo";
            else cout << "e stato risettato lo stesso momento di prima";
        }
    }
    
    /*FUNZIONI GET*/
    int get_lastTime()
    {
        return last_time;
    };
    
    int get_currentTime()
    {
        return current_time;
    };
};

#endif
