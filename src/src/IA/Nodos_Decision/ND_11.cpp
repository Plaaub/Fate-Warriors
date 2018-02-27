#include "ND_11.h"

#include "../Blackboard.h"
#include "../../Personajes/Character.h"

#include<iostream>

ND_11::ND_11(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_11::~ND_11() {

}

enum Enum_Acciones ND_11::toma_decision(Blackboard* _blackboard){

    //std::cout <<"Entra ND_11\n";
	if(_blackboard->_tengo_arma_larga_distancia == true) { // TRUE, es 1
		// Equipar arma larga distancia y atacar normal
		_blackboard->equipar_arma_larga_distancia();
		_blackboard->_ataque_a_realizar = Ataque_Normal;
        //std::cout <<"_tengo_arma_larga_distancia\n";
		return _nodo_der->toma_decision(_blackboard);
	}
	// Seguir a enemigo mas cerca
	Character * enemigo = _blackboard->_enemigo_mas_cerca;

    _blackboard->objetivo_x = enemigo->getX();
	_blackboard->objetivo_y = enemigo->getZ();
    //std::cout <<"NO _tengo_arma_larga_distancia\n";
	return _nodo_izq->toma_decision(_blackboard);
}