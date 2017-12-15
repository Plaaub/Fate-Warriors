#include "Player.h"
#include <iostream>
#include "../Entrada/Input.h"
#include "../Entrada/Controles.h"
#include "../Interfaz/Interfaz.h"
#include "../Interfaz/Interfaz_Fisica.h"
#include "../Camara/Camara.h"
#include "../Tiempo/Time.h"
#include "../Interfaz/Matcher.h"
#include "../Utilidades/Modelados.h"
                                                                                              //  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z) : Character(_id,_i_x, _i_y, _i_z, 15, 10000)
                                                                {   
    //_matcher = new Matcher(LLAVE_R, LLAVE_M, _i_x, _i_y,  _i_z,  1,true);                                                                
    _matcher = new Matcher(PERSONAJE_R, PERSONAJE_M, _i_x, _i_y,  _i_z,  1,true); 
    _tiempo = Time::Instance();
    //std::cout<<"eso: "<<_interface<<std::endl;
    //crear nodo de personaje del motor
    _otro_tiempo = _tiempo->get_start();
    _tiempo_anterior = _tiempo->get_start();
  // _nodoId = _interface->Interfaz_crearProtaZip("models/Personaje.zip", "Personaje.obj",false,
  //                      _i_x,_i_y,_i_z);
 //  _interface_fisica->CargaRigidBodyProta(200,_i_x,_i_y,_i_z);
}

Player::~Player(){
    delete _matcher;
    _matcher = nullptr;
}

void Player::update(){
    
    Controles* controles = Controles::Instance();
    Interfaz* interface = Interfaz::Interfaz_getInstance();
    bool moving = false;
    if(interface!=nullptr){    
        float angulo = interface->Interfaz_GetCamaraAngleRad();
   
        float miX = interface->Interfaz_GetNode(_nodoId)->getPosition().X;
        float miY = interface->Interfaz_GetNode(_nodoId)->getPosition().Y;
        float miZ = interface->Interfaz_GetNode(_nodoId)->getPosition().Z;

        float movX,movY,movZ;

        _otro_tiempo = _tiempo->get_current();

        double _time = _tiempo->get_tiempo_desde_ultimo_update_segundos();

        float desp_x, desp_z;

        desp_x = desp_z = 0;

        if(controles->estaPulsada(Input_key::W)){
            miZ += cos(angulo) * _velocidad * _time;
            miX += sin(angulo) * _velocidad * _time;
            desp_z += cos(angulo) * _velocidad * _time;
            desp_x += sin(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(0);
            moving = true;
        }
        
        if(controles->estaPulsada(Input_key::S)){
            miZ -= cos(angulo) * _velocidad * _time;
            miX -= sin(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(180);    
            desp_z -= cos(angulo) * _velocidad * _time;
            desp_x -= sin(angulo) * _velocidad * _time;
            moving = true;
        }

        if(controles->estaPulsada(Input_key::A)){
            miZ += sin(angulo) * _velocidad * _time;
            miX -= cos(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(-90);
            desp_z += sin(angulo) * _velocidad * _time;
            desp_x -= cos(angulo) * _velocidad * _time;
            moving = true;
        }

        if(controles->estaPulsada(Input_key::D)){
            miZ -= sin(angulo) * _velocidad * _time;
            miX += cos(angulo) * _velocidad * _time;
            interface->Interfaz_rotarProta(90);
            desp_z -= sin(angulo) * _velocidad * _time;
            desp_x += cos(angulo) * _velocidad * _time;
            moving = true;
        }

        if(controles->estaPulsada(Input_key::Escape)){
            interface->Interfaz_Apagar();
        }
        //setX(miX);
        //setZ(miZ);
        //interface->Interfaz_moverProta(miX, miZ);
        if(moving){
            _matcher->Mover(desp_x,miY,desp_z);
        }
        else{
            //std::cout<<"-------BBBBBBBBBBBBBBBBBBBBBB-------------------------"<<std::endl;
            _matcher->Mover(0,0,0);
        }
            //std::cout<<"-------------MOVING: "<<moving<<"----------------------"<<std::endl;
        _tiempo_anterior = _otro_tiempo;

        
  }
}
			
void Player::render(){
  
}