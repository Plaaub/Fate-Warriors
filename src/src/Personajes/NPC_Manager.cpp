#include "NPC_Manager.h"

#include "NPC.h"

NPC_Manager::NPC_Manager() {
	_n_enemigos = 1;
	_n_aliados = 0;

	_npc = new NPC*[_n_enemigos];

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_npc[_cont] = new NPC(0,19,0,0,5,15);
	}
}

NPC_Manager::~NPC_Manager() {
	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

NPC** NPC_Manager::get_npcs(){
	return _npc;
}

unsigned short NPC_Manager::get_n_enemigos(){
	return _n_enemigos;
}