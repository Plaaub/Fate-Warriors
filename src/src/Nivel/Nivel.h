

#include <string>
#include "Nodo.h"
#include "Pasillo.h"
#include "Grafo.h"
#include <stack>
#include <vector>
#ifndef HEADERS_NIVEL_H_
#define HEADERS_NIVEL_H_

const float metro=39.3701;

class Vertice;
class Grafo;

class Nivel {
public:
	static Nivel* nivel_instancia();
	Nivel(std::string &_i_fichero);
	~Nivel();
	void nivel_crear_pasillo(std::ifstream& _Nivel_txt, std::string& _iteracion);
	void nivel_crear_nodo(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion);
	void nivel_crear_objetos(std::ifstream& _i_Nivel_txt, std::string& _i_iteracion, Nodo* _i_nodo);
	void nivel_crear_grafo(std::ifstream& _i_nivel_txt, std::string& _i_iteracion, Grafo* _i_grafo);
	void nivel_crear_arista(std::ifstream& _i_nivel_txt, std::string& _i_iteracion);
	void nivel_crear_adyacentes(std::ifstream& _i_nivel_txt, std::string& _i_iteracion);
	Vertice * nivel_get_vertice(int _i_id);
	Nodo * nivel_get_nodo(int _i_id);
	Pasillo * nivel_get_pasillo(int _i_id);
	void nivel_set_lod(int _i_id);
	int nivel_get_id_vertice(float _i_x, float _i_y);
	Nodo_blackboard* nivel_get_blackboard(float _i_x, float _i_y);
	unsigned short nivel_pathfindinglod1(float _i_xorigen, float _i_yorigen, float xdestino, float ydestino);
	//unsigned short nivel_get_n_enemigos(int _i_id);
	//void nivel_set_n_enemigos(int _i_id,unsigned short _i_n_enemigos);

	inline unsigned short nivel_get_lod(int _i_id){
		return _lod2->grafo_get_vertice(_i_id)->_lod;
	}

	/*inline unsigned short nivel_get_n_enemigos(int _i_id){
		//buscar el vertice con la id
		return _lod2->grafo_get_vertice(_i_id)->_n_enemigos;
	}*/
	/*inline void nivel_set_n_enemigos(int _i_id,unsigned short _i_n_enemigos){
		//buscar el vertice con la id
		_lod2->grafo_get_vertice(_i_id)->_n_enemigos=_i_n_enemigos;
	}*/

//metodos de grafo
	/*bool nivel_vacio();
	unsigned short nivel_tamano();
	Vertice * nivel_get_vertice(int _i_id);
	void nivel_inserta_arista_bi(Vertice *_i_origen, Vertice *i_i_destino, int _i_peso);	
	void nivel_inserta_vertice(Vertice* _i_vert);
	void nivel_lista_adyacencia();
	void nivel_eliminar_arista(Vertice *_i_origen, Vertice *_i_destino);
	void nivel_anular();
	void nivel_crear_arista(std::ifstream& _i_nivel_txt, std::string& _i_iteracion);*/




	//metodos de nivel
	/*En un futuro cambiarlo por las coordenadas x,y
	* In: x,y
	*/
	std::stack<Vertice*> nivel_camino_corto_l2(Vertice *_i_origen, Vertice *_i_destino);
private:
	//Vertice *_h;
	static Nivel* instancia;
	Grafo *_lod2;
	void inserta_arista(Vertice *_i_origen, Vertice *_i_destino, int _i_peso);

};
#endif /* HEADERS_NIVEL_H_ */
