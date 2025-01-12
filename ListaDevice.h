//
//  ListaDevice.h
//  progetto_finale
//
//  Created by Eduardo on 02/01/25.
//

#ifndef LISTADEVICE_H
#define LISTADEVICE_H

#include <vector>
#include <iostream>

#include "Device.h"

using namespace std;
class ListaDevice
{
private:
    vector<Device> lista_Device;
    vector<string> name;
public:
    ListaDevice()
    {
        Device impianto_fotovoltaico ("impianto_fotovoltaico", 1.5/*KW*/);
        lista_Device.push_back(impianto_fotovoltaico); name.push_back("impianto_fotovoltaico");
        
        
        Device lavatrice ("lavatrice", -2/*KW*/, 110/*minuti*/);
        lista_Device.push_back(lavatrice); name.push_back("lavatrice");
        
        
        Device lavastoviglie ("lavastoviglie", -1.5/*KW*/, 195/*minuti*/);
        lista_Device.push_back(lavastoviglie); name.push_back("lavastoviglie");
        
        
        Device termostato ("termostato", -2/*KW*/);
        lista_Device.push_back(termostato); name.push_back("termostato");
        
        
        Device tapparelle_elettriche ("tapparelle_elettriche", -0.3/*KW*/, 1);
        lista_Device.push_back(tapparelle_elettriche); name.push_back("tapparelle_elettriche");
        
        
        Device scaldabagno ("scaldabagno", -1/*KW*/);
        lista_Device.push_back(scaldabagno); name.push_back("scaldabagno");
        
        
        Device frigorifero ("frigorifero", -0.4/*KW*/);
        lista_Device.push_back(frigorifero); name.push_back("frigorifero");
        
        
        Device forno_a_microonde ("forno_a_microonde", -0.8/*KW*/, 2/*minuti*/);
        lista_Device.push_back(forno_a_microonde); name.push_back("forno_a_microonde");
        
        
        Device asciugatrice ("asciugatrice", -0.5/*KW*/, 60)/*minuti*/;
        lista_Device.push_back(asciugatrice); name.push_back("asciugatrice");
        
        
        Device televisore ("televisore", -0.2/*KW*/, 60/*minuti*/);
        lista_Device.push_back(televisore); name.push_back("televisore");
    }
    
    Device get_Device_by_name(string device_name){
        int i=0;
        Device d;
        while(i < lista_Device.size()){
            if(lista_Device.at(i).get_device_name() == device_name){
              d = lista_Device.at(i);
            }
            i++;
        }
        return d;
    }
    vector<Device> get_vector() {return lista_Device;};
    vector<string> get_lista_name() {return name;};
};

#endif
