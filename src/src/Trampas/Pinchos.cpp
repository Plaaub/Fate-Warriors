#include "Pinchos.h"
#include "../Tiempo/Time.h"

Pinchos::Pinchos(short _id, float _i_x, float _i_y,float _i_z) : Trampas(_id, _i_x, _i_y,  _i_z, -50){
siguiente_tiempo_hace_danyo =_reloj->get_current();
}

Pinchos::~Pinchos(){}

void Pinchos::render(){}


bool Pinchos::puede_quitar_vida(){ 
    if(_reloj->get_current() > siguiente_tiempo_hace_danyo){
        siguiente_tiempo_hace_danyo = _reloj->get_current() + 1000;
        return true;
    }
    
    return false;
}