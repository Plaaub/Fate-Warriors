#include "Zonas_Manager.h"

#include "Zona.h"
#include "Zona_Final.h"
#include "Zona_Inicial.h"
#include "Zona_Coliseo.h"
#include "Zona_Respawn_Infinito.h"

#include <iostream>

Zonas_Manager::Zonas_Manager() {

	_equipoA = 0;
	_equipoB = 0;


    // tener xml con la informacion de todos los objetos
    
	_n_zonas = 3;
	_zonas = new Zona*[_n_zonas];

    unsigned short _cont;
	float mult = 4.9212625;
//	_zonas[0] = new Zona(5*mult, 0*mult, 37*mult,20,20, Enum_Equipo_A);

	_zona_incial = new Zona_Inicial(12.5*mult, 0*mult, 12.5*mult,(15*mult)/2,(15*mult)/2, 12.5*mult, 11*mult); 	//Zona 1
	_zonas[0] = _zona_incial;
		
	
	_zonas[1]  = new Zona_Respawn_Infinito(29.5*mult, 0*mult, 28.5*mult,(15*mult)/2,(15*mult)/2, 5, 120); 		//Zona 3
	
	_zonas[2]  = new Zona_Coliseo(10.5*mult, 0*mult, 34.5*mult, (15*mult)/2, (15*mult)/2, 1, 2, 1, 3, 11);		//Zona 7
}

Zonas_Manager::~Zonas_Manager() {
    unsigned short _cont;
    
	for(_cont = 0; _cont < _n_zonas; _cont++) {
		delete _zonas[_cont];
	}
	delete [] _zonas;
}

void Zonas_Manager::actualizar_zonas(){

	for(uint8_t zona=0; zona<_n_zonas; zona++){
		_zonas[zona]->actualizar_zona();
	}
}

Zona** Zonas_Manager::get_zonas(){
	return _zonas;
}

unsigned short Zonas_Manager::get_n_zonas(){
	return _n_zonas;
}


Vector2 Zonas_Manager::get_posicion_zona_inicial(){
	return _zona_incial->get_posicion_inicial();
}