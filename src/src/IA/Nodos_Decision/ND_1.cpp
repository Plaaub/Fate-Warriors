#include "ND_1.h" 
 
#include "../Blackboard.h" 
#include "../../Personajes/NPC.h" 
 
#include<iostream> 
 
ND_1::ND_1(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) { 
  _valor = _i_valor; 
} 
 
ND_1::~ND_1() { 
 
} 
 
enum Enum_Acciones ND_1::toma_decision(Blackboard* _blackboard){ 
 
    //std::cout <<"Entra ND_1\n"; 
  if(_blackboard->_npc_padre->get_zona()->esta_jugador_en_zona() == true && _blackboard->_enemigo_mas_cerca_esta_cerca == true) { // TRUE, es 1 
        //std::cout <<"hay enemigo cerca\n"; 
    return _nodo_der->toma_decision(_blackboard); 
  }  
  //std::cout <<"IR A MI ZONA NODO 1\n"; 
    //std::cout <<"NO hay enemigo cerca\n"; 
  return _nodo_izq->toma_decision(_blackboard); 
} 