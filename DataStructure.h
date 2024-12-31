//
//  DataStructure.h
//  progetto_finale
//
//  Created by Eduardo on 31/12/24.
//

#include <iostream>
#include <string>
#include <vector>
#include "Device.h"

using namespace std;
class DataStructure : public Device
{
private:
    array<string,10> name_id;
    array<array<bool, 10> /*10 Device*/, 60 /*minuti*/ * 24 /*ore*/> data;
    int tempo;
    
public:
    DataStructure(); /*array con gli id lo riempio piano piano*/
    void set (bool status) override;
    
    array<bool, 10> get_Device_On(int moment);               //mi dice in un certo momento chi e acceso (true = accesp, false = spento)
    bool get_one_device_on(int id, int moment);              //mi dice in un certo momento se un dispositiov particolare e acceso o spento
    int get_consumo(int moment);                             //mi dice quanto sto consumando in un istante preciso
    
    int get_id();                                            //dal nome mi collego al relativo id

};
