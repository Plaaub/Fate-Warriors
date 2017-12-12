#include "Datos_Partida.h"

#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Personajes/NPC.h"
#include "Objeto_Estandar.h"

Datos_Partida::Datos_Partida() {

	_jugador = new Player(0,30,230,0);
	_n_enemigos = 1;

	_npc = new NPC*[_n_enemigos];

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_npc[_cont] = new NPC(0,19,0,0,5,15);
	}

	//Crea y devuelve el id del mapa
	Interfaz* _interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
    //_interfaz_grafica->Interfaz_cargaMapaZip("models/Gilipollas.zip", //llamamos a cargar mapa para así indicar que 
	//					"ManuManco.obj",false,					  //este es el nodo con el que los demás colisionaran
	//					0,0,0);
	
	Objeto_Estandar* mapa = new Objeto_Estandar(1, 0, 0, 0, "models/Gilipollas.zip", "ManuManco.obj"); 

	/* MODELADO DEL PRIMER NIVEL
	_interfaz_grafica->Interfaz_cargaMapaZip("models/Nodo1.zip", //llamamos a cargar mapa para así indicar que 
						"Nodo1.obj",false,					  //este es el nodo con el que los demás colisionaran
						5,0,5);
	_interfaz_grafica->Interfaz_cargaMapaZip("models/Nodo3.zip", //llamamos a cargar mapa para así indicar que 
						"Nodo3.obj",false,					  //este es el nodo con el que los demás colisionaran
						21,0,22);
	_interfaz_grafica->Interfaz_cargaMapaZip("models/Nodo7.zip", //llamamos a cargar mapa para así indicar que 
						"Nodo7.obj",false,					  //este es el nodo con el que los demás colisionaran
						27,0,3);
	_interfaz_grafica->Interfaz_cargaMapaZip("models/Pasillo2.zip", //llamamos a cargar mapa para así indicar que 
						"Pasillo2.obj",false,					  //este es el nodo con el que los demás colisionaran
						13,0,20);
	_interfaz_grafica->Interfaz_cargaMapaZip("models/Pasillo6.zip", //llamamos a cargar mapa para así indicar que 
						"Pasillo6.obj",false,					  //este es el nodo con el que los demás colisionaran
						20,0,11);
	_interfaz_grafica->Interfaz_cargaMapaZip("models/Pasillo8.zip", //llamamos a cargar mapa para así indicar que 
						"Pasillo8.obj",false,					  //este es el nodo con el que los demás colisionaran
						30,0,18);
	*/

	_interfaz_grafica = nullptr;
}

Datos_Partida::~Datos_Partida() {
	delete _jugador;

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

unsigned short Datos_Partida::get_n_enemigos(){
	return _n_enemigos;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC** Datos_Partida::get_npcs(){
	return _npc;
}

