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
    int current_time;
public:
    Time() {current_time = 0;};
    
    void set_time(int new_time)
    {
        if (new_time>current_time) {current_time = new_time;} /*viene fatto il salto*/
        else
        {
            if (new_time<current_time) throw invalid_argument("salto temporale puo essere fatto solo avanti nel tempo");
            else throw invalid_argument("e stato risettato lo stesso momento di prima");
        }
    }
    
    int get_currentTime() {return current_time;};
};
#endif
