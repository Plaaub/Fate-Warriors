#include "Consumible_Power_Up.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"
#include "../Tiempo/Time.h"


Consumible_Power_Up::Consumible_Power_Up(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 0), _reloj(Time::Instance()){
    const char* cstr  = "models/Consumibles/Carne/Carne.obj";
    
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    _personaje = nullptr;

}

Consumible_Power_Up::~Consumible_Power_Up(){
}

bool Consumible_Power_Up::usar(Character* _i_personaje){
    if(_personaje!=nullptr){
        if(comprobar_tiempo_power_up()){
            _personaje->disminuir_danyo_ataque_fuerte(50);
            _personaje->eliminar_power_up_puntero();
            std::cout << "YO SOY EL " << this << std::endl;
          return true;
        }
        std::cout << _personaje->get_danyo_ataque_fuerte()<< "pupa que hace\n";
    }
    else{
        if(comprobar_colision(_i_personaje)){
            activar_tiempo();
            _personaje=_i_personaje;
            _personaje->aumentar_danyo_ataque_fuerte(50);
            _personaje->anyadir_power_up(this);
        }
    }
	return false;	
}
	
void Consumible_Power_Up::render(){

}

void Consumible_Power_Up::activar_tiempo(){
        _duracion_power_up = _reloj->get_current() + 5000;
}

bool Consumible_Power_Up::comprobar_tiempo_power_up(){
    if(_reloj->get_current() > _duracion_power_up){
        return true;
    }    
    return false;
}