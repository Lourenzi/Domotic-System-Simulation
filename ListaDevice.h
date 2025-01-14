//
//  ListaDevice.h
//  progetto_finale
//
//  Created by Eduardo on 02/01/25.
//


//CREARE FUNZIONI CHE MODIFICANO DIRETTMENTE QUESTO OGGETTO


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
        
        Device impianto_fotovoltaico ("impianto_fotovoltaico", 1.5/*KW*/, 1, true);
        lista_Device.push_back(impianto_fotovoltaico);
        name.push_back("impianto_fotovoltaico");
        
        
        Device lavatrice ("lavatrice", -2/*KW*/, 110/*minuti*/, 2, false);
        lista_Device.push_back(lavatrice);
        name.push_back("lavatrice");
        
        
        Device lavastoviglie ("lavastoviglie", -1.5/*KW*/, 195/*minuti*/, 3, false);
        lista_Device.push_back(lavastoviglie);
        name.push_back("lavastoviglie");
        
        
        Device termostato ("termostato", -2/*KW*/, 4, false);
        lista_Device.push_back(termostato);
        name.push_back("termostato");
        
        
        Device tapparelle_elettriche ("tapparelle_elettriche", -0.3/*KW*/, 1, 5, false);
        lista_Device.push_back(tapparelle_elettriche);
        name.push_back("tapparelle_elettriche");
        
        
        Device scaldabagno ("scaldabagno", -1/*KW*/, 6, false);
        lista_Device.push_back(scaldabagno);
        name.push_back("scaldabagno");
        
        
        Device frigorifero ("frigorifero", -0.4/*KW*/, 7, true);
        lista_Device.push_back(frigorifero);
        name.push_back("frigorifero");
        
        
        Device forno_a_microonde ("forno_a_microonde", -0.8/*KW*/, 2/*minuti*/, 8, false);
        lista_Device.push_back(forno_a_microonde);
        name.push_back("forno_a_microonde");
        
        
        Device asciugatrice ("asciugatrice", -0.5/*KW*/, 60, 9, false)/*minuti*/;
        lista_Device.push_back(asciugatrice);
        name.push_back("asciugatrice");
        
        
        Device televisore ("televisore", -0.2/*KW*/, 60/*minuti*/, 10, false);
        lista_Device.push_back(televisore);
        name.push_back("televisore");
    }
    
    
    void modify_device_status (int indice, bool status)
    {
        lista_Device[indice].modify_device_status(status);
    };
    
    
    vector<Device> get_vector()
    {
        return lista_Device;
    };
    
    
    vector<string> get_lista_name()
    {
        return name;
    };
    
    
    Device get_device_by_ID(int ID)
    {
        int i =0;
        Device d;
        
        while(i < lista_Device.size())
        {
            if(lista_Device.at(i).get_device_ID() == ID)
            {
                d = lista_Device.at(i);
            }
            i++;
        }
        return d;
    }
    
    
    Device get_Device_by_name(string device_name)
    {
        int i=0;
        Device d;
        
        while(i < lista_Device.size())
        {
            if(lista_Device.at(i).get_device_name() == device_name)
            {
                d = lista_Device.at(i);
            }
            i++;
        }
        return d;
    }
    
    
    int size()
    {
        return (int)lista_Device.size();
    }
    
    Device& operator[](int i)
    {
        if (i >= lista_Device.size())
        {
            throw invalid_argument("fuori dalla taglia del vettore");
        }
        return lista_Device[i];
    }
};

#endif
